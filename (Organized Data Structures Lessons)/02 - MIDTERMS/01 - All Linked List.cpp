#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Comprehensive Linked List Implementation
 * This file combines efficient and correct implementations of linked list operations
 * Based on best practices from multiple sources
 */

// Node structure for integer-based linked list
struct Node {
    int data;
    struct Node* next;
};

// Global pointer declarations
struct Node* head = NULL;

// Function declarations
struct Node* createNode(int value);
void insertAtBeginning(int value);
void insertAtEnd(int value);
void insertAtPosition(int value, int position);
void insertSorted(int value);
void deleteNode(int value);
void deleteAtPosition(int position);
int search(int value);
void displayList();
int countNodes();
int calculateSum();
int findMax();
int findMin();
float calculateAverage();
void reverseList();
void freeList();
void createList();
void createSortedList();
void showMenu();

// Function to create a new node
struct Node* createNode(int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    newNode->data = value;
    newNode->next = NULL;
    return newNode;
}

// Function to insert a node at the beginning of the list
void insertAtBeginning(int value) {
    struct Node* newNode = createNode(value);
    newNode->next = head;
    head = newNode;
    printf("Inserted %d at the beginning.\n", value);
}

// Function to insert a node at the end of the list
void insertAtEnd(int value) {
    struct Node* newNode = createNode(value);
    
    // If the list is empty, make the new node the head
    if (head == NULL) {
        head = newNode;
        printf("Inserted %d at the end (first element).\n", value);
        return;
    }
    
    // Otherwise, traverse to the end and add the new node
    struct Node* temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
    printf("Inserted %d at the end.\n", value);
}

// Function to insert a node at a specific position (0-indexed)
void insertAtPosition(int value, int position) {
    // Handle empty list or insertion at beginning
    if (head == NULL || position == 0) {
        insertAtBeginning(value);
        return;
    }
    
    struct Node* newNode = createNode(value);
    struct Node* temp = head;
    int i = 0;
    
    // Traverse to the position - 1
    while (temp != NULL && i < position - 1) {
        temp = temp->next;
        i++;
    }
    
    // If position is beyond the length of the list
    if (temp == NULL) {
        printf("Position %d is out of bounds. Inserting at the end instead.\n", position);
        insertAtEnd(value);
        return;
    }
    
    // Insert the new node
    newNode->next = temp->next;
    temp->next = newNode;
    printf("Inserted %d at position %d.\n", value, position);
}

// Function to insert a node in sorted order (ascending)
void insertSorted(int value) {
    struct Node* newNode = createNode(value);
    
    // If the list is empty or the value is smaller than the head
    if (head == NULL || value <= head->data) {
        newNode->next = head;
        head = newNode;
        printf("Inserted %d in sorted order (at beginning).\n", value);
        return;
    }
    
    // Find the position to insert
    struct Node* current = head;
    while (current->next != NULL && current->next->data < value) {
        current = current->next;
    }
    
    // Insert the new node
    newNode->next = current->next;
    current->next = newNode;
    printf("Inserted %d in sorted order.\n", value);
}

// Function to delete a node with a specific value
void deleteNode(int value) {
    // If the list is empty
    if (head == NULL) {
        printf("List is empty. Nothing to delete.\n");
        return;
    }
    
    // If the head node contains the value
    if (head->data == value) {
        struct Node* temp = head;
        head = head->next;
        free(temp);
        printf("Deleted %d from the list.\n", value);
        return;
    }
    
    // Search for the node to delete
    struct Node* current = head;
    struct Node* prev = NULL;
    
    while (current != NULL && current->data != value) {
        prev = current;
        current = current->next;
    }
    
    // If the value was not found
    if (current == NULL) {
        printf("Value %d not found in the list.\n", value);
        return;
    }
    
    // Remove the node
    prev->next = current->next;
    free(current);
    printf("Deleted %d from the list.\n", value);
}

// Function to delete a node at a specific position (0-indexed)
void deleteAtPosition(int position) {
    // If the list is empty
    if (head == NULL) {
        printf("List is empty. Nothing to delete.\n");
        return;
    }
    
    // If deleting the head
    if (position == 0) {
        struct Node* temp = head;
        head = head->next;
        free(temp);
        printf("Deleted node at position 0.\n");
        return;
    }
    
    // Traverse to the position
    struct Node* current = head;
    struct Node* prev = NULL;
    int i = 0;
    
    while (current != NULL && i < position) {
        prev = current;
        current = current->next;
        i++;
    }
    
    // If position is beyond the length of the list
    if (current == NULL) {
        printf("Position %d is out of bounds. Nothing deleted.\n", position);
        return;
    }
    
    // Delete the node
    prev->next = current->next;
    free(current);
    printf("Deleted node at position %d.\n", position);
}

// Function to search for a value in the list
int search(int value) {
    struct Node* current = head;
    int position = 0;
    
    while (current != NULL) {
        if (current->data == value) {
            printf("Value %d found at position %d.\n", value, position);
            return position;
        }
        current = current->next;
        position++;
    }
    
    printf("Value %d not found in the list.\n", value);
    return -1;
}

// Function to display the list
void displayList() {
    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }
    
    struct Node* current = head;
    printf("Linked List: ");
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
    printf("Number of elements: %d\n", countNodes());
}

// Function to count the number of nodes in the list
int countNodes() {
    struct Node* current = head;
    int count = 0;
    
    while (current != NULL) {
        count++;
        current = current->next;
    }
    
    return count;
}

// Function to calculate the sum of all values in the list
int calculateSum() {
    struct Node* current = head;
    int sum = 0;
    
    while (current != NULL) {
        sum += current->data;
        current = current->next;
    }
    
    return sum;
}

// Function to find the maximum value in the list
int findMax() {
    if (head == NULL) {
        printf("List is empty. No maximum value.\n");
        return -1; // Assuming -1 is not a valid value in our list
    }
    
    struct Node* current = head;
    int max = current->data;
    
    while (current != NULL) {
        if (current->data > max) {
            max = current->data;
        }
        current = current->next;
    }
    
    return max;
}

// Function to find the minimum value in the list
int findMin() {
    if (head == NULL) {
        printf("List is empty. No minimum value.\n");
        return -1; // Assuming -1 is not a valid value in our list
    }
    
    struct Node* current = head;
    int min = current->data;
    
    while (current != NULL) {
        if (current->data < min) {
            min = current->data;
        }
        current = current->next;
    }
    
    return min;
}

// Function to calculate the average of all values in the list
float calculateAverage() {
    int count = countNodes();
    if (count == 0) {
        printf("List is empty. No average value.\n");
        return 0.0;
    }
    
    float sum = (float)calculateSum();
    return sum / count;
}

// Function to reverse the linked list
void reverseList() {
    if (head == NULL || head->next == NULL) {
        // Empty list or list with only one node
        return;
    }
    
    struct Node* prev = NULL;
    struct Node* current = head;
    struct Node* next = NULL;
    
    while (current != NULL) {
        next = current->next;  // Store the next node
        current->next = prev;  // Reverse the link
        prev = current;        // Move prev one step forward
        current = next;        // Move current one step forward
    }
    
    head = prev;  // Update the head to the new start
    printf("List has been reversed.\n");
}

// Function to free all nodes in the list
void freeList() {
    struct Node* current = head;
    struct Node* next;
    
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    
    head = NULL;
    printf("List has been freed.\n");
}

// Function to create a sample list with user input
void createList() {
    int num, choice;
    
    // Clear any existing list
    freeList();
    
    // Get the first number
    printf("Enter a number: ");
    scanf("%d", &num);
    
    // Create the head node
    head = createNode(num);
    struct Node* current = head;
    
    // Ask for more numbers
    printf("Press 1 to enter another number or any other number to stop: ");
    scanf("%d", &choice);
    
    while (choice == 1) {
        printf("Enter a number: ");
        scanf("%d", &num);
        
        // Create and link a new node
        current->next = createNode(num);
        current = current->next;
        
        printf("Press 1 to enter another number or any other number to stop: ");
        scanf("%d", &choice);
    }
    
    printf("List created successfully.\n");
    displayList();
}

// Function to create a sorted list with user input
void createSortedList() {
    int num, choice;
    
    // Clear any existing list
    freeList();
    
    // Get the first number
    printf("Enter a number: ");
    scanf("%d", &num);
    
    // Insert the first number (creates the head)
    insertSorted(num);
    
    // Ask for more numbers
    printf("Press 1 to enter another number or any other number to stop: ");
    scanf("%d", &choice);
    
    while (choice == 1) {
        printf("Enter a number: ");
        scanf("%d", &num);
        
        // Insert in sorted order
        insertSorted(num);
        
        printf("Press 1 to enter another number or any other number to stop: ");
        scanf("%d", &choice);
    }
    
    printf("Sorted list created successfully.\n");
    displayList();
}

// Main menu function
void showMenu() {
    printf("\n=== Linked List Operations Menu ===\n");
    printf("1. Create a new list\n");
    printf("2. Create a sorted list\n");
    printf("3. Insert at beginning\n");
    printf("4. Insert at end\n");
    printf("5. Insert at position\n");
    printf("6. Insert in sorted order\n");
    printf("7. Delete a node by value\n");
    printf("8. Delete a node by position\n");
    printf("9. Search for a value\n");
    printf("10. Display the list\n");
    printf("11. Count nodes\n");
    printf("12. Calculate sum\n");
    printf("13. Find maximum value\n");
    printf("14. Find minimum value\n");
    printf("15. Calculate average\n");
    printf("16. Reverse the list\n");
    printf("17. Free the list\n");
    printf("18. Exit\n");
    printf("Enter your choice: ");
}

// Main function
int main() {
    int choice, value, position;
    
    do {
        showMenu();
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                createList();
                break;
                
            case 2:
                createSortedList();
                break;
                
            case 3:
                printf("Enter a value to insert at the beginning: ");
                scanf("%d", &value);
                insertAtBeginning(value);
                displayList();
                break;
                
            case 4:
                printf("Enter a value to insert at the end: ");
                scanf("%d", &value);
                insertAtEnd(value);
                displayList();
                break;
                
            case 5:
                printf("Enter a value to insert: ");
                scanf("%d", &value);
                printf("Enter the position (0-indexed): ");
                scanf("%d", &position);
                insertAtPosition(value, position);
                displayList();
                break;
                
            case 6:
                printf("Enter a value to insert in sorted order: ");
                scanf("%d", &value);
                insertSorted(value);
                displayList();
                break;
                
            case 7:
                printf("Enter the value to delete: ");
                scanf("%d", &value);
                deleteNode(value);
                displayList();
                break;
                
            case 8:
                printf("Enter the position to delete (0-indexed): ");
                scanf("%d", &position);
                deleteAtPosition(position);
                displayList();
                break;
                
            case 9:
                printf("Enter the value to search for: ");
                scanf("%d", &value);
                search(value);
                break;
                
            case 10:
                displayList();
                break;
                
            case 11:
                printf("Number of nodes: %d\n", countNodes());
                break;
                
            case 12:
                printf("Sum of values: %d\n", calculateSum());
                break;
                
            case 13:
                printf("Maximum value: %d\n", findMax());
                break;
                
            case 14:
                printf("Minimum value: %d\n", findMin());
                break;
                
            case 15:
                printf("Average value: %.2f\n", calculateAverage());
                break;
                
            case 16:
                reverseList();
                displayList();
                break;
                
            case 17:
                freeList();
                break;
                
            case 18:
                printf("Exiting program. Goodbye!\n");
                break;
                
            default:
                printf("Invalid choice. Please try again.\n");
        }
        
    } while (choice != 18);
    
    // Clean up any remaining nodes before exiting
    freeList();
    
    return 0;
}
