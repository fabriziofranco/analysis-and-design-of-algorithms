#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <fstream>
using namespace std;
using namespace  chrono;
pair<pair<int,int>,long>findMaxCross(vector<int> &values, int min, int mid , int max){
    long sum=0;
    int posLeft=mid,posRight=mid;
    long rightSum=INT64_MIN;
    long leftSum=INT64_MIN;
    for(auto i=mid; i>=min;--i){
        sum+= values[i];
        if(sum>leftSum){
            leftSum=sum;
            posLeft=i;
        }
    }
    sum=0;


    for(auto i=mid; i<=max;++i){
        sum+= values[i];
        if(sum>rightSum){
            rightSum=sum;
            posRight=i;
        }
    }
    return make_pair(make_pair(posLeft,posRight),leftSum+rightSum);
}

pair<pair<int,int>,long> findMaxSubArray(vector<int> &values, int min , int max){
    if(min==max)
        return make_pair(make_pair(min,max), values[min]);
    else{
        int mid=(min+max)/2;
        auto left = findMaxSubArray(values, min, mid);
        auto right = findMaxSubArray(values, mid + 1, max);
        auto cross = findMaxCross(values, min, mid, max);

        if(left.second>=right.second and left.second>=cross.second) return left;
        else if(right.second>=left.second and right.second>=cross.second) return right;
        else return cross;
    }
}

pair<int,int> problem5(std::vector<int> & values){
    return findMaxSubArray(values,0,(int)values.size()-1).first;
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

    fstream file("dc_times.csv", std::ios::out);
    for(double time : times){
        file <<time << "\n" << std::flush;
    }
    file.close();
    return 0;
}
