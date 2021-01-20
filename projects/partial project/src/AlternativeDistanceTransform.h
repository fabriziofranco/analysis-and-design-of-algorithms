#ifndef PARTIAL_PROJECT_TEAM4_ALTERNATIVEDISTANCETRANSFORM_H
#define PARTIAL_PROJECT_TEAM4_ALTERNATIVEDISTANCETRANSFORM_H


#include "Matrix.h"
#include <vector>
#include <math.h>

using namespace std;

struct point{
    double x, y;
    double intensidad;

    point(double x, double y, double intensidad);
    point();
};

class AlternativeDistanceTransform : public Matrix <int>{

    vector<vector<int>> resultMatrix;
    vector<int> neighbor = {0,0,0,0,0};
    int minVal, maxVal, newMinVal, newMaxVal, numLayers;

public:
    AlternativeDistanceTransform(const string &fileNameSource, const string &fileNameDestination);

    void loadMatrix(){
        auto temp = this->getMatrix();
        for (auto &row: temp){
            vector<int> column;
            for( auto &element : row){
                if(element > 250){
                    column.push_back(0);
                }else{
                    column.push_back(1);
                }
            }
            resultMatrix.push_back(column);
        }
        minVal = 0;
        maxVal = 255;
        newMinVal = newMaxVal = (minVal + maxVal) / 2;
        numLayers = 0;
    }

    void loadNeighbor(int row, int col){
        neighbor[0] = resultMatrix[row - 1][col - 1];
        neighbor[1] = resultMatrix[row - 1][col];
        neighbor[2] = resultMatrix[row - 1][col + 1];
        neighbor[3] = resultMatrix[row][col - 1];
        neighbor[4] = resultMatrix[row][col];
    }

    void loadNeighbor2(int row, int col){
        neighbor[0] = resultMatrix[row][col + 1];
        neighbor[1] = resultMatrix[row + 1][col - 1];
        neighbor[2] = resultMatrix[row + 1][col];
        neighbor[3] = resultMatrix[row + 1][col + 1];
        neighbor[4] = resultMatrix[row][col];
    }

    int min(){
        int min = 0;
        for (int i = 0; i < 4; i++)
        {
            if (neighbor[i] < neighbor[min])
            {
                min = i;
            }
        }
    return neighbor[min];
    }

    int min2(){
        int min = 0;
        for (int i = 0; i < 4; i++)
        {
            if (neighbor[i] < neighbor[min])
            {
                min = i;
            }
        }
        if ((neighbor[min] + 1) < neighbor[4])
            return neighbor[min] + 1;
        else
            return neighbor[4];
    }

    void firstPassDistance(){
        for (int i = 1; i < resultMatrix.size(); i++)
        {
            for (int j = 1; j < resultMatrix[0].size(); j++)
            {
                if (resultMatrix[i][j] > 0)
                {
                    loadNeighbor(i, j);
                    resultMatrix[i][j] = min() + 1;
                }

            }
        }
    }

    void secondPassDistance(){
        for (int i = resultMatrix.size() - 2; i > 0; i--)
        {
            for (int j = resultMatrix[0].size() - 2; j > 0; j--)
            {
                if (resultMatrix[i][j] > 0)
                {
                    loadNeighbor2(i, j);
                    resultMatrix[i][j] = min2();
                    if (resultMatrix[i][j] > numLayers) numLayers = resultMatrix[i][j];

                    if (resultMatrix[i][j] < newMinVal)
                    {
                        newMinVal = resultMatrix[i][j];
                    }
                    if (resultMatrix[i][j] > newMaxVal)
                    {
                        newMaxVal = resultMatrix[i][j];
                    }
                }
            }
        }
    }

    void renderizar(){
        vector<vector<int>> tempMatrix;

        for (auto &row : resultMatrix){
            vector<int> column;
            for(auto &current : row){
                int newValue = (current / (float) numLayers) * maxVal;
                column.emplace_back(newValue);
            }
            tempMatrix.emplace_back(column);
        }
        this->setMatrix(tempMatrix);
    }



};

AlternativeDistanceTransform::AlternativeDistanceTransform(const string &fileNameSource,
                                                           const string &fileNameDestination) : Matrix(fileNameSource,
                                                                                                       fileNameDestination) {

}

#endif //PARTIAL_PROJECT_TEAM4_ALTERNATIVEDISTANCETRANSFORM_H
