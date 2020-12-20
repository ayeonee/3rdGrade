#include <iostream>
using namespace std;

int unboundedKnapsack(int W, int n, int wt[], int val[]){
    int K[W+1];
    K[0]=0;
    for(int x=1; x<=W; x++){
        K[x]=0;
        for(int i=1; i<=n; i++){
            if(wt[i]<=x){
                K[x]=max(K[x-wt[i]], K[x-wt[i]]+val[i]);
            }
        }
    }
    return K[W];
}

int main(){
    int W=10;
    int val[]={20, 8, 14, 13, 35};
    int wt[]={6, 2, 4, 3, 11};
    int n=sizeof(val)/sizeof(val[0]);

    cout<<unboundedKnapsack(W,n,val,wt);
    return 0;
}