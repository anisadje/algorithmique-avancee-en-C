#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*
 * Binary trees - exercises
 *
 * Essential functions on binary trees:
 * - Creating nodes
 * - Traversals (iterative and recursive)
 * - Counting nodes with given properties
 * - Checking tree properties (full, mirror)
 *
 * The time complexity of each function is given.
 */

// -------------------- Structure --------------------
typedef struct Node {
    int value;
    struct Node *left;  // left subtree
    struct Node *right; // right subtree
} Node;

typedef Node *Tree; // a Tree is a pointer to its root

// -------------------- Helpers --------------------

/**
 * @brief Returns the maximum of two integers
 * @param a First integer
 * @param b Second integer
 * @return int The maximum
 * Complexity: O(1)
 */
int maximum(int a, int b){
    if(a > b) return a;
    return b;
}

// -------------------- Creating nodes --------------------

/**
 * @brief Creates a node with its subtrees
 * @param L Left subtree
 * @param R Right subtree
 * @param v Value of the node
 * @return Tree The new node
 * Complexity: O(1)
 */
Tree createNodeWithChildren(Tree L, Tree R, int v){
    Tree tmp = (Tree)malloc(sizeof(Node));
    if(tmp == NULL){
        perror("Memory allocation error");
        exit(EXIT_FAILURE);
    }
    tmp->value = v;
    tmp->left = L;
    tmp->right = R;
    return tmp;
}

/**
 * @brief Creates a node without children (a leaf)
 * @param v Value of the node
 * @return Tree The new leaf
 * Complexity: O(1)
 */
Tree createLeaf(int v){
    return createNodeWithChildren(NULL, NULL, v);
}

/**
 * @brief Frees every node of a tree
 * @param root Root of the tree
 * Complexity: O(n)
 */
void destroyTree(Tree root){
    if(root == NULL) return;
    destroyTree(root->left);
    destroyTree(root->right);
    free(root);
}

// -------------------- Height --------------------

/**
 * @brief Computes the height of a tree
 * @param root Root of the tree
 * @return int Height
 * Complexity: O(n)
 */
int height(Tree root){
    if(root == NULL) return 0;
    return 1 + maximum(height(root->left), height(root->right));
}

// -------------------- Mirror --------------------

/**
 * @brief Returns a new tree, mirror of the given one
 * @param root Root of the original tree
 * @return Tree Root of the mirror
 * Complexity: O(n)
 */
Tree Fmirror(Tree root){
    if(root == NULL) return NULL;
    Tree mirror_R = Fmirror(root->right);
    Tree mirror_L = Fmirror(root->left);
    return createNodeWithChildren(mirror_R, mirror_L, root->value);
}

/**
 * @brief Turns the tree into its mirror (in place)
 * @param root Root of the tree
 * Complexity: O(n)
 */
void Pmirror(Tree root){
    if(root == NULL) return;
    Tree tmp = root->left;
    root->left = root->right;
    root->right = tmp;
    Pmirror(root->left);
    Pmirror(root->right);
}

/**
 * @brief Checks whether two trees are mirrors of each other
 * @param A1 First root
 * @param A2 Second root
 * @return true if they are mirrors, false otherwise
 * Complexity: O(n)
 */
bool AreMirrors(Tree A1, Tree A2){
    if(A1 == NULL && A2 == NULL) return true;
    if(A1 == NULL || A2 == NULL || A1->value != A2->value) return false;
    return AreMirrors(A1->left, A2->right) && AreMirrors(A1->right, A2->left);
}

// -------------------- Stack --------------------
typedef struct StackElement{
    Tree ptr;
    struct StackElement *next;
} StackElement;

typedef struct {
    StackElement *top;
} Stack;

Stack *create_stack(){
    Stack *S = (Stack*)malloc(sizeof(Stack));
    if(S == NULL){
        perror("Stack allocation error");
        exit(EXIT_FAILURE);
    }
    S->top = NULL;
    return S;
}

bool isEmpty(Stack *S){
    return S->top == NULL;
}

void push(Stack *S, Tree root){
    StackElement *new_element = (StackElement*)malloc(sizeof(StackElement));
    if(new_element == NULL){
        perror("StackElement allocation error");
        exit(EXIT_FAILURE);
    }
    new_element->ptr = root;
    new_element->next = S->top;
    S->top = new_element;
}

Tree pop(Stack *S){
    if(isEmpty(S)) return NULL;
    StackElement *tmp = S->top;
    Tree root = tmp->ptr;
    S->top = tmp->next;
    free(tmp);
    return root;
}

// -------------------- Iterative preorder printing --------------------
/**
 * @brief Prints the tree in preorder, iteratively
 * @param root Root of the tree
 * Complexity: O(n)
 */
void PrintPreorder(Tree root){
    if(root == NULL) return;
    Stack *stack = create_stack();
    push(stack, root);

    while(!isEmpty(stack)){
        Tree X = pop(stack);
        printf("%d ", X->value);
        if(X->right) push(stack, X->right);
        if(X->left) push(stack, X->left);
    }
    printf("\n");
    free(stack);
}

// -------------------- Counting --------------------

int CountNoAncestor(Tree root){
    if(!root || root->value == 0) return 0;
    int leftVal = (root->left && root->left->value);
    int rightVal = (root->right && root->right->value);
    if(!leftVal && !rightVal)
        return 1 + CountNoAncestor(root->left) + CountNoAncestor(root->right);
    else
        return CountNoAncestor(root->left) + CountNoAncestor(root->right);
}

int CountNoDescendant(Tree root){
    if(!root || root->value == 0) return 0;
    int left_val = (root->left && root->left->value);
    int right_val = (root->right && root->right->value);
    if(!left_val && !right_val)
        return 1 + CountNoDescendant(root->left) + CountNoDescendant(root->right);
    else
        return CountNoDescendant(root->left) + CountNoDescendant(root->right);
}

int CountHeightEqualsDepth(Tree root, int current_depth, int total_height){
    if(!root) return 0;
    int count = 0;
    if(root->value && (total_height - current_depth == 1)) count = 1;
    count += CountHeightEqualsDepth(root->left, current_depth + 1, total_height);
    count += CountHeightEqualsDepth(root->right, current_depth + 1, total_height);
    return count;
}

bool IsFull(Tree root){
    if(!root) return true;
    if((root->left == NULL) != (root->right == NULL)) return false;
    return IsFull(root->left) && IsFull(root->right);
}

// -------------------- Tests --------------------
int main() {
    // Small binary tree
    Tree root = createLeaf(1);
    root->left = createLeaf(0);
    root->right = createLeaf(1);
    root->right->left = createLeaf(1);
    root->right->right = createLeaf(0);

    printf("Height: %d\n", height(root));
    printf("CountNoAncestor: %d\n", CountNoAncestor(root));
    printf("CountNoDescendant: %d\n", CountNoDescendant(root));

    int h = height(root);
    printf("CountHeightEqualsDepth: %d\n", CountHeightEqualsDepth(root, 0, h));
    printf("IsFull: %s\n", IsFull(root) ? "True" : "False");

    printf("Preorder: ");
    PrintPreorder(root);

    destroyTree(root);

    return 0;
}
