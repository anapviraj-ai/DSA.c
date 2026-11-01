
#include <stdio.h>
#include <stdlib.h>

// Structure of BST node
struct Node {
    int data;
    struct Node *left, *right;
};

// Create a new node
struct Node* createNode(int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));

    newNode->data = value;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

// Insert a node
struct Node* insert(struct Node* root, int value) {
    if (root == NULL) {
        return createNode(value);
    }

    if (value < root->data) {
        root->left = insert(root->left, value);
    }
    else if (value > root->data) {
        root->right = insert(root->right, value);
    }
    else {
        printf("Duplicate value not allowed!\n");
    }

    return root;
}

// Find height of tree
int findHeight(struct Node* root) {
    if (root == NULL) {
        return 0;
    }

    int leftHeight = findHeight(root->left);
    int rightHeight = findHeight(root->right);

    return (leftHeight > rightHeight ?
            leftHeight : rightHeight) + 1;
}

// Find minimum value
int findMin(struct Node* root) {
    if (root == NULL) {
        return -1;
    }

    while (root->left != NULL) {
        root = root->left;
    }

    return root->data;
}

// Mirror the tree
void mirrorTree(struct Node* root) {
    if (root == NULL) {
        return;
    }

    struct Node* temp = root->left;
    root->left = root->right;
    root->right = temp;

    mirrorTree(root->left);
    mirrorTree(root->right);
}

// Search a value
int search(struct Node* root, int key) {
    if (root == NULL) {
        return 0;
    }

    if (root->data == key) {
        return 1;
    }

    return search(root->left, key) ||
           search(root->right, key);
}

// Inorder traversal
void inorder(struct Node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

// Main function
int main() {
    struct Node* root = NULL;
    int choice, value, key;

    do {
        printf("\n\n===== BINARY SEARCH TREE =====\n");
        printf("1. Insert New Node\n");
        printf("2. Find Number of Nodes in Longest Path\n");
        printf("3. Find Minimum Value\n");
        printf("4. Mirror the Tree\n");
        printf("5. Search a Value\n");
        printf("6. Display Inorder Traversal\n");
        printf("7. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {

            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &value);

                root = insert(root, value);
                printf("Node inserted successfully.\n");
                break;

            case 2:
                if (root == NULL) {
                    printf("Tree is empty.\n");
                }
                else {
                    printf("Number of nodes in longest path: %d\n",
                           findHeight(root));
                }
                break;

            case 3:
                if (root == NULL) {
                    printf("Tree is empty.\n");
                }
                else {
                    printf("Minimum value in BST: %d\n",
                           findMin(root));
                }
                break;

            case 4:
                if (root == NULL) {
                    printf("Tree is empty.\n");
                }
                else {
                    mirrorTree(root);
                    printf("Tree mirrored successfully.\n");
                }
                break;

            case 5:
                printf("Enter value to search: ");
                scanf("%d", &key);

                if (search(root, key)) {
                    printf("%d found in the tree.\n", key);
                }
                else {
                    printf("%d not found in the tree.\n", key);
                }
                break;

            case 6:
                if (root == NULL) {
                    printf("Tree is empty.\n");
                }
                else {
                    printf("Inorder Traversal: ");
                    inorder(root);
                    printf("\n");
                }
                break;

            case 7:
                printf("Exiting program.\n");
                break;

            default:
                printf("Invalid choice! Please try again.\n");
        }

    } while (choice != 7);

    return 0;
}
