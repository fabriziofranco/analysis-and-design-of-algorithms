#ifndef DISTANCE_TRANSFORM_H
#define DISTANCE_TRANSFORM_H

#include <vector>
#include <utility>
#include <limits.h>
#include <set>

#include "Matrix.h"

template <typename MatrixType>
class DistanceTransform {
    Matrix<MatrixType> image;
    std::vector<double> distances;
    std::vector<int> roots;
    std::set<int> pixelQueue;
    double maxDistance = __DBL_MIN__;
    std::vector<std::vector<double> > distanceTransform;
    double(*distanceFunction)(std::pair<int, int>, std::pair<int, int>);

    void initialize() {
        std::vector<std::vector<MatrixType> > imageMatrix = this->image.getMatrix();
        int rows = this->image.getRows();
        int columns = this->image.getColumns();
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < columns; ++j) {
                if (imageMatrix[i][j] != 1) {
                    this->distances[i * columns + j] = 0;
                    this->roots[i * columns + j] = i * columns + j;
                    this->pixelQueue.insert(i * columns + j);
                }
            }
        }

    }

    std::vector<int> getEightNeighbors(int pixel) {
        std::vector<int> neighbors;
        auto [xPos, yPos] = this->getPositionOfPixel(pixel);
        for (int i = xPos - 1; i <= xPos + 1; ++i) {
            for (int j = yPos - 1; j <= yPos + 1; ++j) {
                if (i == xPos && j == yPos) {
                    continue;
                } else if (this->image.validIndex(i, j)) {
                    neighbors.push_back(i * this->image.getColumns() + j);
                }
            }
        }
        return neighbors;
    }

    void calculateDistances() {
        while (!this->pixelQueue.empty()) {
            int pixel = *(this->pixelQueue.begin());
            this->pixelQueue.erase(this->pixelQueue.begin());
            std::vector<int> neighbors = this->getEightNeighbors(pixel);
            for (int &neighbor : neighbors) {
                auto [xPos, yPos] = this->getPositionOfPixel(neighbor);
                if (this->image.validIndex(xPos, yPos)) {
                    double euclideanDistance = this->distanceFunction(this->getPositionOfPixel(this->roots[pixel]), this->getPositionOfPixel(neighbor));
                    if (euclideanDistance < this->distances[neighbor]) {
                        if (this->distances[neighbor] != INT_MAX) {
                            auto it = this->pixelQueue.find(neighbor);
                            if (it != this->pixelQueue.end()) {
                                this->pixelQueue.erase(it);
                            }
                        }
                        this->distances[neighbor] = euclideanDistance;
                        this->roots[neighbor] = this->roots[pixel];
                        this->pixelQueue.insert(neighbor);
                    }
                }
            }
        }
    }

    std::pair<int, int> getPositionOfPixel(int pixel) {
        int xPos = pixel / this->image.getColumns();
        int yPos = pixel % this->image.getColumns();
        return std::make_pair(xPos, yPos);
    }

    void calculateMaxDistance() {
        int rows = this->image.getRows();
        int columns = this->image.getColumns();
        for (int i = 0; i < rows * columns; ++i) {
            if (this->distances[i] > this->maxDistance) {
                this->maxDistance = this->distances[i];
            }
        }
    }

    std::vector<std::vector<double> > calculateDistanceTransform() {
        this->calculateMaxDistance();
        int rows = this->image.getRows();
        int columns = this->image.getColumns();
        std::vector<std::vector<double> > distanceTransform;
        std::vector<double> currentRow;
        for (int i = 0; i < rows * columns; ++i) {
            if (i % columns == 0 && i != 0) {
                distanceTransform.push_back(currentRow);
                currentRow.clear();
            }
            int currentColor = 255 / this->maxDistance * this->distances[i];
            currentRow.push_back(currentColor);
        }
        return distanceTransform;
    }

public:
    DistanceTransform(Matrix<MatrixType> &image, double(*distanceFunction)(std::pair<int, int>, std::pair<int, int>)) {
        this->image = image;
        this->distances = std::vector<double>(this->image.getRows() * this->image.getColumns(), __DBL_MAX__);
        this->roots = std::vector<int>(this->image.getRows() * this->image.getColumns(), INT_MAX);
        this->distanceFunction = distanceFunction;

        this->image.matrixToBinary();

        this->initialize();
        this->calculateDistances();
        this->distanceTransform = this->calculateDistanceTransform();
    }

    std::vector<std::vector<int> > getDistancesAsMatrix() {
        int rows = this->image.getRows();
        int columns = this->image.getColumns();
        std::vector<std::vector<int> > distancesAsMatrix(rows, std::vector<int>(columns, 0));
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < columns; ++j) {
                distancesAsMatrix[i][j] = this->distances[i * columns + j];
            }
        }
        return distancesAsMatrix;
    }

    std::vector<std::vector<double> > getDistanceTransform() {
        return this->distanceTransform;
    }

};

#endif
