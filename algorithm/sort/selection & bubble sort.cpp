#include <iostream>
using namespace std;
void swap(int &i, int &j){
    int tmp=0;
    tmp=i;
    i=j;
    j=tmp;
}
void selection_sort (int arr[], int len)
{
    for(int i=0; i<len-1; i++){
        int min=arr[i]; 
        int location=i;
        for(int j=i+1; j<len; j++){
            if(min>arr[j]){
                min=arr[j];
                location=j;
                swap(arr[i], arr[location]);
            }
        }
        for(int k=0; k<len; k++){
            cout<<arr[k]<<" ";
        }
        cout<<endl;
    }
}
void bubble_sort (int arr[], int len)
{
    for(int i=0; i<len-1; i++){
        for(int j=0; j<len-(i+1); j++){
            if(arr[j]>arr[j+1]){
                swap(arr[j], arr[j+1]);
            }
        }
        for(int k=0; k<len; k++){
            cout<<arr[k]<<" ";
        }
        cout<<endl;
    }
    
}

int main(void)
{
   int arr[8] = {4,7,1,3,2,8,6,5};
   int arr2[8] = {4,7,1,3,2,8,6,5};
   int len = 8;
   cout<<"selection_sort"<<endl;
   selection_sort (arr, len);
    cout<<"bubble_sort"<<endl;
    bubble_sort (arr2, len);
}