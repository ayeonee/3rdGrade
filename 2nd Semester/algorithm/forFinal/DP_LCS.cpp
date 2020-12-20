#include <iostream>
#include <string>
using namespace std;

int LCS(string &X, string &Y){
    int m=X.length();
    int n=Y.length();
    int C[m+1][n+1];

    for(int i=0; i<=m; i++){
        for(int j=0; j<=n; j++){
            if(i==0 || j==0)
                C[i][j]=0;
            else if(X[i-1]==Y[j-1])
                C[i][j]=C[i-1][j-1]+1;
            else
                C[i][j]=max(C[i][j-1],C[i-1][j]);
        }
    }
    return C[m][n];
}

int main(){
    string X="AGGTAB";
    string Y="GXTXAYB";

    cout << "Length of LCS is "<<LCS(X,Y)<<endl;
    return 0;
}