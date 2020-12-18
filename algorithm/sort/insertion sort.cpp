#include <iostream>
using namespace std;
int main(void){
    int arr[8]={4,7,1,3,2,8,6,5};
    int len=8;
    for(int i=1; i<len; i++){
        int key=arr[i];
        int j=i-1;
        while(j>=0 && arr[j] > key){
            arr[j+1]=arr[j];
            j--;
        }
        arr[j+1]=key;

        for(int k=0; k<len; k++){
            cout<<arr[k]<<" ";
        }
        cout<<endl;
    }
        
    return 0;
}