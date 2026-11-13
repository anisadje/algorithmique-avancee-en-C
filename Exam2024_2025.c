#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*
 * Binary trees - Exam 2024-2025
 *
 * Classic and advanced functions on binary trees and BSTs:
 * - Counting leaves, leaf grandchildren and cherries
 * - Transforming a tree (adding cherries at a given depth)
 * - Checking Fibonacci-type (height-balanced) trees
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

// -------------------- Leaf grandchildren --------------------
// Complexity: O(1)
int NumberOfLeafGrandchildren(Tree A) {
    if (A == NULL) return 0;
    int cpt = 0;

    if (A->left != NULL) {
        if (A->left->left != NULL && A->left->left->left == NULL && A->left->left->right == NULL)
            cpt++;
        if (A->left->right != NULL && A->left->right->left == NULL && A->left->right->right == NULL)
            cpt++;
    }

    if (A->right != NULL) {
        if (A->right->left != NULL && A->right->left->left == NULL && A->right->left->right == NULL)
            cpt++;
        if (A->right->right != NULL && A->right->right->left == NULL && A->right->right->right == NULL)
            cpt++;
    }

    return cpt;
}

// -------------------- Counting cherries --------------------
// A cherry is a node whose two children are leaves
// Complexity: O(n)
int CountCherries(Tree A) {
    if (A == NULL) return 0;

    int isCherry = 0;
    if (A->left != NULL && A->right != NULL) {
        bool leftLeaf = (A->left->left == NULL && A->left->right == NULL);
        bool rightLeaf = (A->right->left == NULL && A->right->right == NULL);
        if (leftLeaf && rightLeaf) isCherry = 1;
    }

    return isCherry + CountCherries(A->left) + CountCherries(A->right);
}

// -------------------- Adding cherries at depth P --------------------
// Every leaf at depth P gets two leaf children (copying its value)
// Complexity: O(n)
void AddCherriesAtDepth(Tree *A, int P) {
    if (*A == NULL) return;

    if (P == 0) {
        if ((*A)->left == NULL && (*A)->right == NULL) {
            (*A)->left = malloc(sizeof(Node));
            (*A)->right = malloc(sizeof(Node));
            if ((*A)->left == NULL || (*A)->right == NULL) {
                perror("malloc");
                exit(EXIT_FAILURE);
            }
            (*A)->left->value = (*A)->value;
            (*A)->right->value = (*A)->value;
            (*A)->left->left = NULL;
            (*A)->left->right = NULL;
            (*A)->right->left = NULL;
            (*A)->right->right = NULL;
        }
        return;
    }

    AddCherriesAtDepth(&((*A)->left), P - 1);
    AddCherriesAtDepth(&((*A)->right), P - 1);
}

// -------------------- Internal nodes >= x in a BST --------------------
// Complexity: O(n)
int CountXOrMoreInBST(Tree A, int x) {
    if (A == NULL) return 0;

    int cpt = 0;
    bool isInternal = (A->left != NULL || A->right != NULL);
    if (isInternal && A->value >= x) cpt = 1;

    if (A->value < x) return CountXOrMoreInBST(A->right, x);
    return cpt + CountXOrMoreInBST(A->left, x) + CountXOrMoreInBST(A->right, x);
}

// -------------------- Leaves equal to 1 --------------------
// Complexity: O(n)
int CountTrueLeaves(Tree A) {
    if (A == NULL) return 0;
    if (A->left == NULL && A->right == NULL) {
        if (A->value == 1) return 1;
        return 0;
    }
    return CountTrueLeaves(A->left) + CountTrueLeaves(A->right);
}

// Counts the leaves equal to 1 at depth P
// Complexity: O(n)
int CountTrueLeavesAtDepth(Tree A, int P) {
    if (A == NULL) return 0;
    if (P == 0) {
        if (A->left == NULL && A->right == NULL) {
            if (A->value == 1) return 1;
            return 0;
        }
        return 0;
    }
    return CountTrueLeavesAtDepth(A->left, P - 1) + CountTrueLeavesAtDepth(A->right, P - 1);
}

// -------------------- Height --------------------
// Complexity: O(n)
int height(Tree A) {
    if (A == NULL) return -1;
    int hl = height(A->left);
    int hr = height(A->right);
    if (hl > hr) return hl + 1;
    return hr + 1;
}

// -------------------- Fibonacci-type tree check --------------------
// (the heights of the two subtrees of every node differ by at most 1)

// Version 1: simple recursion
// Complexity: O(n^2)
bool FibonacciTree_V1(Tree A) {
    if (A == NULL) return true;
    int hl = height(A->left);
    int hr = height(A->right);
    if (hl - hr > 1 || hr - hl > 1) return false;
    return FibonacciTree_V1(A->left) && FibonacciTree_V1(A->right);
}

// Version 2: returns the height and the boolean together
// Complexity: O(n)
void f_V2(Tree A, int *h, bool *isFibo) {
    if (A == NULL) { *h = -1; *isFibo = true; return; }
    int hL, hR; bool fL, fR;
    f_V2(A->left, &hL, &fL);
    f_V2(A->right, &hR, &fR);
    *h = (hL > hR) ? 1 + hL : 1 + hR;
    *isFibo = fL && fR && (hL - hR <= 1 && hR - hL <= 1);
}

// Version 3: one shared boolean (must be set to true by the caller)
// Complexity: O(n)
void f_V3(Tree A, int *h, bool *isFibo) {
    if (A == NULL) { *h = -1; return; }
    int hL, hR;
    f_V3(A->left, &hL, isFibo);
    f_V3(A->right, &hR, isFibo);
    *h = (hL > hR) ? 1 + hL : 1 + hR;
    if (hL - hR > 1 || hR - hL > 1) *isFibo = false;
}

// -------------------- Tests --------------------
int main() {
    // Tree used for the tests
    Tree root = malloc(sizeof(Node));
    root->value = 1;
    root->left = malloc(sizeof(Node));
    root->left->value = 1;
    root->left->left = root->left->right = NULL;
    root->right = malloc(sizeof(Node));
    root->right->value = 0;
    root->right->left = root->right->right = NULL;

    printf("Leaf grandchildren: %d\n", NumberOfLeafGrandchildren(root));
    printf("Cherries: %d\n", CountCherries(root));

    int h;
    bool isFibo = true;
    f_V2(root, &h, &isFibo);
    printf("Tree height: %d\n", h);
    printf("Fibonacci-type tree: %s\n", isFibo ? "Yes" : "No");

    printf("Leaves equal to 1: %d\n", CountTrueLeaves(root));

    // Free memory
    free(root->left);
    free(root->right);
    free(root);

    return 0;
}
