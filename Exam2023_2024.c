#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*
 * Binary trees - Exam 2023-2024
 *
 * Classic and advanced functions on binary trees and BSTs:
 * - Detecting leaves and internal nodes
 * - Counting nodes at a given depth or height
 * - Checking BSTs and specific tree shapes
 * - Simplifying a tree
 *
 * The time complexity of each function is given.
 */

// -------------------- Structure --------------------
typedef struct Node {
    int value;
    struct Node *left;  // left subtree
    struct Node *right; // right subtree
} Node;

typedef Node *Tree;

// -------------------- Helpers --------------------

// Checks whether a node is a leaf
// Complexity: O(1)
bool isLeaf(Tree a) {
    if (a != NULL && a->left == NULL && a->right == NULL) return true;
    return false;
}

// Checks whether a node is internal (not a leaf)
// Complexity: O(1)
bool isInternal(Tree a) {
    if (a != NULL && (a->left != NULL || a->right != NULL)) return true;
    return false;
}

// Counts the internal nodes of a tree
// Complexity: O(n)
int countInternal(Tree a) {
    if (a == NULL || isLeaf(a)) return 0;
    return 1 + countInternal(a->left) + countInternal(a->right);
}

// Checks whether the tree has at least three internal nodes
// Complexity: O(n)
bool AtLeastThreeInternalNodes(Tree a) {
    int nb = countInternal(a);
    if (nb >= 3) return true;
    return false;
}

// -------------------- Comparison and pruning --------------------

// Checks whether a1 is a pruning of a2
// Complexity: O(n)
bool Pruning(Tree a1, Tree a2) {
    if (a1 == NULL) return true;
    if (a2 == NULL) return false;

    if (isLeaf(a1)) return true;

    if (a1->value != a2->value) return false;

    return Pruning(a1->left, a2->left) && Pruning(a1->right, a2->right);
}

// Checks whether every leaf has value 1
// Complexity: O(n)
bool ALLWHITE(Tree a) {
    if (a == NULL) return true;
    if (isLeaf(a)) {
        if (a->value == 1) return true;
        return false;
    }

    if (ALLWHITE(a->left) && ALLWHITE(a->right)) return true;
    return false;
}

// -------------------- Simplification --------------------

// Simplifies the tree: when the two children of a node are leaves of the
// same color, they are removed and the node becomes a leaf of that color
// Complexity: O(n)
void SIMPLIFY(Tree *a) {
    if (*a == NULL || isLeaf(*a)) return;

    SIMPLIFY(&((*a)->left));
    SIMPLIFY(&((*a)->right));

    if (isLeaf((*a)->left) && isLeaf((*a)->right)) {
        if ((*a)->left->value == (*a)->right->value) {
            int color = (*a)->left->value;
            free((*a)->left);
            free((*a)->right);
            (*a)->left = NULL;
            (*a)->right = NULL;
            (*a)->value = color;
        }
    }
}

// -------------------- Counting internal nodes --------------------

// Counts the internal nodes at depth p
// Complexity: O(n)
int CountInternalNodesAtDepth(Tree a, int p) {
    if (a == NULL) return 0;
    if (p == 0) {
        if (isInternal(a)) return 1;
        return 0;
    }
    return CountInternalNodesAtDepth(a->left, p - 1) +
           CountInternalNodesAtDepth(a->right, p - 1);
}

// Counts the internal nodes at height h
// Complexity: O(n)
void checkHeight(Tree a, int target_h, int *node_h, int *nb) {
    if (a == NULL) {
        *node_h = -1;
        return;
    }

    int hL = -1, hR = -1;
    checkHeight(a->left, target_h, &hL, nb);
    checkHeight(a->right, target_h, &hR, nb);

    if (hL > hR) *node_h = 1 + hL;
    else *node_h = 1 + hR;

    if (*node_h == target_h && isInternal(a)) (*nb)++;
}

int CountInternalNodesAtHeight(Tree a, int h) {
    int h_res = 0, nb = 0;
    checkHeight(a, h, &h_res, &nb);
    return nb;
}

// -------------------- Searching a BST --------------------

// Counts the nodes equal to x in a BST
// Complexity: O(n) for an unbalanced tree, O(log n) for a balanced BST
int CountXInBST(Tree a, int x) {
    if (a == NULL) return 0;
    if (a->value == x)
        return 1 + CountXInBST(a->left, x) + CountXInBST(a->right, x);
    if (x < a->value) return CountXInBST(a->left, x);
    return CountXInBST(a->right, x);
}

// Checks that a tree is a BST (helper with bounds)
// Complexity: O(n)
bool isBST_rec(Tree a, long min, long max) {
    if (a == NULL) return true;
    if (a->value <= min || a->value >= max) return false;
    return isBST_rec(a->left, min, a->value) &&
           isBST_rec(a->right, a->value, max);
}

// Checks whether a tree is a BST
// Complexity: O(n)
bool IsBST(Tree a) {
    return isBST_rec(a, -2147483648L, 2147483647L);
}

// -------------------- Example --------------------
int main() {
    // Small binary tree for testing
    Tree root = malloc(sizeof(Node));
    root->value = 10;
    root->left = malloc(sizeof(Node));
    root->left->value = 5;
    root->left->left = root->left->right = NULL;
    root->right = malloc(sizeof(Node));
    root->right->value = 15;
    root->right->left = root->right->right = NULL;

    printf("At least 3 internal nodes: %s\n", AtLeastThreeInternalNodes(root) ? "Yes" : "No");
    printf("Tree is a BST: %s\n", IsBST(root) ? "Yes" : "No");

    printf("Nodes equal to 5 in the BST: %d\n", CountXInBST(root, 5));
    printf("Internal nodes at depth 1: %d\n", CountInternalNodesAtDepth(root, 1));
    printf("Internal nodes at height 1: %d\n", CountInternalNodesAtHeight(root, 1));

    // Free memory
    free(root->left);
    free(root->right);
    free(root);

    return 0;
}
