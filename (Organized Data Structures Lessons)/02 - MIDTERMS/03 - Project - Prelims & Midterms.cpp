#include <stdio.h>
#include <stdlib.h>

//ARRAYS FUNCTIONS
int arrlinsearch(int arr[], int size, int value) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == value) {
            return i;
        }
    }
    return -1;
}
int arrbinsearch(int arr[], int size, int value) {
    int left = 0;
    int right = size - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (arr[mid] == value) {
            return mid;
        }

        if (arr[mid] < value) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return -1;
}
void arrinsert(int arr[], int *size, int pos, int value) {
    int i;
    for (i = *size - 1; i >= pos - 1; i--) {
        arr[i + 1] = arr[i];
    }
    arr[pos - 1] = value;
    (*size)++;
}
void arrdelete(int arr[], int *size, int pos) {
    int i;
    for (i = pos - 1; i < *size - 1; i++) {
        arr[i] = arr[i + 1];
    }
    (*size)--;
}
void arrdisplay(int arr[], int size) {
    printf("Current Array: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n\n");
}

//LINKED LIST FUNCTIONS
typedef struct node {
    int value;
    struct node *next;
} Node;
int listsearch(Node *head, int value) {
    int pos = 0;
    Node *current = head;
    while (current != NULL) {
        if (current->value == value) {
            return pos;
        }
        current = current->next;
        pos++;
    }
    return -1;
}
void listinsert(Node **head, int pos, int value) {
    Node *new_node = (Node*) malloc(sizeof(Node));
    new_node->value = value;
    if (pos == 0) {
        new_node->next = *head;
        *head = new_node;
    } else {
        Node *current = *head;
        for (int i = 0; i < pos - 1; i++) {
            current = current->next;
        }
        new_node->next = current->next;
        current->next = new_node;
    }
}
void listdelete(Node **head, int pos) {
    if (pos == 0) {
        Node *temp = *head;
        *head = (*head)->next;
        free(temp);
    } else {
        Node *current = *head;
        for (int i = 0; i < pos - 1; i++) {
            current = current->next;
        }
        Node *temp = current->next;
        current->next = temp->next;
        free(temp);
    }
}
void listdisplay(Node *head) {
    Node *current = head;
    printf("Current Linked List: ");
    while (current != NULL) {
        printf("%d ", current->value);
        current = current->next;
    }
    printf("\n");
}

//STACKS FUNCTIONS
typedef struct {
    int* data;
    int top;
    int max_size;
} Stack;
void initializeStack(Stack* stack) {
    stack->top = -1;
    stack->data = (int*) malloc(stack->max_size * sizeof(int));
}
int isEmpty(Stack* stack) {
    return stack->top == -1;
}
int isFull(Stack* stack) {
    return stack->top == stack->max_size - 1;
}
void push(Stack* stack, int value) {
    if (isFull(stack)) {
        printf("Stack is full. Cannot push %d.\n", value);
    } else {
        stack->data[++stack->top] = value;
    }
}
int pop(Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack is empty. Cannot pop.\n");
        return -1;
    } else {
        int poppedValue = stack->data[stack->top--];
        return poppedValue;
    }
}
void displayStack(Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack is empty.\n");
    } else {
        printf("Stack contents: ");
        for (int i = 0; i <= stack->top; i++) {
            printf("%d ", stack->data[i]);
        }
        printf("\n");
    }
}

//QUEUE FUNCTIONS
typedef struct {
    int* data;
    int front;
    int rear;
    int max_size;
} Queue;
void initializeQueue(Queue* queue) {
    queue->front = 0;
    queue->rear = -1;
    queue->data = (int*) malloc(queue->max_size * sizeof(int));
}
int isQueueEmpty(Queue* queue) {
    return queue->rear < queue->front;
}
int isQueueFull(Queue* queue) {
    return queue->rear == queue->max_size - 1;
}
void enqueue(Queue* queue, int value) {
    if (isQueueFull(queue)) {
        printf("Queue is full. Cannot enqueue %d.\n", value);
    } else {
        queue->data[++queue->rear] = value;
    }
}
int dequeue(Queue* queue) {
    if (isQueueEmpty(queue)) {
        printf("Queue is empty. Cannot dequeue.\n");
        return -1;
    } else {
        int dequeuedValue = queue->data[queue->front++];
        return dequeuedValue;
    }
}
void displayQueue(Queue* queue) {
    if (isQueueEmpty(queue)) {
        printf("Queue is empty.\n");
    } else {
        printf("Queue contents: ");
        for (int i = queue->front; i <= queue->rear; i++) {
            printf("%d ", queue->data[i]);
        }
        printf("\n");
    }
}

int main() {
    int size, i, choice, pos, value, num;
    while (1) {
        printf("\nMENU:\n");
        printf("1. Array Operations\n");
        printf("2. Linked List Operations\n");
        printf("3. Stacks\n");
        printf("4. Queues\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
			    if (choice == 1) {
			        printf("Enter array size: ");
			        scanf("%d", &size);
			        int arr[size];
			        printf("Enter array elements:\n");
			        for (i = 0; i < size; i++) {
			            scanf("%d", &arr[i]);
			        }
			        do {
			            printf("Array Operations:\n");
			            printf("1. Linear Search\n");
			            printf("2. Binary Search\n");
			            printf("3. Insert\n");
			            printf("4. Delete\n");
			            printf("5. Exit\n");
			            printf("Enter your choice: ");
			            scanf("%d", &choice);
			            switch (choice) {
			                case 1:
			                    printf("Enter element to search: ");
			                    scanf("%d", &value);
			                    pos = arrlinsearch(arr, size, value);
			                    if (pos == -1) {
			                        printf("Element not found\n");
			                    } else {
			                        printf("Number is in position %d\n", pos + 1);
			                    }
			                    arrdisplay(arr, size);
			                    break;
			                case 2:
			                    printf("Enter element to search (Binary Search): ");
			                    scanf("%d", &value);
			                    pos = arrbinsearch(arr, size, value);
			                    if (pos == -1) {
			                        printf("Element not found\n");
			                    } else {
			                        printf("Number is in position %d\n", pos + 1);
			                    }
			                    arrdisplay(arr, size);
			                    break;
			                case 3:
			                    printf("Insert Position: ");
			                    scanf("%d", &pos);
			                    printf("Insert Number: ");
			                    scanf("%d", &value);
			                    arrinsert(arr, &size, pos, value);
			                    arrdisplay(arr, size);
			                    break;
			                case 4:
			                    printf("Delete Position: ");
			                    scanf("%d", &pos);
			                    arrdelete(arr, &size, pos);
			                    arrdisplay(arr, size);
			                    break;
			                case 5:
			                    arrdisplay(arr, size);
			                    break;
			                default:
			                    printf("Invalid\n");
			                    break;
			            }
			        } while (choice != 5);
			    } 
                printf("\n\n");
                break;
            case 2:
				if (choice == 2) {
			        Node *head = NULL;
			        printf("Enter list size: ");
			        scanf("%d", &size);
			        printf("Enter list elements:\n");
			        for (i = 0; i < size; i++) {
			            scanf("%d", &value);
			            listinsert(&head, i, value);
			        }
			        do {
			            printf("Linked List Operations:\n");
			            printf("1. Search\n");
			            printf("2. Insert\n");
			            printf("3. Delete\n");
			            printf("4. Exit\n");
			            printf("Enter your choice: ");
			            scanf("%d", &choice);
			            switch (choice) {
			                case 1:
			                    printf("Enter element to search: ");
			                    scanf("%d", &value);
			                    pos = listsearch(head, value);
			                    if (pos == -1) {
			                        printf("Element not found\n");
			                        listdisplay(head);
			                    } else {
			                        printf("Number is in position %d\n", pos + 1);
			                    }
			                    listdisplay(head);
			                    break;
			                case 2:
			                    printf("Insert Position: ");
			                    scanf("%d", &pos);
			                    printf("Insert Number: ");
			                    scanf("%d", &value);
			                    listinsert(&head, pos - 1, value);
			                    listdisplay(head);
			                    break;
			                case 3:
			                    printf("Delete Position: ");
			                    scanf("%d", &pos);
			                    listdelete(&head, pos - 1);
			                    listdisplay(head);
			                    break;
			                case 4:
			                    listdisplay(head);
			                    break;
			                default:
			                    printf("Invalid\n");
			                    listdisplay(head);
			                    break;
			            }
			        } while (choice != 4);
			    }    
                printf("\n\n");
                break;
            case 3:
                printf("Enter the maximum size of the stack: ");
                scanf("%d", &size);
                Stack stack;
                stack.top = -1;
                stack.max_size = size;
                stack.data = (int*) malloc(stack.max_size * sizeof(int));
                initializeStack(&stack);
                while (1) {
                    printf("\nStack Operations:\n");
                    printf("1. Push\n");
                    printf("2. Pop\n");
                    printf("3. Back to main menu\n");
                    printf("Enter your choice: ");
                    scanf("%d", &choice);
                    switch (choice) {
                        case 1:
                            printf("Enter value to push: ");
                            scanf("%d", &value);
                            push(&stack, value);
                            displayStack(&stack);
                            break;
                        case 2:
                            pop(&stack);
                            displayStack(&stack);
                            break;
                        case 3:
                            displayStack(&stack);
                            break;
                        default:
                            printf("Invalid choice. Please try again.\n");
                            displayStack(&stack);
                    }
                    if (choice == 3) {
                        break;
                    }
                }
                break;
            case 4:
                printf("Enter the maximum size of the queue: ");
                scanf("%d", &size);
                Queue queue;
                queue.front = 0;
                queue.rear = -1;
                queue.max_size = size;
                queue.data = (int*) malloc(queue.max_size * sizeof(int));
                initializeQueue(&queue);
                while (1) {
                    printf("\nQueue Operations:\n");
                    printf("1. Enqueue\n");
                    printf("2. Dequeue\n");
                    printf("3. Back to main menu\n");
                    printf("Enter your choice: ");
                    scanf("%d", &choice);

                    switch (choice) {
                        case 1:
                            printf("Enter value to enqueue: ");
                            scanf("%d", &value);
                            enqueue(&queue, value);
                            displayQueue(&queue);
                            break;
                        case 2:
                            dequeue(&queue);
                            displayQueue(&queue);
                            break;
                        case 3:
                            displayQueue(&queue);
                            break;
                        default:
                            printf("Invalid choice. Please try again.\n");
                            displayQueue(&queue);
                    }
                    if (choice == 3) {
                        break;
                    }
                }
                break;
            case 5:
                printf("ADIOS AMIGO...");
                return 0;

            default:
                printf("Invalid choice. Try again.\n");
        }
    }
    return 0;
}
