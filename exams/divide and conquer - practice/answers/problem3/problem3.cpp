#include <iostream>
#include <vector>

using namespace std;

pair<pair<int,int>,long>findMaxCross(vector<int> &stockPrices,int min,int mid ,int max){
    long sum=0;
    int posLeft=mid,posRight=mid;
    long rightSum=INT64_MIN;
    long leftSum=INT64_MIN;
    for(auto i=mid; i>=min;--i){
        sum+= stockPrices[i];
        if(sum>leftSum){
            leftSum=sum;
            posLeft=i;
        }
    }
    sum=0;


    for(auto i=mid; i<=max;++i){
        sum+= stockPrices[i];
        if(sum>rightSum){
            rightSum=sum;
            posRight=i;
        }
    }
    return make_pair(make_pair(posLeft,posRight),leftSum+rightSum);
}


pair<pair<int,int>,long> findMaxSubArray(vector<int> &stockPrices,int min ,int max){
    if(min==max)
        return make_pair(make_pair(min,max),stockPrices[min]);
    else{
        int mid=(min+max)/2;
        auto left = findMaxSubArray(stockPrices,min,mid);
        auto right = findMaxSubArray(stockPrices,mid+1,max);
        auto cross = findMaxCross(stockPrices,min,mid,max);

        if(left.second>=right.second and left.second>=cross.second) return left;
        else if(right.second>=left.second and right.second>=cross.second) return right;
        else return cross;
    }
}



pair<int,int> problem3(std::vector<int> & stockPrices){
    vector<int> changeFactor;
    changeFactor.push_back(0);
    for(auto i=1;i<stockPrices.size();++i){
        changeFactor.push_back(stockPrices[i]-stockPrices[i-1]);
    }
    return findMaxSubArray(changeFactor,0,(int)changeFactor.size()-1).first;
}

int main() {
    std::cout << "Problem 3 - Volatile investment\n";

    std::vector<int> stocks = {100,113,110,85,105,102,86,63,81,101,94,106,101,79,94,90,97};
    auto [buy, sell] = problem3(stocks);

    printf("Buying at day %d\nSelling at day %d\n", buy, sell);
}
