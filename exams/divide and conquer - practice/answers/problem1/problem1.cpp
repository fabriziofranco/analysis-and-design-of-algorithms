#include <iostream>
#include <vector>

using namespace std;

///BASED ON MERGE SORT IMPLEMENTATION

void merge(vector<int> & numbers, int min, int mid, int max, long & count){
    int i, j, k;
    int size_1 = mid - min;
    int size_2 = max - mid+1;

    int Array_izquierda[size_1], Array_Derecha[size_2];

    for (i = 0; i < size_1; i++){
        Array_izquierda[i] = numbers[min + i];}

    for (j = 0; j < size_2; j++){
        Array_Derecha[j] = numbers[mid + j];}

    i = 0; j = 0;
    k = min;
    while (i < size_1 && j < size_2){
        if (Array_izquierda[i] >= Array_Derecha[j]){
            numbers[k] = Array_izquierda[i];
            i++;}
        else{
            numbers[k] = Array_Derecha[j];
            j++;
            count += mid - (min + i);
        }
        k++;
    }

    while (i < size_1){
        numbers[k] = Array_izquierda[i];
        i++;
        k++;}

    while (j < size_2){
        numbers[k] = Array_Derecha[j];
        j++;
        k++;}
}


void mergeSort(vector<int> & numbers, int min, int max, long &count) {
    int mid = (min + max) / 2;
    if (max > min) {
        mergeSort(numbers, min, mid,count);
        mergeSort(numbers, mid + 1, max,count);
        merge(numbers, min, mid + 1, max,count);
    }
}

void countInvertions(vector<int> & numbers, long & count){
    mergeSort(numbers, 0, (int)numbers.size() - 1, count);
}

long problem1(std::vector<int> & numbers) {
    long tobeReturned=0;
    countInvertions(numbers,tobeReturned);
    return tobeReturned;
}


int main() {
    std::cout << "Problem 1 - Similarity\n";
    vector<int> numbers = {2,4,1,3,5};
    std::cout << problem1(numbers) <<"\n--\n";
    for(auto i:numbers)
        cout<<i<<endl;
}
