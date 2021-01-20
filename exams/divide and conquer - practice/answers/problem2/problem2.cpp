#include <iostream>
#include <vector>




int problem2(std::vector<int> & numbers,int min,int max, int k){
    if(min>=max){
        if(numbers[min]==k)
            return 1;
        else
            return 0;
    }

    int dividedProblem1=problem2(numbers,min,(min+max)/2,k);
    int dividedProblem2=problem2(numbers,(min+max)/2+1,max,k);

    return dividedProblem1+dividedProblem2;
}

int main(){
    std::cout << "Problem 2 - Occurrences\n";

    std::vector<int> numbers = {5,5,5,5,5,6,10,5,2,5};
    int k = 5;
    std::cout << problem2(numbers,0,(int) numbers.size()-1, k) << std::endl;
}
