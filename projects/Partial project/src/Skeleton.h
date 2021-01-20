//
// Created by Christian Ledgard on 10/26/20.
//

#ifndef PARTIAL_PROJECT_TEAM4_SKELETON_H
#define PARTIAL_PROJECT_TEAM4_SKELETON_H

#include <vector>
#include <iostream>
#include <algorithm>
#include <map>
#include <set>

#include "Distance.h"

using namespace std;

struct Pixel
{
    int x, y;
    int intensidad;

    Pixel(int x, int y, int intensidad) : x(x), y(y), intensidad(intensidad) {}
    Pixel() {}

    bool operator < (const Pixel &pixel) const
    {
        return (intensidad > pixel.intensidad);
    }
};

struct Cuadrante{
    int x, y;
    vector<Pixel> cuadrante;

    Cuadrante(int x, int y) {
        this->x = x;
        this->y = y;
    };
};

struct Straight{
    double a, b;
    int begin_x,end_x;
    bool flag=false;
};



class Skeleton
{
    vector<vector<int> > distanceTransform;
    vector<vector<int> > resultMatrix;
    vector<vector<Cuadrante> > cuadrantes;
    int ratioCantidadCuadrantes;
    int numTopStrongestPixel;
    vector<Pixel> mostRelevantPixels;
    vector<Straight> straightVector;
    vector<pair<int, int> > skeletonPixels;

public:
    Skeleton(const vector<vector<int> > &distanceTransform, int ratioCantidadCuadrantes,
                   int numTopStrongestPixel) : distanceTransform(distanceTransform),
                                               ratioCantidadCuadrantes(ratioCantidadCuadrantes),
                                               numTopStrongestPixel(numTopStrongestPixel) {}

    vector<vector<int> > run(){
        generarCuadrantes();
        hallarMaximosLocales();
        return resultMatrix;
    }


    void generarCuadrantes(){
        unsigned long numElementosX = distanceTransform[0].size()/ratioCantidadCuadrantes;
        unsigned long numElementosy = distanceTransform.size()/ratioCantidadCuadrantes;

        int sobranteY = 0, sobranteX = 0;
        if(distanceTransform.size() % numElementosy != 0) sobranteY = 1;
        if(distanceTransform[0].size() % numElementosX != 0) sobranteX = 1;

        for (int k = 0; k < numElementosy + sobranteY; ++k) {
            vector<Cuadrante> temp;
            for (int i = 0; i < numElementosX + sobranteX; ++i) {
                temp.emplace_back(i,k);
            }
            cuadrantes.push_back(temp);
            temp.clear();
        }

        for (int i = 0, conty = 0,temy = 0; i < distanceTransform.size(); i++, temy++)
        {
            if(temy >= distanceTransform.size()/numElementosy){
                conty++;
                temy = 0;
            }
            for (int j = 0, contx = 0, temx = 0; j < distanceTransform[0].size(); j++, temx++)
            {
                if(temx >=  distanceTransform[0].size()/numElementosX){
                    contx++;
                    temx = 0;
                }
                cuadrantes[conty][contx].cuadrante.emplace_back(i,j,distanceTransform[i][j]);
            }
        }
    }

    void hallarMaximosLocales(){
        for (auto &row: distanceTransform){
            vector<int> temp;
            for (auto &elemento: row){
                temp.push_back(0);
            }
            resultMatrix.push_back(temp);
            temp.clear();
        }

        for (auto &row : cuadrantes){
            for(auto &cuadrante: row){
                vector<Pixel> vectorDeCuadrantes = cuadrante.cuadrante;
                sort(vectorDeCuadrantes.begin(),vectorDeCuadrantes.end());
                for (int i = 0; i < numTopStrongestPixel; ++i) {
                    Pixel pixelAGuardar = vectorDeCuadrantes[i];
                    resultMatrix[pixelAGuardar.x][pixelAGuardar.y] = pixelAGuardar.intensidad;
                    if (pixelAGuardar.intensidad > 0) {
                        this->mostRelevantPixels.push_back(pixelAGuardar);
                    }
                }
            }
        }
    }

    bool check(Pixel dot1, Pixel pixel, Pixel nearest,set<pair<Pixel,Pixel>>lines, vector<Pixel>copySkeletonPixels){
        bool result = true;
        Pixel temp = copySkeletonPixels[0];
        if(nearest.x==temp.x and temp.y==nearest.y)
            return result;
        if(lines.find(make_pair(dot1,pixel)) != lines.end())
            result=false;
        // if(lines.find(make_pair(pixel,dot1)) != lines.end())
        //     result=false;
        // if(lines.find(make_pair(pixel,nearest)) != lines.end())
        //     result=false;
        // if(lines.find(make_pair(nearest,pixel)) != lines.end())
        //     result=false;
        return result;
    }


    Pixel nearestPoint(Pixel dot1, vector<Pixel> & copySkeletonPixels, set<pair<Pixel,Pixel>> & lines ){
        Pixel nearest = copySkeletonPixels[0];
        for(int i = 1; i < copySkeletonPixels.size(); ++i){
            Pixel pixel= copySkeletonPixels[i];
            double nearestDistance= calculateEuclideanDistance(make_pair(dot1.x,dot1.y),make_pair(nearest.x,nearest.y));
            double pixelDistance= calculateEuclideanDistance(make_pair(dot1.x,dot1.y),make_pair(pixel.x,pixel.y));
            if(pixelDistance < nearestDistance && check(dot1,pixel,nearest,lines,copySkeletonPixels))
                nearest = pixel;
        }
        lines.insert(make_pair(dot1,nearest));
        return nearest;
    }

    void matchDots() {
        vector<Pixel> copySkeletonPixels = mostRelevantPixels;
        set<pair<Pixel,Pixel>>  lines;
        for (auto it = copySkeletonPixels.begin(); it != copySkeletonPixels.end(); ++it) {
            Pixel currentPixel = *it;
            Pixel closestPixel = nearestPoint(currentPixel, copySkeletonPixels,lines);
            generateEdge(currentPixel, closestPixel);
        }
    }

    void generateEdge(Pixel pixel1, Pixel pixel2){
        Straight straight;
        int min_y = pixel1.y  < pixel2.y ? pixel1.y : pixel2.y;
        int max_y = pixel1.y  > pixel2.y ? pixel1.y : pixel2.y;


        int position=pixel2.y-pixel1.y;
        if(position==0){
            straight.flag=true;
            straight.b = pixel2.x;
            straight.a = 0;
            int min_x = pixel1.x < pixel2.x ? pixel1.x : pixel2.x;
            int max_x = pixel1.x  > pixel2.x ? pixel1.x : pixel2.x;
            straight.begin_x=min_x;
            straight.end_x=max_x;
        }
        else{
            straight.a = (pixel2.x - pixel1.x)/(pixel2.y - pixel1.y);
            straight.b = pixel2.x - (pixel2.y * straight.a);
            straight.begin_x=min_y;
            straight.end_x=max_y;
        }
        straightVector.push_back(straight);
    }

    void straightPointsToPlot() { 
        for (auto i : straightVector) {
            for (int x = i.begin_x; x <= i.end_x; ++x) {
                int y = i.a * x + i.b;
                if(!i.flag){
                    this->skeletonPixels.push_back(make_pair(x, y));
                }
                else{
                    this->skeletonPixels.push_back(make_pair(y, x));
                }
            }
        }
    }

    vector<vector<int> > generateSkeletonAsMatrix() {
        matchDots();
        straightPointsToPlot();
        vector<vector<int> > skeletonAsMatrix = vector<vector<int> >(distanceTransform.size(), vector<int>(distanceTransform[0].size(), 0));
        for (pair<int, int> point : this->skeletonPixels) {
            skeletonAsMatrix[point.second][point.first] = 255;
        }
        return skeletonAsMatrix;
    }

};
#endif //PARTIAL_PROJECT_TEAM4_SKELETON_H
