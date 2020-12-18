#include <iostream>
#include <vector>
using namespace std;

class Solution
{
/* DO NOT change this core function prototype. 
 * The main function of the evaluation system will access your codes through this entry point
 */
public:
    vector<vector<int>> kClosest(vector<vector<int>>& points, vector<int> keypoint, int K);
/* DO NOT change by here */
    
/* Put your codes */
    int forResult(vector<pair<double, int>> distance, int K);
};