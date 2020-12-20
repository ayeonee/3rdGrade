#include <iostream>
using namespace std;

int ZeroOneKnapsack(int W, int n, int val[], int wt[]){
    int K[W+1][n+1];
    for(int x=0; x<=W; x++){
        for(int j=0; j<=n; j++){
            if(x == 0 || j == 0) 
                K[x][j] = 0; 
            else{
                K[x][j]=K[x][j-1];
                if(wt[j]<=x){
                    K[x][j]=max(K[x][j],K[x-wt[j]][j-1]+val[j]);
                }
            }
        }
    }
    return K[W][n];
}

int main(){
    int W=50;
    int val[]={60,100,120};
    int wt[]={10,20,30};
    int n=sizeof(val)/sizeof(val[0]);

    cout<<ZeroOneKnapsack(W,n,val,wt);
    return 0;
}