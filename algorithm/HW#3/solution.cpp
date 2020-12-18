#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include "solution.h"
using namespace std;

/* Fill free to implement any function on here */
int inputSize;
int cnt=0;
TreeNode* root;
TreeNode* lastNode;
vector<pair<TreeNode*, int>> branch;
vector<long long int> pathSum;
vector<long long int> nodeNum;

vector<long long int> countBranch(struct TreeNode* root){
    if(root){
        countBranch(root->left);
        nodeNum.push_back(root->val);
    }
    return nodeNum;
}

unsigned long long int calPathSum(vector<long long int> pathSum){
    unsigned long long int resultSum=0;
    for(int i=0; i<pathSum.size(); i++){
        resultSum+=pathSum[i];
    }
    return resultSum;
}

unsigned long long int Solution::getPathSum (struct TreeNode* root)
{
    long long int sum=0;
    if(root){
        cnt++;
        branch.push_back(make_pair(root, cnt));
        
        if(root->left==NULL && root->right==NULL){
            for(int i=0; i<branch.size(); i++){
                int n=branch.size()-branch[i].second;
                long long int k=branch[i].first->val * pow(10,n);
                sum+=k;
            }
            pathSum.push_back(sum);
        }
        if(root==lastNode){
            branch.pop_back();
            cnt--;
        }
        getPathSum(root->left);
        if(root==branch.front().first){
            branch.clear();
            cnt=1;
            branch.push_back(make_pair(root, cnt));
        }
        else if(root->left) {
            int k= countBranch(root->right).size();
            nodeNum.clear();
            for(int i=0; i<k; i++){
                branch.pop_back();
                cnt--;
            }
        }
       getPathSum(root->right);
    }
    
    return calPathSum(pathSum);
}


struct TreeNode* Solution::buildTree (string filename)
{
    ifstream ifs (filename);
    if(ifs.is_open()){
        ifs >> inputSize;
        TreeNode *tree[inputSize+1];
        for(int i=1; i<=inputSize; i++){
            tree[i]=new TreeNode;
        }
        for(int i=1; i<=inputSize; i++){
            if(i*2<inputSize){
                tree[i]->left=tree[i*2];
                tree[i]->right=tree[i*2+1];
                ifs >> tree[i]->val;
            }
            else if(i*2 == inputSize){
                tree[i]->left=tree[i*2];
                tree[i]->right=NULL;
                ifs >> tree[i]->val;
            }
            else{
                tree[i]->left=tree[i]->right=NULL;
                ifs >> tree[i]-> val;
            }
        }
        root=tree[1];
        lastNode=tree[inputSize];
    }
    return root;
}