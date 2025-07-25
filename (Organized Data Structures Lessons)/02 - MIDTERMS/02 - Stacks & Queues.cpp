#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

// Node structure for linked list implementation
struct Node {
    int data;
    struct Node* next;
};

// ============= STACK IMPLEMENTATION =============
struct Stack {
    // Array implementation
    int* array;
    int top;
    int capacity;
    
    // Linked list implementation
    struct Node* head;
    
    // Flag to determine which implementation to use
    int useArray;
};

// Function prototypes for Stack
struct Stack* createStack(int capacity, int useArray);
int isStackEmpty(struct Stack* stack);
int isStackFull(struct Stack* stack);
void push(struct Stack* stack, int item);
int pop(struct Stack* stack);
int peekStack(struct Stack* stack);
void displayStack(struct Stack* stack);
void freeStack(struct Stack* stack);

// ============= QUEUE IMPLEMENTATION =============
struct Queue {
    // Array implementation
    int* array;
    int front;
    int rear;
    int capacity;
    
    // Linked list implementation
    struct Node* head; // front of queue
    struct Node* tail; // rear of queue
    
    // Flags to determine implementation type
    int implementationType; // 1=Array, 2=Dynamic, 3=LinkedList, 4=Circular
};

// Function prototypes for Queue
struct Queue* createQueue(int capacity, int implementationType);
int isQueueEmpty(struct Queue* queue);
int isQueueFull(struct Queue* queue);
void enqueue(struct Queue* queue, int item);
int dequeue(struct Queue* queue);
int peekQueue(struct Queue* queue);
void displayQueue(struct Queue* queue);
void freeQueue(struct Queue* queue);

// Create a new stack
struct Stack* createStack(int capacity, int useArray) {
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    if (!stack) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    
    stack->useArray = useArray;
    
    if (useArray) {
        // Initialize array implementation
        stack->capacity = capacity;
        stack->top = -1;
        stack->array = (int*)malloc(stack->capacity * sizeof(int));
        if (!stack->array) {
            printf("Memory allocation failed!\n");
            free(stack);
            exit(1);
        }
        stack->head = NULL;
    } else {
        // Initialize linked list implementation
        stack->array = NULL;
        stack->head = NULL;
        stack->capacity = 0;
        stack->top = -1;
    }
    
    return stack;
}

// Check if the stack is empty
int isStackEmpty(struct Stack* stack) {
    if (stack->useArray) {
        return stack->top == -1;
    } else {
        return stack->head == NULL;
    }
}

// Check if the stack is full (only applicable for array implementation)
int isStackFull(struct Stack* stack) {
    if (stack->useArray) {
        return stack->top == stack->capacity - 1;
    } else {
        return 0; // Linked list implementation is never full
    }
}

// Push an item onto the stack
void push(struct Stack* stack, int item) {
    if (stack->useArray) {
        if (isStackFull(stack)) {
            printf("Stack Overflow! Cannot push %d.\n", item);
            return;
        }
        
        stack->array[++stack->top] = item;
        printf("Pushed %d onto the stack.\n", item);
    } else {
        struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
        if (!newNode) {
            printf("Memory allocation failed!\n");
            exit(1);
        }
        
        newNode->data = item;
        newNode->next = stack->head;
        stack->head = newNode;
        printf("Pushed %d onto the stack.\n", item);
    }
}

// Pop an item from the stack
int pop(struct Stack* stack) {
    if (isStackEmpty(stack)) {
        printf("Stack Underflow! Cannot pop from an empty stack.\n");
        return -1;
    }
    
    int item;
    
    if (stack->useArray) {
        item = stack->array[stack->top--];
    } else {
        struct Node* temp = stack->head;
        item = temp->data;
        stack->head = temp->next;
        free(temp);
    }
    
    printf("Popped %d from the stack.\n", item);
    return item;
}

// Get the top item without removing it
int peekStack(struct Stack* stack) {
    if (isStackEmpty(stack)) {
        printf("Stack is empty!\n");
        return -1;
    }
    
    if (stack->useArray) {
        return stack->array[stack->top];
    } else {
        return stack->head->data;
    }
}

// Display all elements in the stack
void displayStack(struct Stack* stack) {
    if (isStackEmpty(stack)) {
        printf("Stack is empty.\n");
        return;
    }
    
    printf("Stack contents: ");
    
    if (stack->useArray) {
        for (int i = 0; i <= stack->top; i++) {
            printf("%d ", stack->array[i]);
        }
    } else {
        struct Node* current = stack->head;
        while (current != NULL) {
            printf("%d ", current->data);
            current = current->next;
        }
    }
    
    printf("\n");
}

// Free memory allocated for the stack
void freeStack(struct Stack* stack) {
    if (stack->useArray) {
        free(stack->array);
    } else {
        struct Node* current = stack->head;
        struct Node* next;
        
        while (current != NULL) {
            next = current->next;
            free(current);
            current = next;
        }
    }
    
    free(stack);
}

// Create a new queue
struct Queue* createQueue(int capacity, int implementationType) {
    struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));
    if (!queue) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    
    queue->implementationType = implementationType;
    
    // Initialize based on implementation type
    if (implementationType == 1 || implementationType == 4) {
        // Array-based or Circular Queue
        queue->capacity = capacity > 0 ? capacity : MAX_SIZE;
        queue->front = -1;
        queue->rear = -1;
        queue->array = (int*)malloc(queue->capacity * sizeof(int));
        if (!queue->array) {
            printf("Memory allocation failed!\n");
            free(queue);
            exit(1);
        }
        queue->head = NULL;
        queue->tail = NULL;
    } 
    else if (implementationType == 2) {
        // Dynamic Array Queue
        queue->capacity = capacity;
        queue->front = 0;
        queue->rear = -1;
        queue->array = (int*)malloc(queue->capacity * sizeof(int));
        if (!queue->array) {
            printf("Memory allocation failed!\n");
            free(queue);
            exit(1);
        }
        queue->head = NULL;
        queue->tail = NULL;
    }
    else {
        // Linked List Queue
        queue->array = NULL;
        queue->head = NULL;
        queue->tail = NULL;
        queue->capacity = 0;
        queue->front = -1;
        queue->rear = -1;
    }
    
    return queue;
}

// Check if the queue is empty
int isQueueEmpty(struct Queue* queue) {
    if (queue->implementationType == 1 || queue->implementationType == 4) {
        // Array-based or Circular Queue
        return queue->front == -1;
    } 
    else if (queue->implementationType == 2) {
        // Dynamic Array Queue
        return queue->rear < queue->front;
    }
    else {
        // Linked List Queue
        return queue->head == NULL;
    }
}

// Check if the queue is full
int isQueueFull(struct Queue* queue) {
    if (queue->implementationType == 1) {
        // Standard Array Queue
        return queue->rear == queue->capacity - 1;
    } 
    else if (queue->implementationType == 2) {
        // Dynamic Array Queue
        return queue->rear == queue->capacity - 1;
    }
    else if (queue->implementationType == 4) {
        // Circular Queue
        return (queue->front == 0 && queue->rear == queue->capacity - 1) || 
               (queue->rear == (queue->front - 1) % (queue->capacity - 1));
    }
    else {
        // Linked List Queue is never full
        return 0;
    }
}

// Add an element to the queue
void enqueue(struct Queue* queue, int item) {
    if (isQueueFull(queue)) {
        printf("Queue Overflow! Cannot enqueue %d.\n", item);
        return;
    }
    
    switch (queue->implementationType) {
        case 1: // Array-based Queue
            if (isQueueEmpty(queue)) {
                queue->front = 0;
            }
            queue->array[++queue->rear] = item;
            printf("Enqueued %d into the queue.\n", item);
            break;
            
        case 2: // Dynamic Array Queue
            queue->array[++queue->rear] = item;
            printf("Enqueued %d into the queue.\n", item);
            break;
            
        case 3: // Linked List Queue
            {
                struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
                if (!newNode) {
                    printf("Memory allocation failed!\n");
                    exit(1);
                }
                
                newNode->data = item;
                newNode->next = NULL;
                
                if (isQueueEmpty(queue)) {
                    queue->head = queue->tail = newNode;
                } else {
                    queue->tail->next = newNode;
                    queue->tail = newNode;
                }
                
                printf("Enqueued %d into the queue.\n", item);
            }
            break;
            
        case 4: // Circular Queue
            if (isQueueEmpty(queue)) {
                queue->front = 0;
                queue->rear = 0;
            } else {
                queue->rear = (queue->rear + 1) % queue->capacity;
            }
            
            queue->array[queue->rear] = item;
            printf("Enqueued %d into the circular queue.\n", item);
            break;
    }
}

// Remove an element from the queue
int dequeue(struct Queue* queue) {
    if (isQueueEmpty(queue)) {
        printf("Queue Underflow! Cannot dequeue from an empty queue.\n");
        return -1;
    }
    
    int item;
    
    switch (queue->implementationType) {
        case 1: // Array-based Queue
            item = queue->array[queue->front];
            
            if (queue->front == queue->rear) {
                // Last element is being removed
                queue->front = -1;
                queue->rear = -1;
            } else {
                queue->front++;
            }
            break;
            
        case 2: // Dynamic Array Queue
            item = queue->array[queue->front++];
            break;
            
        case 3: // Linked List Queue
            {
                struct Node* temp = queue->head;
                item = temp->data;
                
                queue->head = queue->head->next;
                
                if (queue->head == NULL) {
                    queue->tail = NULL;
                }
                
                free(temp);
            }
            break;
            
        case 4: // Circular Queue
            item = queue->array[queue->front];
            
            if (queue->front == queue->rear) {
                // Last element is being removed
                queue->front = -1;
                queue->rear = -1;
            } else {
                queue->front = (queue->front + 1) % queue->capacity;
            }
            break;
    }
    
    printf("Dequeued %d from the queue.\n", item);
    return item;
}

// Get the front element without removing it
int peekQueue(struct Queue* queue) {
    if (isQueueEmpty(queue)) {
        printf("Queue is empty!\n");
        return -1;
    }
    
    if (queue->implementationType == 3) {
        // Linked List Queue
        return queue->head->data;
    } else {
        // All array-based queues
        return queue->array[queue->front];
    }
}

// Display all elements in the queue
void displayQueue(struct Queue* queue) {
    if (isQueueEmpty(queue)) {
        printf("Queue is empty.\n");
        return;
    }
    
    printf("Queue contents: ");
    
    switch (queue->implementationType) {
        case 1: // Array-based Queue
        case 2: // Dynamic Array Queue
            for (int i = queue->front; i <= queue->rear; i++) {
                printf("%d ", queue->array[i]);
            }
            break;
            
        case 3: // Linked List Queue
            {
                struct Node* current = queue->head;
                while (current != NULL) {
                    printf("%d ", current->data);
                    current = current->next;
                }
            }
            break;
            
        case 4: // Circular Queue
            if (queue->front <= queue->rear) {
                // No wrap-around
                for (int i = queue->front; i <= queue->rear; i++) {
                    printf("%d ", queue->array[i]);
                }
            } else {
                // Elements wrap around
                for (int i = queue->front; i < queue->capacity; i++) {
                    printf("%d ", queue->array[i]);
                }
                for (int i = 0; i <= queue->rear; i++) {
                    printf("%d ", queue->array[i]);
                }
            }
            break;
    }
    
    printf("\n");
}

// Free memory allocated for the queue
void freeQueue(struct Queue* queue) {
    if (queue->implementationType != 3) {
        // Free array for array-based implementations
        free(queue->array);
    } else {
        // Free linked list nodes
        struct Node* current = queue->head;
        struct Node* next;
        
        while (current != NULL) {
            next = current->next;
            free(current);
            current = next;
        }
    }
    
    free(queue);
}

// Main function
int main() {
    int dataStructureChoice, implementationChoice, operationChoice;
    int item, capacity;
    struct Stack* stack = NULL;
    struct Queue* queue = NULL;
    
    while (1) {
        // Main menu for data structure selection
        printf("\n===== DATA STRUCTURES IMPLEMENTATION =====\n");
        printf("Choose a data structure:\n");
        printf("1. Stack\n");
        printf("2. Queue\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &dataStructureChoice);
        
        if (dataStructureChoice == 3) {
            printf("Exiting program...\n");
            break;
        }
        
        if (dataStructureChoice != 1 && dataStructureChoice != 2) {
            printf("Invalid choice. Please try again.\n");
            continue;
        }
        
        // Handle Stack operations
        if (dataStructureChoice == 1) {
            // Menu for stack implementation selection
            printf("\n===== STACK IMPLEMENTATION =====\n");
            printf("Choose the type of implementation:\n");
            printf("1. Array-based Stack\n");
            printf("2. Linked List-based Stack\n");
            printf("3. Return to Main Menu\n");
            printf("Enter your choice: ");
            scanf("%d", &implementationChoice);
            
            if (implementationChoice == 3) {
                continue;
            }
            
            if (implementationChoice != 1 && implementationChoice != 2) {
                printf("Invalid choice. Please try again.\n");
                continue;
            }
            
            // For array implementation, get capacity
            if (implementationChoice == 1) {
                printf("Enter the capacity of the stack: ");
                scanf("%d", &capacity);
            } else {
                capacity = 0; // Not needed for linked list implementation
            }
            
            // Create stack with chosen implementation
            stack = createStack(capacity, implementationChoice == 1);
            
            // Operations menu
            do {
                printf("\n===== STACK OPERATIONS =====\n");
                printf("1. Push\n");
                printf("2. Pop\n");
                printf("3. Peek\n");
                printf("4. Display\n");
                printf("5. Check if Empty\n");
                printf("6. Check if Full\n");
                printf("7. Return to Implementation Selection\n");
                printf("Enter your choice: ");
                scanf("%d", &operationChoice);
                
                switch (operationChoice) {
                    case 1:
                        printf("Enter the value to push: ");
                        scanf("%d", &item);
                        push(stack, item);
                        displayStack(stack);
                        break;
                        
                    case 2:
                        pop(stack);
                        displayStack(stack);
                        break;
                        
                    case 3:
                        if (!isStackEmpty(stack)) {
                            printf("Top element is: %d\n", peekStack(stack));
                        } else {
                            printf("Stack is empty!\n");
                        }
                        break;
                        
                    case 4:
                        displayStack(stack);
                        break;
                        
                    case 5:
                        if (isStackEmpty(stack)) {
                            printf("Stack is empty.\n");
                        } else {
                            printf("Stack is not empty.\n");
                        }
                        break;
                        
                    case 6:
                        if (isStackFull(stack)) {
                            printf("Stack is full.\n");
                        } else {
                            printf("Stack is not full.\n");
                        }
                        break;
                        
                    case 7:
                        printf("Returning to implementation selection...\n");
                        break;
                        
                    default:
                        printf("Invalid choice. Please try again.\n");
                }
            } while (operationChoice != 7);
            
            // Free allocated memory before creating a new stack
            freeStack(stack);
        }
        // Handle Queue operations
        else if (dataStructureChoice == 2) {
            // Menu for queue implementation selection
            printf("\n===== QUEUE IMPLEMENTATION =====\n");
            printf("Choose the type of implementation:\n");
            printf("1. Array-based Queue (Fixed Size)\n");
            printf("2. Dynamic Array Queue (User-defined Size)\n");
            printf("3. Linked List-based Queue\n");
            printf("4. Circular Queue\n");
            printf("5. Return to Main Menu\n");
            printf("Enter your choice: ");
            scanf("%d", &implementationChoice);
            
            if (implementationChoice == 5) {
                continue;
            }
            
            if (implementationChoice < 1 || implementationChoice > 4) {
                printf("Invalid choice. Please try again.\n");
                continue;
            }
            
            // For array implementations, get capacity
            if (implementationChoice != 3) {
                printf("Enter the capacity of the queue: ");
                scanf("%d", &capacity);
            } else {
                capacity = 0; // Not needed for linked list implementation
            }
            
            // Create queue with chosen implementation
            queue = createQueue(capacity, implementationChoice);
            
            // Operations menu
            do {
                printf("\n===== QUEUE OPERATIONS =====\n");
                printf("1. Enqueue\n");
                printf("2. Dequeue\n");
                printf("3. Peek (Front Element)\n");
                printf("4. Display\n");
                printf("5. Check if Empty\n");
                printf("6. Check if Full\n");
                printf("7. Return to Implementation Selection\n");
                printf("Enter your choice: ");
                scanf("%d", &operationChoice);
                
                switch (operationChoice) {
                    case 1:
                        printf("Enter the value to enqueue: ");
                        scanf("%d", &item);
                        enqueue(queue, item);
                        displayQueue(queue);
                        break;
                        
                    case 2:
                        dequeue(queue);
                        displayQueue(queue);
                        break;
                        
                    case 3:
                        if (!isQueueEmpty(queue)) {
                            printf("Front element is: %d\n", peekQueue(queue));
                        } else {
                            printf("Queue is empty!\n");
                        }
                        break;
                        
                    case 4:
                        displayQueue(queue);
                        break;
                        
                    case 5:
                        if (isQueueEmpty(queue)) {
                            printf("Queue is empty.\n");
                        } else {
                            printf("Queue is not empty.\n");
                        }
                        break;
                        
                    case 6:
                        if (isQueueFull(queue)) {
                            printf("Queue is full.\n");
                        } else {
                            printf("Queue is not full.\n");
                        }
                        break;
                        
                    case 7:
                        printf("Returning to implementation selection...\n");
                        break;
                        
                    default:
                        printf("Invalid choice. Please try again.\n");
                }
            } while (operationChoice != 7);
            
            // Free allocated memory before creating a new queue
            freeQueue(queue);
        }
    }
    
    printf("\nThank you for using the Data Structures program!\n");
    
    return 0;
}
