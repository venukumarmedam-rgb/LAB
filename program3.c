#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *left, *right;
};

struct Node* newNode(int val) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = val;
    node->left = node->right = NULL;
    return node;
}

struct Node* insert(struct Node* root, int val) {
    if(root == NULL) return newNode(val);
    if(val < root->data) root->left = insert(root->left, val);
    else if(val > root->data) root->right = insert(root->right, val);
    return root;
}

struct Node* minValueNode(struct Node* node) {
    struct Node* curr = node;
    while(curr->left) curr = curr->left;
    return curr;
}

struct Node* deleteNode(struct Node* root, int key) {
    if(root == NULL) return root;
    if(key < root->data) root->left = deleteNode(root->left, key);
    else if(key > root->data) root->right = deleteNode(root->right, key);
    else {
        if(root->left == NULL) {
            struct Node* temp = root->right;
            free(root);
            return temp;
        }
        else if(root->right == NULL) {
            struct Node* temp = root->left;
            free(root);
            return temp;
        }
        struct Node* temp = minValueNode(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}

int main() {
    struct Node* root = NULL;
    int n, i, val, del;

    printf("Enter number of nodes: ");
    scanf("%d", &n);

    printf("Enter %d values:\n", n);
    for(i = 0; i < n; i++) {
        scanf("%d", &val);
        root = insert(root, val);
    }

    printf("Enter value to delete: ");
    scanf("%d", &del);
    root = deleteNode(root, del);

    return 0;
}