#include <iostream>
#include <vector>
using namespace std;

//Se usa long long int para probar con valores más grandes, la tasa de crecimiento del factorial es sumamente grande

long long int recursiveFactorial(int n){
    if(n==1)
        return n;
    else
        return n * recursiveFactorial(n-1);
}


long long int worker(int n, vector<long long int>& dm){
    int size=dm.size();
    if(size-1 >= n){
        return dm[n];
    }
    else{
        long long int result;
        if(n==1){
            result=n;
        }
        else{
            result= worker(n-1,dm) * n;
        }
        dm.push_back(result);
        return result;
    }
}


long long int dynamicFactorial(int n){
    vector<long long  int> dm;
    return worker(n,dm);
}



int main() {
    cout<<recursiveFactorial(20)<<endl;
    cout<<dynamicFactorial(20)<<endl;
}

