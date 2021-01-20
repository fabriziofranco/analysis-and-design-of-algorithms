#ifndef DISTANCE_H
#define DISTANCE_H

#include <cmath>
#include <utility>

double calculateEuclideanDistance(std::pair<int, int> p1, std::pair<int, int> p2) {
    return sqrt(pow((p1.first - p2.first), 2) + pow((p1.second - p2.second), 2));
}

double calculateManhattanDistance(std::pair<int, int> p1, std::pair<int, int> p2) {
    return abs(p1.first - p2.first) + abs(p1.second - p2.second);
}

double calculateChebyshevDistance(std::pair<int, int> p1, std::pair<int, int> p2) {
    return fmax(abs(p1.first - p2.first), abs(p1.second - p2.second));
}

#endif
