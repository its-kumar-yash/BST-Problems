//Given two BSTs, return elements of both BSTs in sorted form.


//Amazon MicroSoft Google


#include <bits/stdc++.h>
using namespace std;
#define MAX_HEIGHT 100000

// Tree Node
struct Node {
    int data;
    Node *left;
    Node *right;

    Node(int val) {
        data = val;
        left = right = NULL;
    }
};





// Function to Build Tree
Node* buildTree(string str)
{
   // Corner Case
   if(str.length() == 0 || str[0] == 'N')
       return NULL;

   // Creating vector of strings from input
   // string after spliting by space
   vector<string> ip;

   istringstream iss(str);
   for(string str; iss >> str; )
       ip.push_back(str);

   // Create the root of the tree
   Node* root = new Node(stoi(ip[0]));

   // Push the root to the queue
   queue<Node*> queue;
   queue.push(root);

   // Starting from the second element
   int i = 1;
   while(!queue.empty() && i < ip.size()) {

       // Get and remove the front of the queue
       Node* currNode = queue.front();
       queue.pop();

       // Get the current node's value from the string
       string currVal = ip[i];

       // If the left child is not null
       if(currVal != "N") {

           // Create the left child for the current node
           currNode->left = new Node(stoi(currVal));

           // Push it to the queue
           queue.push(currNode->left);
       }

       // For the right child
       i++;
       if(i >= ip.size())
           break;
       currVal = ip[i];

       // If the right child is not null
       if(currVal != "N") {

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
/*
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

//Approach 1 - Brute Force - TC - O(NlogN), SC - O(N)

class Solution
{
    public:
    void inOrder(Node* root, vector<int> &ans){
        if(root != NULL){
            inOrder(root->left, ans);
            ans.push_back(root->data);
            inOrder(root->right, ans);
        }
    }
    //Function to return a list of integers denoting the node 
    //values of both the BST in a sorted order.
    vector<int> merge(Node *root1, Node *root2)
    {
       vector<int> BST;
       
       inOrder(root1, BST);
       inOrder(root2, BST);
       
       sort(BST.begin(), BST.end());
       
       return BST;
       
    }
};


//Approach 2 - Store Inorder -> merge 2 sorted arr -> inorder to bst
// TC --> O(M + N) , SC --> O(M + N) 

class Solution
{
    public:
    //function to store inorder of bst
    void inOrder(Node* root, vector<int> &ans){
        if(root != NULL){
            inOrder(root->left, ans);
            ans.push_back(root->data);
            inOrder(root->right, ans);
        }
    }
    
    //function to merge two sorted array
    vector<int> mergeArray(vector<int> arr1, vector<int> arr2){
        vector<int> ans;
        
        int n = arr1.size(), m = arr2.size();
        
        int i = 0, j = 0;
        
        while(i < n && j < m){
            if(arr1[i] <= arr2[j]){
                ans.push_back(arr1[i++]);
            }
            else{
                ans.push_back(arr2[j++]);
            }
        }
        
        
        while(i < n){
            ans.push_back(arr1[i++]);
        }
        
        while(j < m){
            ans.push_back(arr2[j++]);
        }
        
        
        return ans;
    }
    
    //function to convert inorder to balanced bst
    Node* inorderToBST(vector<int> &arr, int s, int e){
        //base case
        if(s > e){
            return NULL;
        }
        
        int mid = s + (e - s)/2;
        Node* root = new Node(arr[mid]);
        root->left = inorderToBST(arr, s, mid - 1);
        root->right = inorderToBST(arr, mid + 1, e);
        
        return root;
    }
    
    vector<int> merge(Node *root1, Node *root2)
    {
       vector<int> inorder1, inorder2;
       
       //step 1 - store inorder of both bst 
       inOrder(root1, inorder1);
       inOrder(root2, inorder2);
       
       //step 2 - merge 2 sorted arr
       vector<int> mergedInorder = mergeArray(inorder1, inorder2);
       
       //step 3 - inorder to bst
       Node* root = inorderToBST(mergedInorder, 0, mergedInorder.size() - 1);
       
       vector<int> ans;
       inOrder(root, ans);
       
       return ans;
    }
};


//Approach #3 - Optimized Approach


class Solution
{
    public:
    
    void convertIntoSortedDLL(Node* root, Node* &head){
        //base case
        if(root == NULL){
            return ;
        }
        
        convertIntoSortedDLL(root->left, head);
        
        root->right = head;
        head->left = root;
        
        head = root;
        
        convertIntoSortedDLL(root->right, head);
    }
    
    int countNode(Node* head){
        int cnt = 0;
        
        while(head != NULL){
            cnt++;
            head = head->right;
        }
        
        return cnt;
    }
    
    
    Node* sortedLLToBST(Node* &head, int n){
        
        if(n <= 0 || head == NULL){
            return NULL;
        }
        
        Node* left = sortedLLToBST(head, n/2);
        
        Node* root = head;
        root->left = left;
        
        head = head->right;
        
        root->right = sortedLLToBST(head, n - n/2 - 1);
        
        return root;
        
    }
    
    
    Node* mergeLL(Node* head1, Node* head2){
        
        Node* head = NULL;
        Node* tail = NULL;
        
        while(head1 != NULL && head2 != NULL){
            
            if(head1->data < head2->data){
                if(head == NULL){
                    head = head1;
                    tail = head1;
                    head1 = head1->right;
                }
                else{
                    //insert at end
                    tail->right = head1;
                    head1->left = tail;
                    tail = head1;
                    head1 = head1->right;
                }
            }
            else{
                if(head == NULL){
                    head = head2;
                    tail = head2;
                    head2 = head2->right;
                }
                else{
                    tail->right = head2;
                    head2->left = tail;
                    tail = head2;
                    head2 = head2->right;
                }
            }
        }
        
        while(head1 != NULL){
            tail->right = head1;
            head1->left = tail;
            tail = head1;
            head1 = head1->right;
        }
        
        while(head2 != NULL){
            tail->right = head2;
            head2->left = tail;
            tail = head2;
            head2 = head2->right;
        }
        
       return head;
       
       
    }
    
    
    
    Node* merge(Node *root1, Node *root2)
    {   
        Node* head1 = NULL;
        convertIntoSortedDLL(root1, head1);
        head1->left = NULL;
        
        Node* head2 = NULL;
        convertIntoSortedDLL(root2, head2);
        head2->left = NULL;
        
        
        
        Node* head = mergeLL(head1, head2);
        
        int n = countNode(head);
        return sortedLLToBST(head, n);
        
    }
};



