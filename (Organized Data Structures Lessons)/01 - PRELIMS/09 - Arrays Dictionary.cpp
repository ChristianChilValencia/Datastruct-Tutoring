/*
 * DictionaryArrays.cpp
 * Description: An efficient dictionary implementation using Arrays
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

#define MAX_WORDS 100
#define MAX_WORD_LENGTH 50
#define MAX_DEFINITION_LENGTH 200

// Define a struct for a dictionary entry
struct DictionaryEntry {
    char word[MAX_WORD_LENGTH];
    char definition[MAX_DEFINITION_LENGTH];
    int isActive; // Flag to mark if entry is active (1) or deleted (0)
};

// Global dictionary array and size counter
struct DictionaryEntry dictionary[MAX_WORDS];
int dictionarySize = 0;

// Function prototypes
void initializeDictionary();
int addWord(const char* word, const char* definition);
int searchWord(const char* word);
int deleteWord(const char* word);
void displayAllWords();
void saveToFile(const char* filename);
void sortDictionary();
void displayMenu();

int main() {
    char word[MAX_WORD_LENGTH];
    char definition[MAX_DEFINITION_LENGTH];
    int choice;
    int index;
    
    // Initialize all dictionary entries
    initializeDictionary();
    
    printf("\n===== Welcome to the Dictionary Program (Array Implementation) =====\n\n");
    
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
                
                if (addWord(word, definition)) {
                    printf("\nWord '%s' has been added to the dictionary.\n", word);
                } else {
                    printf("\nDictionary is full. Cannot add more words.\n");
                }
                break;
                
            case 2: // Search word
                printf("\nEnter a word to search: ");
                scanf("%s", word);
                
                index = searchWord(word);
                if (index != -1) {
                    printf("\nWord: %s\n", dictionary[index].word);
                    printf("Definition: %s\n", dictionary[index].definition);
                } else {
                    printf("\nWord '%s' not found in the dictionary.\n", word);
                }
                break;
                
            case 3: // Delete word
                printf("\nEnter a word to delete: ");
                scanf("%s", word);
                
                if (deleteWord(word)) {
                    printf("\nWord '%s' has been deleted from the dictionary.\n", word);
                } else {
                    printf("\nWord '%s' not found in the dictionary.\n", word);
                }
                break;
                
            case 4: // Display all words
                printf("\n===== All Words and Definitions =====\n\n");
                displayAllWords();
                break;
                
            case 5: // Save to file
                saveToFile("dictionary.txt");
                printf("\nDictionary has been saved to 'dictionary.txt'.\n");
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

// Function to initialize the dictionary array
void initializeDictionary() {
    for (int i = 0; i < MAX_WORDS; i++) {
        dictionary[i].isActive = 0; // Mark all entries as inactive initially
    }
    dictionarySize = 0;
}

// Function to add a word to the dictionary
int addWord(const char* word, const char* definition) {
    int index;
    
    // Check if dictionary is full
    if (dictionarySize >= MAX_WORDS) {
        return 0; // Dictionary is full
    }
    
    // Check if word already exists, update if it does
    index = searchWord(word);
    if (index != -1) {
        // Word found, update its definition
        strncpy(dictionary[index].definition, definition, MAX_DEFINITION_LENGTH - 1);
        dictionary[index].definition[MAX_DEFINITION_LENGTH - 1] = '\0';
        printf("Word already exists. Definition updated.\n");
        return 1;
    }
    
    // Add new word
    strncpy(dictionary[dictionarySize].word, word, MAX_WORD_LENGTH - 1);
    dictionary[dictionarySize].word[MAX_WORD_LENGTH - 1] = '\0';
    
    strncpy(dictionary[dictionarySize].definition, definition, MAX_DEFINITION_LENGTH - 1);
    dictionary[dictionarySize].definition[MAX_DEFINITION_LENGTH - 1] = '\0';
    
    dictionary[dictionarySize].isActive = 1; // Mark as active
    dictionarySize++;
    
    // Sort the dictionary after adding a new word
    sortDictionary();
    
    return 1;
}

// Function to search for a word in the dictionary (binary search)
int searchWord(const char* word) {
    int left = 0;
    int right = dictionarySize - 1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        // Skip inactive entries
        if (!dictionary[mid].isActive) {
            // Try linear search instead if we hit an inactive entry
            for (int i = 0; i < dictionarySize; i++) {
                if (dictionary[i].isActive && strcmp(dictionary[i].word, word) == 0) {
                    return i;
                }
            }
            return -1;
        }
        
        int compareResult = strcmp(word, dictionary[mid].word);
        
        if (compareResult == 0) {
            return mid; // Word found
        } else if (compareResult < 0) {
            right = mid - 1; // Search in the left half
        } else {
            left = mid + 1; // Search in the right half
        }
    }
    
    return -1; // Word not found
}

// Function to delete a word from the dictionary
int deleteWord(const char* word) {
    int index = searchWord(word);
    
    if (index == -1) {
        return 0; // Word not found
    }
    
    // Mark entry as inactive
    dictionary[index].isActive = 0;
    
    // Shift all elements to the left to fill the gap
    for (int i = index; i < dictionarySize - 1; i++) {
        strcpy(dictionary[i].word, dictionary[i + 1].word);
        strcpy(dictionary[i].definition, dictionary[i + 1].definition);
        dictionary[i].isActive = dictionary[i + 1].isActive;
    }
    
    dictionarySize--;
    
    return 1; // Word deleted successfully
}

// Function to sort the dictionary array (using bubble sort for simplicity)
void sortDictionary() {
    struct DictionaryEntry temp;
    
    for (int i = 0; i < dictionarySize - 1; i++) {
        for (int j = 0; j < dictionarySize - i - 1; j++) {
            if (strcmp(dictionary[j].word, dictionary[j + 1].word) > 0) {
                // Swap entries
                temp = dictionary[j];
                dictionary[j] = dictionary[j + 1];
                dictionary[j + 1] = temp;
            }
        }
    }
}

// Function to display all words in the dictionary
void displayAllWords() {
    if (dictionarySize == 0) {
        printf("Dictionary is empty.\n");
        return;
    }
    
    for (int i = 0; i < dictionarySize; i++) {
        if (dictionary[i].isActive) {
            printf("Word: %s\n", dictionary[i].word);
            printf("Definition: %s\n\n", dictionary[i].definition);
        }
    }
}

// Function to save the dictionary to a file
void saveToFile(const char* filename) {
    FILE* file = fopen(filename, "w");
    
    if (file == NULL) {
        printf("\nError opening file for writing.\n");
        return;
    }
    
    for (int i = 0; i < dictionarySize; i++) {
        if (dictionary[i].isActive) {
            fprintf(file, "%s - %s\n", dictionary[i].word, dictionary[i].definition);
        }
    }
    
    fclose(file);
}
