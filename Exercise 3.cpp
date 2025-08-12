#include <stdio.h>

int insert(int size, int a[], int temp, int element);
int delet(int size, int a[], int del);

int main(){
    int choice;
    int size;
    int element, temp;
    int del;

    printf("Enter the size first: ");
    scanf("%d", &size);
    printf("\n");

    int a[size]; 

    printf("Enter the integers: ");
    for(int i = 0; i < size; i++){
        scanf("%d", &a[i]);
    }
    printf("\n");

    do {
        printf("Menu:\n");
        printf("1. Insert\n");
        printf("2. Delete\n");
        printf("3. Exit\n\n");

        printf("Stored Integers: ");
        for(int i = 0; i < size; i++){
            printf("%d ", a[i]);
        }
        printf("\n\n");

        printf("Choose: ");
        scanf("%d", &choice);

        switch(choice){
            case 1:
                printf("Enter an element to insert: ");
                scanf("%d", &element);
                printf("Enter the position to insert: ");
                scanf("%d", &temp);
                temp--;

                if(temp < 0 || temp > size) {
                    printf("Invalid position!\n\n");
                    break;
                }

                size = insert(size, a, temp, element);

                printf("\n\n");
                break;

            case 2:
                printf("Enter an element to delete: ");
                scanf("%d", &del);
                size = delet(size, a, del);

                printf("After deletion: ");
                for(int i = 0; i < size; i++){
                    printf("%d ", a[i]);
                }
                printf("\n\n");
                break;

            case 3:
                printf("Thanks for using :)\n");
                break;

            default:
                printf("Not in the list\n\n");
                break;
        }
    } while(choice != 3);

    return 0;
}

int insert(int size, int a[], int temp, int element){
    for(int i = size - 1; i >= temp; i--){
        a[i + 1] = a[i];
    }
    a[temp] = element;
    return size + 1;
}

int delet(int size, int a[], int del){
    for(int i = 0; i < size; i++){
        if(a[i] == del){
            for(int j = i; j < size - 1; j++){
                a[j] = a[j + 1];
            }
            return size - 1;
        }
    }
    printf("Not found :(\n\n");
    return size;
}
