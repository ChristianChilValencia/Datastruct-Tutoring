#include <stdio.h>

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

int main() {
    int size, i, choice, pos, value;
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
                printf("Adios\n");
                break;
            default:
                printf("Invalid\n");
                break;
        }
    } while (choice != 5);
    return 0;
}
