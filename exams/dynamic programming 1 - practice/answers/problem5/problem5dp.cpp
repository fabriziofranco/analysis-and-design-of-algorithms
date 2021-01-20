#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <fstream>
using namespace std;
using namespace  chrono;

int problem5(std::vector<int> & values){
    int global = values[0]; //i in problem 4
    int temp = values[0]; //j in problem 4
    for (auto it= values.begin()+1; it!=values.end(); ++it) {
        if(temp<0) temp=0;
        temp += *it;
        if(temp>global)
            global=temp;
    }
    return global;
}

int main() {
    vector<double> times;
    for(auto i=1;i<10000;++i){
        vector<int> values;
        for(auto j=0;j<i;++j)
            values.push_back(rand() % 1000 -1000);
        high_resolution_clock::time_point start = high_resolution_clock::now();
        problem5(values);
        high_resolution_clock::time_point stop = high_resolution_clock::now();;
        double duration =  duration_cast<microseconds>(stop - start).count();
        times.push_back(duration);
    }

    fstream file("dp_times.csv", std::ios::out);
    for(double time : times){
        file <<time << "\n" << std::flush;
    }
    file.close();
    return 0;
}
