//Given a BST and an integer K. Find the Kth Smallest element in the BST using O(1) extra space. 
#include <bits/stdc++.h>
using namespace std;
#define MAX_HEIGHT 100000

// Tree Node
struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int val) {
        data = val;
        left = right = NULL;
    }
};

// Function to Build Tree
Node* buildTree(string str) {
    // Corner Case
    if (str.length() == 0 || str[0] == 'N') return NULL;

    // Creating vector of strings from input
    // string after spliting by space
    vector<string> ip;

    istringstream iss(str);
    for (string str; iss >> str;) ip.push_back(str);

    // Create the root of the tree
    Node* root = new Node(stoi(ip[0]));

    // Push the root to the queue
    queue<Node*> queue;
    queue.push(root);

    // Starting from the second element
    int i = 1;
    while (!queue.empty() && i < ip.size()) {

        // Get and remove the front of the queue
        Node* currNode = queue.front();
        queue.pop();

        // Get the current node's value from the string
        string currVal = ip[i];

        // If the left child is not null
        if (currVal != "N") {

            // Create the left child for the current node
            currNode->left = new Node(stoi(currVal));

            // Push it to the queue
            queue.push(currNode->left);
        }

        // For the right child
        i++;
        if (i >= ip.size()) break;
        currVal = ip[i];

        // If the right child is not null
        if (currVal != "N") {

            // Create the right child for the current node
            currNode->right = new Node(stoi(currVal));

            // Push it to the queue
            queue.push(currNode->right);
        }
        i++;
    }

    return root;
}


// } Driver Code Ends
/*Complete the function below

struct Node {
    int data;
    Node *left;
    Node *right;

    Node(int val) {
        data = val;
        left = right = NULL;
    }
};
*/

//Approach 1 : Brute Force : Using Inorder Traversal

class Solution {
  public:
    void inOrder(Node* root, vector<int> &ans){
        if(root != NULL){
            inOrder(root->left, ans);
            ans.push_back(root->data);
            inOrder(root->right, ans);
        }
    }
    // Return the Kth smallest element in the given BST
    int KthSmallestElement(Node *root, int K) {
        vector<int> ans;
        
        //finding inorder traversal
        inOrder(root, ans);
        
        //edge case
        if(K > ans.size()){
            return -1;
        }
        
        return ans[K - 1];
    }
};

//Approach 2 : Optimized Inorder Traversal



//{ Driver Code Starts.
int main() {

    int t;
    string tc;
    getline(cin, tc);
    t = stoi(tc);
    while (t--) {
        string s;
        getline(cin, s);
        Node* root = buildTree(s);

        getline(cin, s);
        int k = stoi(s);
        //  getline(cin, s);
        Solution obj;
        cout << obj.KthSmallestElement(root, k) << endl;
        // cout<<"~"<<endl;
    }
    return 0;
}

//Approach 3 : Using Morris Traversal

class Solution {
  public:
    int res = -1;
    void morrisTraversal(Node *root, int k){
        Node* curr = root;
        
        while(curr != NULL){
            
            //if curr is null
            if(curr->left == NULL){
                k--;
                //target condition
                if(k == 0){
                    res = curr->data;
                    return;
                }
                
                curr = curr->right;
            }
            
            else{
                //find predecessor
                Node* prev = curr->left;
                
                while(prev->right && prev->right != curr){
                    prev = prev->right;
                }
                
                
                //temp link creation
                if(prev->right == NULL){
                    prev->right = curr;
                    curr = curr->left;
                }
                //temp link removed
                else{
                    prev->right = NULL;
                    k--;
                    if(k == 0){
                        res = curr->data;
                        return;
                    }
                    curr = curr->right;
                }
            }
            
        }
    }
    // Return the Kth smallest element in the given BST
    int KthSmallestElement(Node *root, int K) {
        if(root == NULL){
            return -1;
        }
        
        morrisTraversal(root, K);
        
        return res;
    }
};