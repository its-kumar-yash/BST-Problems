#include<bits/stdc++.h>
using namespace std;

class Node{
    public:
    int data;
    Node* left;
    Node* right;

    Node(int data){
        this->data = data;
        this->left = NULL;
        this->right = NULL;
    }
};

//function to insert into BST
Node* insertIntoBST(Node* root, int data){
    //base case
    if(root == NULL){
        root = new Node(data);
        return root;
    }

    if(root->data > data){
        //insert into left sub tree
        root->left = insertIntoBST(root->left, data);
    }
    else{
        //insert into right sub tree
        root->right = insertIntoBST(root->right, data);
    }

    return root;
}

void takeInput(Node* &root){
    int data;
    cin >> data;

    while(data != -1){
        root = insertIntoBST(root, data);
        cin >> data;
    }
}

void inOrder(Node* root){
    //base case
    if(root == NULL){
        return;
    }

    //Left -> Node -> Right
    inOrder(root->left);
    cout<<root->data<<" ";
    inOrder(root->right);
}

int main(){
    Node* root = NULL;

    cout<<"Enter Node Data"<<endl;

    takeInput(root);

    cout<<"Printing BST : "<<endl;

    inOrder(root);

    return 0;
}