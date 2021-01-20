#include <iostream>

#include "Skeleton.h"
#include "DistanceTransform.h"
#include "AlternativeDistanceTransform.h"
#include "Distance.h"
#include <chrono>


void applyEveryDistanceTransform(std::string imageName) {
    std::vector<std::string> extensions = {"EDT.csv", "MDT.csv", "CDT.csv"};
    double (*distanceFunctions[3]) (std::pair<int, int>, std::pair<int, int>) = {calculateEuclideanDistance, 
        calculateManhattanDistance, calculateChebyshevDistance};
    for (int i = 0 ; i < extensions.size(); ++i) {
        Matrix<double> image("images/" + imageName + ".csv", "images/" + imageName + extensions[i]);
        image.import();
        DistanceTransform<double> dt(image, *(distanceFunctions[i]));
        image.setMatrix(dt.getDistanceTransform());
        image.invert();
        image.write();
    }
}

void applyAlternativeDistanceTransform(std::string imageName){
    AlternativeDistanceTransform dt("images/" + imageName + ".csv", "images/" + imageName +  "RES.csv");
    dt.import();
    dt.loadMatrix();
    dt.firstPassDistance();
    dt.secondPassDistance();
    dt.renderizar();
    dt.invert();
    dt.write();
}

int main() {

    Matrix<double> image("images/caballo.csv", "images/caballoEDT.csv");
    image.import();
    DistanceTransform<double> dt(image, calculateEuclideanDistance);
    Skeleton skeleton(dt.getDistancesAsMatrix(), 50, 2);
    skeleton.run();
    Matrix<int> resultado("images/caballoSkeleton.csv");
    resultado.setMatrix(skeleton.generateSkeletonAsMatrix());
    resultado.write();
    // Matrix<int> nubePuntos("images/nubePuntosCaballo.csv");
    // nubePuntos.setMatrix(skeleton.run());
    // nubePuntos.write();

/*
    auto start = std::chrono::high_resolution_clock::now();
    //applyEveryDistanceTransform("caballo");
    applyAlternativeDistanceTransform("caballo");

    auto stop = std::chrono::high_resolution_clock::now();

    auto duration = duration_cast<chrono::milliseconds>(stop - start);
    cout << duration.count() << endl;
    */

    return EXIT_SUCCESS;
}
