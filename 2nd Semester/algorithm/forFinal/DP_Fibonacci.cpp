#include <iostream>
using namespace std;

/* Bottom up */
int BUfibonacci(int n){
    int arr[n];
    arr[0]=0;
    arr[1]=1;
    for(int i=2; i<=n; i++)
        arr[i]=arr[i-2]+arr[i-1];
    return arr[n];
}

/* Top down : 안됨 
int F[]={0,1,0,};
int TDfibonacci(int n){
    if(F[n]!=0){
        return F[n];
    }
    else
        F[n]=TDfibonacci(n-1)+TDfibonacci(n-2);
    return F[n];
}*/

int main(){
    int n=5;
    cout << "Bottom up " <<BUfibonacci(n) <<endl;
    return 0;
}