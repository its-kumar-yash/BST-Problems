//{ Driver Code Starts
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

struct Node* deleteNode(struct Node* root, int key);

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

void inorder(Node* root, vector<int>& v) {
    if (root == NULL) return;

    inorder(root->left, v);
    v.push_back(root->data);
    inorder(root->right, v);
}

int main() {

    int t;
    string tc;
    getline(cin, tc);
    t = stoi(tc);
    while (t--) {
        string s;
        getline(cin, s);
        Node* root1 = buildTree(s);
        getline(cin, s);
        int k = stoi(s);
        root1 = deleteNode(root1, k);
        vector<int> v;
        inorder(root1, v);
        for (auto i : v) cout << i << " ";
        cout << endl;
    }
    return 0;
}
// } Driver Code Ends

//function to find minValue 
Node* findMin(Node* root){
    while(root->left != NULL){
        root = root->left;
    }
    
    return root;
}

// Function to delete a node from BST.
Node *deleteNode(Node *root, int X) {
    //base case
    if(root == NULL){
        return root;
    }
    
    //target condition
    if(root->data == X){
        
        // Case 1 : 0 Child
        if(root->left == NULL && root->right == NULL){
            // for leaf node simply delete node and return NULL
            delete root;
            return NULL;
        }
        
        // Case 2 : 1 Child
        
        // 1 left child
        if(root->left != NULL && root->right == NULL){
            //save the left node -> delete root node -> return saved node
            Node* temp = root->left;
            delete root;
            return temp;
        }
        
        // 1 right child
        if(root->left == NULL && root->right != NULL){
            //save the right node -> delete root node -> return saved node
            Node* temp = root->right;
            delete root;
            return temp;
        }
        
        // Case 3 : 2 Child
        if(root->left != NULL && root->right != NULL){
            // find the min value in the right sub tree(inorder successor)
            // replace the root value with successor
            // delete the successor
            int minValue = findMin(root->right)->data;
            root->data = minValue;
            root->right = deleteNode(root->right, minValue);
            return root;
        }
    }
    
    //root's value greater than X , then search in left part
    else if(root->data > X){
        root->left = deleteNode(root->left, X);
        return root;
    }
    //else search in right part
    else{
        root->right = deleteNode(root->right, X);
        return root;
    }
}
