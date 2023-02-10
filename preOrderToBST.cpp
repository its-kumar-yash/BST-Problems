// Given an array arr[] of N nodes representing preorder traversal of some BST. You have to build the exact BST from it's given preorder traversal.
// In Pre-Order traversal, the root node is visited before the left child and right child nodes.

/* A O(n) iterative program for construction of BST from preorder traversal */
#include <bits/stdc++.h>
using namespace std;

/* A binary tree node has data, pointer to left child
   and a pointer to right child */
typedef struct Node
{
    int data;
    struct Node *left, *right;
} Node;

// A Stack has array of Nodes, capacity, and top
typedef struct Stack
{
    int top;
    int capacity;
    Node **array;
} Stack;

// A utility function to create a new tree node
Node *newNode(int data)
{
    Node *temp = (Node *)malloc(sizeof(Node));
    temp->data = data;
    temp->left = temp->right = NULL;
    return temp;
}

// A utility function to create a stack of given capacity
Stack *createStack(int capacity)
{
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    stack->top = -1;
    stack->capacity = capacity;
    stack->array = (Node **)malloc(stack->capacity * sizeof(Node *));
    return stack;
}

// A utility function to check if stack is full
int isFull(Stack *stack)
{
    return stack->top == stack->capacity - 1;
}

// A utility function to check if stack is empty
int isEmpty(Stack *stack)
{
    return stack->top == -1;
}

// A utility function to push an item to stack
void push(Stack *stack, Node *item)
{
    if (isFull(stack))
        return;
    stack->array[++stack->top] = item;
}

// A utility function to remove an item from stack
Node *pop(Stack *stack)
{
    if (isEmpty(stack))
        return NULL;
    return stack->array[stack->top--];
}

// A utility function to get top node of stack
Node *peek(Stack *stack)
{
    return stack->array[stack->top];
}

bool canRepresentBST(int pre[], int n)
{
    // Create an empty stack
    stack<int> s;

    // Initialize current root as minimum possible
    // value
    int root = INT_MIN;

    // Traverse given array
    for (int i = 0; i < n; i++)
    {
        // If we find a node who is on right side
        // and smaller than root, return false
        if (pre[i] < root)
            return false;

        // If pre[i] is in right subtree of stack top,
        // Keep removing items smaller than pre[i]
        // and make the last removed item as new
        // root.
        while (!s.empty() && s.top() < pre[i])
        {
            root = s.top();
            s.pop();
        }

        // At this point either stack is empty or
        // pre[i] is smaller than root, push pre[i]
        s.push(pre[i]);
    }
    return true;
}

// A utility function to print postorder traversal of a Binary Tree
void printPostorder(Node *node)
{
    if (node == NULL)
        return;
    printPostorder(node->left);
    printPostorder(node->right);
    printf("%d ", node->data);
}

// } Driver Code Ends
// User function template in C++

/*

typedef struct Node
{
    int data;
    struct Node *left, *right;
} Node;


// A utility function to create a new tree node
Node* newNode( int data )
{
    Node* temp = (Node *)malloc( sizeof( Node ) );
    temp->data = data;
    temp->left = temp->right = NULL;
    return temp;
}

*/

// Approach 1 - using max & min

class Solution
{
public:
    Node *solve(int pre[], int n, int mini, int maxi, int &idx)
    {

        // base case
        if (idx >= n || pre[idx] < mini || pre[idx] > maxi)
        {
            return NULL;
        }

        Node *root = newNode(pre[idx]);
        idx = idx + 1;
        root->left = solve(pre, n, mini, root->data, idx);
        root->right = solve(pre, n, root->data, maxi, idx);

        return root;
    }
    // Function that constructs BST from its preorder traversal.
    Node *post_order(int pre[], int size)
    {
        int mini = INT_MIN;
        int maxi = INT_MAX;
        int idx = 0;

        return solve(pre, size, mini, maxi, idx);
    }
};

//{ Driver Code Starts.

int main()
{
    // Note that size of arr[] is considered 100 according to
    // the constraints mentioned in problem statement.
    int arr[1000], x, t, n;

    // Input the number of test cases you want to run
    cin >> t;

    // One by one run for all input test cases
    while (t--)
    {
        // Input the size of the array
        cin >> n;

        // Input the array
        for (int i = 0; i < n; i++)
            cin >> arr[i];

        Solution ob;
        printPostorder(ob.post_order(arr, n));
        cout << endl;
    }
    return 0;
}


//Approach 2 - Using Only MAx
class Solution
{
public:
    // Function that constructs BST from its preorder traversal.
    Node *solve(int pre[], int n, int &i, int max)

    {

        if (i >= n || pre[i] > max)

            return NULL;

        Node *root = newNode(pre[i++]);

        root->left = solve(pre, n, i, root->data);

        root->right = solve(pre, n, i, max);

        return root;
    }

    // Function that constructs BST from its preorder traversal.

    Node *post_order(int pre[], int size)

    {

        int i = 0;

        return solve(pre, size, i, INT_MAX);

        // code here
    }
};