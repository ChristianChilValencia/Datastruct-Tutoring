#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define a structure for a binary tree node
struct Node {
    int data;           // Data stored in the node
    struct Node* left;  // Pointer to the left child
    struct Node* right; // Pointer to the right child
};

// Function to create a new node with the given data
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node)); // Allocate memory for the new node
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newNode->data = data;         // Set the data of the new node
    newNode->left = newNode->right = NULL; // Initialize left and right child pointers to NULL
    return newNode;              // Return the new node
}

// Function to insert a node with the given data into the BST
struct Node* insertNode(struct Node* root, int data) {
    if (root == NULL) {
        return createNode(data); // If the tree is empty, create a new node as the root
    }
    if (data < root->data) {
        root->left = insertNode(root->left, data); // Recursively insert into the left subtree
    } else if (data > root->data) {
        root->right = insertNode(root->right, data); // Recursively insert into the right subtree
    }
    // If data is equal to root's data, we don't insert (no duplicates)
    return root;
}

// Function to delete a node with the given key from the BST
struct Node* deleteNode(struct Node* root, int key) {
    if (root == NULL) {
        return root; // If the tree is empty or the key is not found, return root as it is
    }
    
    // Search for the node to be deleted
    if (key < root->data) {
        root->left = deleteNode(root->left, key); // Recursively delete from the left subtree
    } else if (key > root->data) {
        root->right = deleteNode(root->right, key); // Recursively delete from the right subtree
    } else {
        // Node with the key to be deleted is found
        
        // Case 1: Node with only one child or no child
        if (root->left == NULL) {
            struct Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct Node* temp = root->left;
            free(root);
            return temp;
        }
        
        // Case 2: Node with two children
        // Get the inorder successor (smallest in the right subtree)
        struct Node* successor = root->right;
        while (successor->left != NULL) {
            successor = successor->left;
        }
        
        // Copy the inorder successor's data to this node
        root->data = successor->data;
        
        // Delete the inorder successor
        root->right = deleteNode(root->right, successor->data);
    }
    return root;
}

// Function to perform an in-order traversal of the BST (ascending order)
void inOrder(struct Node* root) {
    if (root == NULL) return; // If the current node is NULL, return (base case)
    inOrder(root->left);      // Recursively traverse the left subtree
    printf("%d ", root->data); // Print the current node's data
    inOrder(root->right);     // Recursively traverse the right subtree
}

// Function to perform a pre-order traversal of the BST
void preOrder(struct Node* root) {
    if (root == NULL) return;      // Base case
    printf("%d ", root->data);     // Visit the current node
    preOrder(root->left);          // Recursively traverse the left subtree
    preOrder(root->right);         // Recursively traverse the right subtree
}

// Function to perform a post-order traversal of the BST
void postOrder(struct Node* root) {
    if (root == NULL) return;      // Base case
    postOrder(root->left);         // Recursively traverse the left subtree
    postOrder(root->right);        // Recursively traverse the right subtree
    printf("%d ", root->data);     // Visit the current node
}

// Function to find the height (maximum depth) of the tree
int findHeight(struct Node* root) {
    if (root == NULL) {
        return 0; // If the current node is NULL, the height is 0 (base case)
    }
    
    int leftHeight = findHeight(root->left);   // Recursively calculate the height of the left subtree
    int rightHeight = findHeight(root->right); // Recursively calculate the height of the right subtree
    
    // Return the greater height of the two subtrees, plus 1 for the current level
    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

// Function to find the size (number of nodes) of the tree
int findSize(struct Node* root) {
    if (root == NULL) {
        return 0; // If the current node is NULL, the size is 0 (base case)
    }
    
    // Return the sum of sizes of left subtree, right subtree, and the current node
    return findSize(root->left) + findSize(root->right) + 1;
}

// Function to find the maximum value in the BST
int findMaximum(struct Node* root) {
    if (root == NULL) {
        return -1; // If the tree is empty, return -1 to indicate no maximum
    }
    
    // The maximum value is at the rightmost node
    while (root->right != NULL) {
        root = root->right;
    }
    return root->data;
}

// Function to find the minimum value in the BST
int findMinimum(struct Node* root) {
    if (root == NULL) {
        return -1; // If the tree is empty, return -1 to indicate no minimum
    }
    
    // The minimum value is at the leftmost node
    while (root->left != NULL) {
        root = root->left;
    }
    return root->data;
}

// Function to search for a value in the BST
struct Node* search(struct Node* root, int key) {
    // Base case: root is NULL or key is found at root
    if (root == NULL || root->data == key) {
        return root;
    }
    
    // Key is greater than root's data, search in right subtree
    if (root->data < key) {
        return search(root->right, key);
    }
    
    // Key is smaller than root's data, search in left subtree
    return search(root->left, key);
}

// Function to free all nodes in the BST
void freeTree(struct Node* root) {
    if (root != NULL) {
        freeTree(root->left);   // Free the left subtree
        freeTree(root->right);  // Free the right subtree
        free(root);             // Free the current node
    }
}

int main() {
    struct Node* root = NULL;
    int num, ch;

    // Input loop to build the BST
    printf("=== Binary Search Tree Implementation ===\n\n");
    printf("Let's start by building a BST!\n");
    while (1) {
        printf("Enter numbers (enter 0 to stop): ");
        scanf("%d", &num);
        if (num == 0) {
            break;
        }
        root = insertNode(root, num);
    }

    do {
        // Display menu and perform operations based on user's choice
        printf("\n=== BST OPERATIONS MENU ===\n");
        printf("1. Insert a node\n");
        printf("2. Delete a node\n");
        printf("3. Display traversals (in-order, pre-order, post-order)\n");
        printf("4. Find minimum value\n");
        printf("5. Find maximum value\n");
        printf("6. Search for a value\n");
        printf("7. Find height of the tree\n");
        printf("8. Find size of the tree\n");
        printf("9. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &ch);

        switch (ch) {
            case 1:
                printf("\nEnter a number to insert: ");
                scanf("%d", &num);
                root = insertNode(root, num);
                printf("%d has been inserted into the BST.\n", num);
                break;
            case 2:
                printf("\nEnter a number to delete: ");
                scanf("%d", &num);
                root = deleteNode(root, num);
                printf("%d has been deleted from the BST (if it existed).\n", num);
                break;
            case 3:
                printf("\nIn-order traversal (sorted): ");
                inOrder(root);
                printf("\nPre-order traversal: ");
                preOrder(root);
                printf("\nPost-order traversal: ");
                postOrder(root);
                printf("\n");
                break;
            case 4: {
                int minVal = findMinimum(root);
                if (minVal != -1) {
                    printf("\nMinimum value in the BST: %d\n", minVal);
                } else {
                    printf("\nThe tree is empty.\n");
                }
                break;
            }
            case 5: {
                int maxVal = findMaximum(root);
                if (maxVal != -1) {
                    printf("\nMaximum value in the BST: %d\n", maxVal);
                } else {
                    printf("\nThe tree is empty.\n");
                }
                break;
            }
            case 6:
                printf("\nEnter a value to search for: ");
                scanf("%d", &num);
                if (search(root, num) != NULL) {
                    printf("Value %d found in the BST.\n", num);
                } else {
                    printf("Value %d not found in the BST.\n", num);
                }
                break;
            case 7:
                printf("\nThe height of the tree is: %d\n", findHeight(root));
                break;
            case 8:
                printf("\nThe size of the tree is: %d nodes\n", findSize(root));
                break;
            case 9:
                printf("\nExiting the program. Goodbye!\n");
                freeTree(root);  // Free all allocated memory before exiting
                return 0;
            default:
                printf("\nInvalid choice. Please try again.\n");
        }
    } while (1);

    return 0;
}
