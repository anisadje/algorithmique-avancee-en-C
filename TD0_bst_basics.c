#include <stdio.h>
#include <stdlib.h>

/*
 * The basic code to master for this course.
 * Classic operations on binary search trees:
 * creation, insertion, search, traversals and deletion.
 */

// -------------------- Structure --------------------
typedef struct Node {
    int value;
    struct Node *left;   // left subtree
    struct Node *right;  // right subtree
} Node;

typedef Node *Tree; // a Tree is a pointer to its root

// -------------------- Creating a node --------------------
Tree createNode(int v){
    Tree new_node = (Tree)malloc(sizeof(Node));
    if (new_node != NULL) {
        new_node->value = v;
        new_node->left = NULL;
        new_node->right = NULL;
    }
    return new_node;
}

// -------------------- Insertion in a BST --------------------
Tree insert(Tree root, int v){
    if (root == NULL){
        return createNode(v);
    }

    if(v < root->value){
        root->left = insert(root->left, v);
    } else if(v > root->value){
        root->right = insert(root->right, v);
    }
    // If v == root->value, nothing is done (no duplicates)
    return root;
}

// -------------------- Searching a value --------------------
Tree search(Tree root, int v){
    if(root == NULL || root->value == v){
        return root;
    }
    if(v > root->value){
        return search(root->right, v);
    } else {
        return search(root->left, v);
    }
}

// -------------------- Height and depth --------------------
int maximum(int a, int b){
    return (a > b) ? a : b;
}

// Height of the tree (number of levels - 1)
int height(Tree root){
    if(root == NULL) return -1;
    return 1 + maximum(height(root->left), height(root->right));
}

// Depth of a node, starting from the root
int depth(Tree root, int v, int level){
    if(root == NULL) return -1;
    if(root->value == v) return level;

    int res_left = depth(root->left, v, level + 1);
    if(res_left != -1) return res_left;

    return depth(root->right, v, level + 1);
}

// -------------------- Minimum --------------------
Tree findMin(Tree root){
    while(root && root->left != NULL){
        root = root->left;
    }
    return root;
}

// -------------------- Traversals --------------------
void visitPreorder(Tree root){
    if(root == NULL) return;
    printf("%d ", root->value);     // root
    visitPreorder(root->left);      // left subtree
    visitPreorder(root->right);     // right subtree
}

void visitInorder(Tree root){
    if(root == NULL) return;
    visitInorder(root->left);       // left subtree
    printf("%d ", root->value);     // root
    visitInorder(root->right);      // right subtree
}

void visitPostorder(Tree root){
    if(root == NULL) return;
    visitPostorder(root->left);     // left subtree
    visitPostorder(root->right);    // right subtree
    printf("%d ", root->value);     // root
}

// -------------------- Deleting a node --------------------
Tree deleteNode(Tree root, int v){
    if(root == NULL) return root;

    if(v < root->value){
        root->left = deleteNode(root->left, v);
    } else if(v > root->value){
        root->right = deleteNode(root->right, v);
    } else {
        // Case 1: no child or one child
        if(root->left == NULL){
            Tree temp = root->right;
            free(root);
            return temp;
        } else if(root->right == NULL){
            Tree temp = root->left;
            free(root);
            return temp;
        }
        // Case 2: two children
        Tree temp = findMin(root->right);
        root->value = temp->value;
        root->right = deleteNode(root->right, temp->value);
    }
    return root;
}

// -------------------- Destroying the tree --------------------
void destroyTree(Tree root){
    if(root != NULL){
        destroyTree(root->left);
        destroyTree(root->right);
        free(root);
    }
}

// -------------------- Example --------------------
int main(){
    Tree root = NULL;

    // Insert values
    root = insert(root, 50);
    root = insert(root, 30);
    root = insert(root, 70);
    root = insert(root, 20);
    root = insert(root, 40);
    root = insert(root, 60);
    root = insert(root, 80);

    printf("Preorder: ");
    visitPreorder(root);
    printf("\n");

    printf("Inorder: ");
    visitInorder(root);
    printf("\n");

    printf("Postorder: ");
    visitPostorder(root);
    printf("\n");

    printf("Tree height: %d\n", height(root));
    printf("Depth of node 40: %d\n", depth(root, 40, 0));

    // Delete a node
    root = deleteNode(root, 70);
    printf("Inorder after deleting 70: ");
    visitInorder(root);
    printf("\n");

    destroyTree(root);

    return 0;
}
