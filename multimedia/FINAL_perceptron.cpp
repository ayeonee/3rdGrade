#include <iostream>
using namespace std;

int percept(int input[4][2], int target[4], float w1, float w2, float alpha, float theta){
    int epoch=1;
    cout << "--------------------------------------------------"<<endl;
    while(1){
        cout<<"Epoch : "<< epoch << endl;
        cout << "x1 "<<"x2 "<<"Yd "<<" w1  "<<"w2 "<<" Y "<<" e "<<" w1 "<<" w2 "<<endl;
        cout << "--------------------------------------------------"<<endl;
        float Y;
        int step,e,compare[4];
        for(int i=0; i<4; i++){
            cout<<input[i][0]<<"  "<<input[i][1]<<"  "<<target[i]<<"  "<<w1<<" "<<w2<<" ";
            Y=input[i][0] * w1 + input[i][1] * w2-theta;
            if(Y>=0)
                step= 1;
            else 
                step= 0;

            e=target[i]-step;

            w1 = w1 + alpha * input[i][0] * e;
            w2 = w2 + alpha * input[i][1] * e;
            compare[i]=e;
            cout<<step<<" "<<e<<"  "<<w1<<"  "<<w2<<endl;
        }
        cout << "--------------------------------------------------"<<endl;
        if(compare[0]==0 & compare[1]==0 & compare[2]==0 & compare[3]==0){
            return 0;
        }
        else
            epoch++;
    }
}

int main(){
    int input[4][2]={
        {0,0},
        {0,1},
        {1,0},
        {1,1}
    };

    int targetAND[4]={0,0,0,1};
    int targetOR[4]={0,1,1,1};

    float alpha=0.1, theta=0.2, w1=0.3, w2=-0.1;
    cout << "AND 논리 연산자 학습"<<endl;
    percept(input, targetAND, w1, w2, alpha, theta);
    cout<<"OR 논리 연산자 학습"<<endl;
    percept(input, targetOR, w1, w2, alpha, theta);
    return 0;

}