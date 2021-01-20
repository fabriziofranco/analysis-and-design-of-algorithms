#include <iostream>
#include <vector>
using namespace std;

void insertionSort(vector<int> &numbers, long index){
    if(index==1) return;
    else{
        index-=1;
        insertionSort(numbers,index);
        int value = numbers[index];
        long pos= index -1;

        while(pos>=0 && numbers[pos]>value){
            numbers[pos+1]=numbers[pos];
            pos-=1;
        }

        numbers[pos+1] = value;
    }
}


int main() {
    vector<int> stocks = {100,113,110,85,105,102,86,63,81,101,94,106,101,79,94,90,97};
    insertionSort(stocks,(long) stocks.size());

    for(auto i:stocks)
        cout<<i<<" ";

    std::cout << "\nProblem 5 - Recursive Insertion Sort\n";
    std::cout << "\nIt works :D\n";

    /// T(n) = T(n-1) + O(n), n>1
    /// T(n) = 1 , n<=1









}
