//
// Created by Christian Ledgard on 10/19/20.
//

#ifndef PARTIAL_PROJECT_TEAM4_MATRIX_H
#define PARTIAL_PROJECT_TEAM4_MATRIX_H

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>

template <typename T>
class Matrix{
    std::string fileNameSource;
    std::string fileNameDestination;
    std::vector<std::vector<T> > matrix;
    int rows, columns;
    bool isBinaryImage;

public:
    Matrix(const std::string &fileNameSource, const std::string &fileNameDestination) 
    : fileNameSource(fileNameSource), fileNameDestination(fileNameDestination) {
        this->isBinaryImage = false;
    }

    Matrix(const std::string &fileNameDestination) 
    : fileNameDestination(fileNameDestination) {
        this->isBinaryImage = false;
    }


    Matrix() {}

    void import(){
        std::ifstream file;
        file.open(fileNameSource);

        std::string line;
        while (getline(file, line)) {
            std::stringstream ss(line);
            std::vector<T> vec;
            while(ss.good()){
                std::string substr;
                getline(ss, substr, ',');
                vec.push_back(stoi(substr));
            }
            matrix.push_back(vec);
            vec.clear();
        }
        this->rows = this->matrix.size();
        this->columns = this->matrix[0].size();
    }

    void write(){
        std::ofstream file(fileNameDestination, std::ofstream::trunc);
        for (auto &lista : matrix){
            for (int i = 0; i < lista.size(); ++i) {
                file << lista[i];
                if(i != lista.size()-1) file << ",";
            }
            file << "\n";
        }
    }

    void print(){
        for (auto &lista : matrix){
            for (auto &elemento : lista){
                std::cout << elemento << " ";
            }
            std::cout << std:: endl;
        }
    }

    const std::vector<std::vector<T> > &getMatrix() const {
        return matrix;
    }

    void setMatrix(const std::vector<std::vector<T> > &matrix) {
        Matrix::matrix = matrix;
    }

    void invert(){
        std::vector<std::vector<T> > temp;
        for (auto &lista : matrix){
            std::vector<T> column;
            for (auto &elemento : lista){
                int invertido = 255 - elemento;
                column.push_back(invertido);
            }
            temp.push_back(column);
        }
        this->matrix = temp;
    }

    void renderizar(std::vector<std::vector<int> > &rawMatrix, int maxValueOfIntensity){
        std::vector<std::vector<int> > tempMatrix;

        for (auto &row : rawMatrix){
            std::vector<int> column;
            for(auto &current : row){
                int newValue = (current / (float) maxValueOfIntensity) * 255;
                column.emplace_back(newValue);
            }
            tempMatrix.emplace_back(column);
        }
        this->matrix = tempMatrix;
    }

    void assignValueToMatrix(T value) {
        this->matrix = std::vector<std::vector<T> >(this->rows, std::vector<T>(this->columns, value));
    }

    bool validIndex(int i, int long j) {
        return i >= 0 && i < rows && j >= 0 && j < columns;
    }

    int getRows() {
        return this->rows;
    } 

    int getColumns() {
        return this->columns;
    }

    void matrixToBinary() {
        if (this->isBinaryImage) {
            return;
        } else {
            this->isBinaryImage = true;
            for (int i = 0; i < this->matrix.size(); ++i) {
                std::vector<T> tempRow;
                for (T &val : this->matrix[i]) {
                    if (val > 250) {
                        tempRow.push_back(0); // borde blanco
                    } else {
                        tempRow.push_back(1); // relleno negro
                    }
                }
                this->matrix[i] = tempRow;
            }
        }
    }

};

#endif //PARTIAL_PROJECT_TEAM4_MATRIX_H
