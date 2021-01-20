#include <iostream>

long problem4BruteForce(long base, long power){
    long result=1;
    for(int i=0;i<power;++i)
        result*=base;
    return result;
}


long problem4DivideAndConquer(long base, long power){
    if(power==0)
        return 1;
    else{
        long extraPowerIfNeeeded = power%2==0 ? 1:base;
        long dividedProblem1 = problem4DivideAndConquer(base, power / 2);
        long dividedProblem2 = problem4DivideAndConquer(base, power / 2);
        return dividedProblem1 * dividedProblem2 * extraPowerIfNeeeded;
    }
}

int main() {
    std::cout << "Problem 4 - Powering\n";

    long base = 2;
    long power = 5;
    printf("%ld power of %ld is %ld\n", base, power, problem4BruteForce(base, power));
    printf("%ld power of %ld is %ld\n", base, power, problem4DivideAndConquer(base, power));
}
