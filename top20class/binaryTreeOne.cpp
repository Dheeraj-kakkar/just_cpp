#include<iostream>
#include<vector>

using namespace std;

#include"btreeUtil.h" // std is being used inside this header file

using namespace bTreeUtil;

/*
Problem Statement:
	Find the sum of all left leaves in a given binary tree.


   3
   / \
  9  20
    /  \
   15   7

There are two left leaves in the binary tree, with values 9 and 15 respectively. Return 24.
*/

/*
    Using Recursion:

    Test this code in LeetCode Problem

    TC: O(n), SC: O(n) --> n * (stack size)
*/

struct QueueNode {
    struct BTree *root;
    bool isLeft;
};

class TreeLeftLeafSum {
   
    public:

        int treeLeftLeafSum1(struct BTree *root, bool isLeft) {

            int sum = 0;

            if(root == NULL) return 0;
            
            if(root->left == NULL && root->right == NULL) {
                if(isLeft)
                    return root->data;
                else
                    return 0;
            }

            sum+=treeLeftLeafSum1(root->left, true);
            sum+=treeLeftLeafSum1(root->right, false);

            return sum;
        }

// Done TODO: Tested on One Child Tree, Need to see if multiple nodes at same level. It will fail because tmp->root is getting modified again for right child
        int treeLeftLeafSum2(BTree *root) {
            
            int sum = 0;
            bool isLeft = false;
            vector<struct QueueNode *> queue;

            BTree *leftChild = NULL;
            BTree *rightChild = NULL;

            QueueNode *tmp = new QueueNode;
            tmp->isLeft = isLeft;
            tmp->root = root;
            queue.push_back(tmp);

            while(!queue.empty()) {
                tmp = queue.front();

                isLeft = tmp->isLeft;
                leftChild = tmp->root->left;
                rightChild = tmp->root->right;
                queue.erase(queue.begin());

                if(isLeft) {
                    if(leftChild == NULL && rightChild == NULL) {
                        sum+=tmp->root->data;
                    }
                }

                delete tmp; // Can Free this Memory
                tmp = nullptr; // To avoid Dangling Behaviour

                if(leftChild != NULL) {
                    tmp = new QueueNode;
                    tmp->isLeft = true;
                    tmp->root = leftChild;
                    queue.push_back(tmp);
                }

                //if(tmp->root->right != NULL) {    Not Using Because root was getting modified in prev if statement
                if(rightChild != NULL) {
                    tmp = new QueueNode;
                    tmp->isLeft = false;
                    tmp->root = rightChild;
                    queue.push_back(tmp);
                }
            }
            return sum;
         }
};

int main() {
    
    TreeLeftLeafSum *obj = new TreeLeftLeafSum(); 

    cout << "Enter Size of Tree" << endl;
    cin >> bTreeUtil::size; // Part of Namespace bTreeUtil

    //createOneChildTree();
    createRandomTree();
    displayTree(bTreeUtil::root);

    cout << "Sum of Left Leaf Nodes is : " << obj->treeLeftLeafSum1(bTreeUtil::root, false) << endl;
    cout << "Sum of Left Leaf Nodes is : " << obj->treeLeftLeafSum2(bTreeUtil::root) << endl;

    return 0;
}

