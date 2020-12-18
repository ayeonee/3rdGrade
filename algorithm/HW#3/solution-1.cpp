#include <iostream>
#include <fstream>
#include <vector>
#include "solution.h"
using namespace std;

/* Fill free to implement any function on here */
int inputSize;

vector<unsigned long long int> leafNode;
struct TreeNode {
    long long int val;
    struct TreeNode *left;
    struct TreeNode *right;
};
TreeNode* root;

vector<unsigned long long int> countLeaf(struct TreeNode* root){
    if(root){
        countLeaf(root->left);
        countLeaf(root->right);
        if(root->left==NULL && root->right==NULL){
            leafNode.push_back(root->val);
        }
    }
    return leafNode;
}

unsigned long long int calPathSum(vector<unsigned long long int> leafNode){
    unsigned long long int resultSum=0;
    for(int i=0; i<leafNode.size(); i++){
        resultSum+=leafNode[i];
    }
    return resultSum;
}

unsigned long long int Solution::getPathSum (struct TreeNode* root)
{
    return calPathSum(countLeaf(root));
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

        TreeNode* newNode[inputSize+1];
        for(int i=1; i<=inputSize; i++){
            newNode[i]=new TreeNode;
        }
        for(int i=1; i<=inputSize; i++){
            if(i*2<inputSize){
                newNode[i]->left=newNode[i*2];
                newNode[i]->right=newNode[i*2+1];
            }
            else if(i*2 == inputSize){
                newNode[i]->left=newNode[i*2];
                newNode[i]->right=NULL;
            }
            else{
                newNode[i]->left=newNode[i]->right=NULL;
            }
        }

        newNode[1]->val=tree[1]->val;
        for(int i=2; i<=inputSize; i++){
            if(i%2==0){
                newNode[i]->val=(newNode[i/2]->val)* 10 + (tree[i]->val);
            }
            else{
                newNode[i]->val=(newNode[(i-1)/2]->val)* 10 + (tree[i]->val);
            }
        }
        root=newNode[1];
    }
    return root;
}
