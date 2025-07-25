/*
 * Dictionary.cpp
 * Description: An efficient dictionary implementation using Binary Search Tree
 * Features:
 *   - Add words with definitions
 *   - Search for words
 *   - Delete words
 *   - Display all words in alphabetical order
 *   - Save dictionary to file
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define a struct for a node in the binary search tree
struct DictionaryNode {
    char word[50];
    char definition[200];
    struct DictionaryNode* left;
    struct DictionaryNode* right;
};

// Function prototypes
struct DictionaryNode* createNode(const char* word, const char* definition);
struct DictionaryNode* insertNode(struct DictionaryNode* root, const char* word, const char* definition);
void searchWord(struct DictionaryNode* root, const char* word);
struct DictionaryNode* deleteNode(struct DictionaryNode* root, const char* word);
struct DictionaryNode* findMinNode(struct DictionaryNode* node);
void displayAllWords(struct DictionaryNode* root);
void saveToFile(FILE* file, struct DictionaryNode* root);
void displayMenu();

int main() {
    struct DictionaryNode* root = NULL;
    char word[50];
    char definition[200];
    int choice;
    FILE* dictionaryFile = NULL;

    printf("\n===== Welcome to the Dictionary Program =====\n\n");

    do {
        displayMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Clear the newline character from the input buffer

        switch (choice) {
            case 1: // Add word
                printf("\nEnter a word: ");
                scanf("%s", word);
                printf("Enter its definition: ");
                getchar(); // Clear the newline character
                scanf("%[^\n]", definition);
                root = insertNode(root, word, definition);
                printf("\nWord '%s' has been added to the dictionary.\n", word);
                break;
                
            case 2: // Search word
                printf("\nEnter a word to search: ");
                scanf("%s", word);
                searchWord(root, word);
                break;
                
            case 3: // Delete word
                printf("\nEnter a word to delete: ");
                scanf("%s", word);
                root = deleteNode(root, word);
                break;
                
            case 4: // Display all words
                printf("\n===== All Words and Definitions =====\n\n");
                if (root == NULL) {
                    printf("Dictionary is empty.\n");
                } else {
                    displayAllWords(root);
                }
                break;
                
            case 5: // Save to file
                dictionaryFile = fopen("dictionary.txt", "w");
                if (dictionaryFile == NULL) {
                    printf("\nError opening file for writing.\n");
                } else {
                    saveToFile(dictionaryFile, root);
                    fclose(dictionaryFile);
                    printf("\nDictionary has been saved to 'dictionary.txt'.\n");
                }
                break;
                
            case 6: // Exit
                printf("\nExiting the program. Goodbye!\n");
                break;
                
            default:
                printf("\nInvalid choice. Please try again.\n");
        }
    } while (choice != 6);

    return 0;
}

// Function to display the menu
void displayMenu() {
    printf("\n===== DICTIONARY MENU =====\n");
    printf("1. Add a word and its definition\n");
    printf("2. Search for a word\n");
    printf("3. Delete a word\n");
    printf("4. Display all words\n");
    printf("5. Save dictionary to file\n");
    printf("6. Exit\n");
}

// Function to create a new node with the given word and definition
struct DictionaryNode* createNode(const char* word, const char* definition) {
    struct DictionaryNode* newNode = (struct DictionaryNode*)malloc(sizeof(struct DictionaryNode));
    if (newNode == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    
    strncpy(newNode->word, word, sizeof(newNode->word) - 1);
    newNode->word[sizeof(newNode->word) - 1] = '\0'; // Ensure null-terminated string
    
    strncpy(newNode->definition, definition, sizeof(newNode->definition) - 1);
    newNode->definition[sizeof(newNode->definition) - 1] = '\0'; // Ensure null-terminated string
    
    newNode->left = newNode->right = NULL;
    
    return newNode;
}

// Function to insert a new word and its definition into the binary search tree
struct DictionaryNode* insertNode(struct DictionaryNode* root, const char* word, const char* definition) {
    // If the root is NULL, create a new node with the given word and definition
    if (root == NULL) {
        return createNode(word, definition);
    }
    
    // Compare the word with the current node's word
    int compareResult = strcmp(word, root->word);
    
    // If the word comes before the root's word, insert it into the left subtree
    if (compareResult < 0) {
        root->left = insertNode(root->left, word, definition);
    }
    // If the word comes after the root's word, insert it into the right subtree
    else if (compareResult > 0) {
        root->right = insertNode(root->right, word, definition);
    }
    // If the word is already in the dictionary, update its definition
    else {
        // Update the definition for the existing word
        strncpy(root->definition, definition, sizeof(root->definition) - 1);
        root->definition[sizeof(root->definition) - 1] = '\0';
        printf("Word already exists. Definition updated.\n");
    }
    
    // Return the root node
    return root;
}

// Function to search for a word in the binary search tree and display its definition
void searchWord(struct DictionaryNode* root, const char* word) {
    if (root == NULL) {
        printf("Word '%s' not found in the dictionary.\n", word);
        return;
    }
    
    int compareResult = strcmp(word, root->word);
    
    if (compareResult == 0) {
        // Word found, display its definition
        printf("\nWord: %s\n", root->word);
        printf("Definition: %s\n", root->definition);
    } else if (compareResult < 0) {
        // Search in the left subtree
        searchWord(root->left, word);
    } else {
        // Search in the right subtree
        searchWord(root->right, word);
    }
}

// Function to find the minimum node in a binary search tree (used for deletion)
struct DictionaryNode* findMinNode(struct DictionaryNode* node) {
    struct DictionaryNode* current = node;
    
    // Find the leftmost leaf node
    while (current && current->left != NULL) {
        current = current->left;
    }
    
    return current;
}

// Function to delete a node with a given word from the binary search tree
struct DictionaryNode* deleteNode(struct DictionaryNode* root, const char* word) {
    if (root == NULL) {
        printf("Word '%s' not found in the dictionary.\n", word);
        return root;
    }
    
    int compareResult = strcmp(word, root->word);
    
    if (compareResult < 0) {
        // The word to be deleted is in the left subtree
        root->left = deleteNode(root->left, word);
    } else if (compareResult > 0) {
        // The word to be deleted is in the right subtree
        root->right = deleteNode(root->right, word);
    } else {
        // This is the node to be deleted
        
        // Case 1: No child or only one child
        if (root->left == NULL) {
            struct DictionaryNode* temp = root->right;
            free(root);
            printf("Word '%s' has been deleted from the dictionary.\n", word);
            return temp;
        } else if (root->right == NULL) {
            struct DictionaryNode* temp = root->left;
            free(root);
            printf("Word '%s' has been deleted from the dictionary.\n", word);
            return temp;
        }
        
        // Case 2: Two children
        // Get the inorder successor (smallest in the right subtree)
        struct DictionaryNode* temp = findMinNode(root->right);
        
        // Copy the inorder successor's content to this node
        strncpy(root->word, temp->word, sizeof(root->word) - 1);
        root->word[sizeof(root->word) - 1] = '\0';
        
        strncpy(root->definition, temp->definition, sizeof(root->definition) - 1);
        root->definition[sizeof(root->definition) - 1] = '\0';
        
        // Delete the inorder successor
        root->right = deleteNode(root->right, temp->word);
        printf("Word '%s' has been deleted from the dictionary.\n", word);
    }
    
    return root;
}

// Function to display all words and their definitions in alphabetical order (inorder traversal)
void displayAllWords(struct DictionaryNode* root) {
    if (root != NULL) {
        // Visit left subtree
        displayAllWords(root->left);
        
        // Display current node
        printf("Word: %s\n", root->word);
        printf("Definition: %s\n\n", root->definition);
        
        // Visit right subtree
        displayAllWords(root->right);
    }
}

// Function to save the dictionary to a file in alphabetical order
void saveToFile(FILE* file, struct DictionaryNode* root) {
    if (root != NULL) {
        // Visit left subtree
        saveToFile(file, root->left);
        
        // Save current node to file
        fprintf(file, "%s - %s\n", root->word, root->definition);
        
        // Visit right subtree
        saveToFile(file, root->right);
    }
}
