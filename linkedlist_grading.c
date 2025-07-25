#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define student node
struct Student {
    char name[50];
    int grade;
    struct Student* next;
};

// Function to create new student node
struct Student* createStudent(char name[], int grade) {
    struct Student* newStudent = (struct Student*)malloc(sizeof(struct Student));
    strcpy(newStudent->name, name);
    newStudent->grade = grade;
    newStudent->next = NULL;
    return newStudent;
}


// github tutorial chuchuhcu

// Insert student at the end
void addStudent(struct Student** head, char name[], int grade) {
    struct Student* newStudent = createStudent(name, grade);

    if (*head == NULL) {
        *head = newStudent;
        return;
    }

    struct Student* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newStudent;
}

// Delete student by name
void deleteStudent(struct Student** head, char name[]) {
    struct Student* temp = *head;
    struct Student* prev = NULL;

    while (temp != NULL && strcmp(temp->name, name) != 0) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Student '%s' not found.\n", name);
        return;
    }

    if (prev == NULL) {
        *head = temp->next;
    } else {
        prev->next = temp->next;
    }

    free(temp);
    printf("Student '%s' deleted successfully.\n", name);
}

// Search students by grade
void searchByGrade(struct Student* head, int grade) {
    int found = 0;
    printf("Students with grade %d:\n", grade);
    while (head != NULL) {
        if (head->grade == grade) {
            printf("Name: %s\n", head->name);
            found = 1;
        }
        head = head->next;
    }
    if (!found) {
        printf("No students with grade %d found.\n", grade);
    }
}

// Display all students
void displayAll(struct Student* head) {
    if (head == NULL) {
        printf("No students in the list.\n");
        return;
    }

    printf("All Students:\n");
    while (head != NULL) {
        printf("Name: %s | Grade: %d\n", head->name, head->grade);
        head = head->next;
    }
}

// Free memory
void freeList(struct Student* head) {
    struct Student* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

void clearScreen() {
    // Use "cls" for Windows or "clear" for Linux/Mac
    system("cls");  // For Windows
    // system("clear"); // Uncomment if using Linux/Mac
}

// Main program
int main() {
    struct Student* head = NULL;
    int choice, grade;
    char name[50];

    do {
        clearScreen();
        printf("\n--- Student Grading System ---\n");
        printf("1. Add Student\n");
        printf("2. Delete Student\n");
        printf("3. Search by Grade\n");
        printf("4. Display All Students\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Clear newline

        switch (choice) {
            case 1:
                printf("Enter name: ");
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = '\0'; // Remove newline
                printf("Enter grade: ");
                scanf("%d", &grade);
                addStudent(&head, name, grade);
                break;
            case 2:
                printf("Enter name to delete: ");
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = '\0';
                deleteStudent(&head, name);
                break;
            case 3:
                printf("Enter grade to search: ");
                scanf("%d", &grade);
                searchByGrade(head, grade);
                break;
            case 4:
                displayAll(head);
                break;
            case 5:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Try again.\n");
        }

    } while (choice != 5);

    freeList(head);
    return 0;
}
