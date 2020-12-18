#include<iostream>
#include<vector>
using namespace std;

float add_rule(float x, float y, bool n){
    float z;
    if(n==0){
        if(x>=y)
            z=x;
        else
            z=y;
    }
    else{
        if(x>=y)
            z=y;
        else
            z=x;
    }
    return z;
}

float add_rule(float x){
    float z = x;
    return z;
}

float evaluate_output(vector<float> z){
    vector<pair<int, float>>output;

    for(int i=0; i<=10; i++){
        if(i<3) 
            output.push_back(make_pair(i*10,z.front()));

        else if(i<7) 
            output.push_back(make_pair(i*10,z.at(1)));

        else 
            output.push_back(make_pair(i*10,z.at(2)));
    }

    float deno; //분모
    float numer; //분자
    for(int i=0; i<output.size(); i++){
        deno+=output[i].second;
        numer+=output[i].first*output[i].second;
    }
    return numer/deno;
}

int main(){
    cout<<"[크리스프 입력]"<<endl;
    cout<< "프로젝트 자금(x1) = 35%"<<endl;
    cout<< "프로젝트 인력(y1) = 60%"<<endl;

    float A1=0.5, A2=0.2, A3=0.0;
    float B1=0.1, B2=0.7;

    vector<float>z;
    float C1=add_rule(A3, B1, 0); 
    //1 -> and, 0 -> or
    float C2=add_rule(A2, B2, 1);
    float C3=add_rule(A1);

    z.push_back(C1);
    z.push_back(C2);
    z.push_back(C3);

    cout.precision(3);
    cout << "퍼지 프로젝트에 수반하는 위험성은 " << evaluate_output(z) <<"% 이다."<<endl;
    return 0;
}