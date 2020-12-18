#include <iostream>
#include <vector>
#include "solution.h"
#include <math.h>
#include <algorithm>
#include <utility>
using namespace std;

/* Put your codes */
bool compare(pair<double,int> &a, pair<double, int> &b){
    return a.first < b.first;
}

vector<vector<int>> Solution::kClosest (vector<vector<int>>& points, vector<int> keypoint, int K){
    vector<pair<double, int>> distance;
    for(int i=0; i<points.size(); i++){
       double s = sqrt(pow(keypoint[0] - points[i][0], 2) + pow(keypoint[1] - points[i][1], 2));
       distance.push_back(make_pair(s, i));
    }
    sort(distance.begin(),distance.end(),compare);
    int index = forResult(distance, K);
    vector<vector<int>> result;
    result.push_back(points[index]);
    return result;
};

int Solution::forResult(vector<pair<double, int>> distance, int K) {
    if (K < distance.size()) {
        vector<int> randomIndex;
        for (int i = K; i < distance.size(); i++) {
            if (distance[i - 1].first == distance[i].first) {
                randomIndex.push_back(distance[i - 1].second);
            }
            else {
                randomIndex.push_back(distance[i - 1].second);
                break;
            }
        }
        int r = rand()%randomIndex.size();
        return randomIndex[r];
    }
    else
        return distance[K - 1].second;
};