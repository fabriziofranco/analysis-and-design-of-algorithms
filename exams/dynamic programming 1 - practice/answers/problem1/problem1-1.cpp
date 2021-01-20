#include <iostream>
#include <vector>
using namespace std;


int recursiveFibonacci(int n){
    if(n==1 or n==0)
        return n;
    else
        return recursiveFibonacci(n-1)+recursiveFibonacci(n-2);
}


int worker(int n, int* dm,int size){
    if(dm[n]!=-1){
        return dm[n];
    }
    else{
        if(n==0 or n ==1){
            dm[n]=n;
            return n;
        }
        int result= worker(n-1,dm,size)+worker(n-2,dm,size);
        dm[n]=result;
        return result;
    }
}


int dynamicFibonacci(int n){
    int dm[n];
    for(int i = 0; i <= n; i++)
        dm[i] = -1;
   return worker(n,dm,n);
}



int main() {
    cout<<recursiveFibonacci(10)<<endl;
    cout<<dynamicFibonacci(1000)<<endl;
}

