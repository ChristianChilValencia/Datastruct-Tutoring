/**
 * Comprehensive Sorting Algorithms Implementation
 * This program demonstrates various sorting algorithms with detailed step-by-step visualization.
 * It combines the best features from multiple implementations with added improvements.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/**
 * Prints the elements of an array with step information
 * 
 * @param array The array to be printed
 * @param size The number of elements in the array
 * @param step The current step/pass number in the sorting process
 * @param algorithmName The name of the algorithm being used
 */
void printArray(int array[], int size, int step, const char* algorithmName) {
    printf("%s - Step %d: ", algorithmName, step);
    for (int i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

/**
 * Swaps two integers using pointers
 * 
 * @param a Pointer to the first integer
 * @param b Pointer to the second integer
 */
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

/**
 * Bubble Sort Algorithm
 * - Repeatedly steps through the list, compares adjacent elements
 *   and swaps them if they are in the wrong order
 * - Time Complexity: O(n²) in worst and average case, O(n) in best case
 * - Space Complexity: O(1)
 * - Stable: Yes (doesn't change the relative order of elements with equal values)
 * 
 * @param array The array to be sorted
 * @param size The number of elements in the array
 */
void bubbleSort(int array[], int size) {
    // Initialize step counter for tracking progress
    int step = 1;
    
    // Outer loop controls the number of passes needed (at most size-1)
    for (int i = 0; i < size - 1; i++) {
        // Flag to detect if any swaps were made in this pass
        int swapped = 0;
        
        // Inner loop performs comparisons and swaps
        // Note: With each pass, the largest unsorted element bubbles to the end
        // So we can reduce the inner loop range by i elements
        for (int j = 0; j < size - i - 1; j++) {
            // If current element is greater than the next element
            if (array[j] > array[j + 1]) {
                // Swap the elements
                swap(&array[j], &array[j + 1]);
                // Mark that a swap was made
                swapped = 1;
            }
        }
        
        // Print the array after each pass
        printArray(array, size, step++, "Bubble Sort");
        
        // Early termination: If no swaps were made in this pass,
        // the array is already sorted, so we can stop
        if (!swapped) {
            printf("Bubble Sort - Array is sorted after %d passes\n", i + 1);
            break;
        }
    }
}

/**
 * Selection Sort Algorithm
 * - Repeatedly finds the minimum element from the unsorted part and puts it at the beginning
 * - Time Complexity: O(n²) in all cases
 * - Space Complexity: O(1)
 * - Stable: No (can change the relative order of elements with equal values)
 * 
 * @param array The array to be sorted
 * @param size The number of elements in the array
 */
void selectionSort(int array[], int size) {
    // Step counter for tracking progress
    int step = 1;
    
    // Outer loop controls the boundary between sorted and unsorted sections
    for (int i = 0; i < size - 1; i++) {
        // Assume the current position has the minimum value
        int minIndex = i;
        
        // Find the minimum element in the unsorted part
        for (int j = i + 1; j < size; j++) {
            if (array[j] < array[minIndex]) {
                minIndex = j;
            }
        }
        
        // If minimum element is not at current position, swap elements
        if (minIndex != i) {
            swap(&array[i], &array[minIndex]);
        }
        
        // Print array after each placement of minimum element
        printArray(array, size, step++, "Selection Sort");
    }
}

/**
 * Insertion Sort Algorithm
 * - Builds the sorted array one element at a time
 * - Time Complexity: O(n²) in worst and average case, O(n) in best case
 * - Space Complexity: O(1)
 * - Stable: Yes
 * 
 * @param array The array to be sorted
 * @param size The number of elements in the array
 */
void insertionSort(int array[], int size) {
    // Step counter for tracking progress
    int step = 1;
    
    // Start from the second element (index 1)
    // First element (index 0) is considered already sorted
    for (int i = 1; i < size; i++) {
        // Store the current element as key
        int key = array[i];
        int j = i - 1;
        
        // Move elements greater than key one position ahead
        while (j >= 0 && array[j] > key) {
            array[j + 1] = array[j];
            j--;
        }
        
        // Place key at its correct position in sorted part
        array[j + 1] = key;
        
        // Print array after inserting each element
        printArray(array, size, step++, "Insertion Sort");
    }
}

/**
 * Merge function for Merge Sort
 * - Merges two sorted subarrays into one sorted array
 * 
 * @param array The array containing the subarrays to merge
 * @param left The starting index of the array
 * @param middle The middle index that divides the two subarrays
 * @param right The ending index of the array
 * @param step Current step counter for visualization
 */
void merge(int array[], int left, int middle, int right, int *step) {
    // Calculate sizes of the two subarrays
    int n1 = middle - left + 1;
    int n2 = right - middle;
    
    // Create temporary arrays to hold the subarrays
    int leftArray[n1], rightArray[n2];
    
    // Copy data to temporary arrays
    for (int i = 0; i < n1; i++)
        leftArray[i] = array[left + i];
    for (int j = 0; j < n2; j++)
        rightArray[j] = array[middle + 1 + j];
    
    // Merge the temporary arrays back into array[left..right]
    int i = 0;    // Initial index of first subarray
    int j = 0;    // Initial index of second subarray
    int k = left; // Initial index of merged subarray
    
    while (i < n1 && j < n2) {
        if (leftArray[i] <= rightArray[j]) {
            array[k] = leftArray[i];
            i++;
        } else {
            array[k] = rightArray[j];
            j++;
        }
        k++;
    }
    
    // Copy remaining elements of leftArray, if any
    while (i < n1) {
        array[k] = leftArray[i];
        i++;
        k++;
    }
    
    // Copy remaining elements of rightArray, if any
    while (j < n2) {
        array[k] = rightArray[j];
        j++;
        k++;
    }
    
    // Print the array after each merge operation
    printArray(array + left, right - left + 1, (*step)++, "Merge Sort");
}

/**
 * Merge Sort Algorithm
 * - Divides the array into halves, sorts them, and merges them back
 * - Time Complexity: O(n log n) in all cases
 * - Space Complexity: O(n)
 * - Stable: Yes
 * 
 * @param array The array to be sorted
 * @param left The starting index of the array
 * @param right The ending index of the array
 * @param step Pointer to step counter for tracking progress
 */
void mergeSort(int array[], int left, int right, int *step) {
    if (left < right) {
        // Find the middle point to divide the array into two halves
        int middle = left + (right - left) / 2;
        
        // Sort first and second halves recursively
        mergeSort(array, left, middle, step);
        mergeSort(array, middle + 1, right, step);
        
        // Merge the sorted halves
        merge(array, left, middle, right, step);
    }
}

/**
 * Partition function for Quick Sort
 * - Selects a pivot and places elements smaller than pivot to its left
 *   and elements greater than pivot to its right
 * 
 * @param array The array to be partitioned
 * @param low Starting index
 * @param high Ending index
 * @return The position of the pivot after partitioning
 */
int partition(int array[], int low, int high) {
    // Select the rightmost element as pivot
    int pivot = array[high];
    
    // Index of smaller element
    int i = low - 1;
    
    // Compare each element with pivot and swap if needed
    for (int j = low; j <= high - 1; j++) {
        // If current element is smaller than the pivot
        if (array[j] < pivot) {
            // Increment index of smaller element
            i++;
            swap(&array[i], &array[j]);
        }
    }
    
    // Place pivot in its correct position
    swap(&array[i + 1], &array[high]);
    
    // Return the partition index
    return i + 1;
}

/**
 * Quick Sort Algorithm
 * - Divides array around a pivot, with smaller elements to the left and larger to the right
 * - Time Complexity: O(n log n) average case, O(n²) worst case
 * - Space Complexity: O(log n) for recursive calls
 * - Stable: No
 * 
 * @param array The array to be sorted
 * @param low Starting index
 * @param high Ending index
 * @param step Pointer to step counter for tracking progress
 */
void quickSort(int array[], int low, int high, int *step) {
    if (low < high) {
        // Find the partition index
        int pivotIndex = partition(array, low, high);
        
        // Print array after partitioning
        printArray(array + low, high - low + 1, (*step)++, "Quick Sort");
        
        // Sort elements before and after partition
        quickSort(array, low, pivotIndex - 1, step);
        quickSort(array, pivotIndex + 1, high, step);
    }
}

/**
 * Heapify function for Heap Sort
 * - Converts a binary tree rooted at 'i' into a max-heap
 * 
 * @param array The array representing the binary tree
 * @param n Size of the heap
 * @param i Root index of the subtree to heapify
 */
void heapify(int array[], int n, int i) {
    // Initialize largest as root
    int largest = i;
    
    // Calculate indices of left and right children
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    
    // If left child exists and is larger than root
    if (left < n && array[left] > array[largest])
        largest = left;
    
    // If right child exists and is larger than current largest
    if (right < n && array[right] > array[largest])
        largest = right;
    
    // If largest is not root
    if (largest != i) {
        // Swap root with largest
        swap(&array[i], &array[largest]);
        
        // Recursively heapify the affected sub-tree
        heapify(array, n, largest);
    }
}

/**
 * Heap Sort Algorithm
 * - Creates a max-heap and repeatedly extracts maximum element
 * - Time Complexity: O(n log n) in all cases
 * - Space Complexity: O(1)
 * - Stable: No
 * 
 * @param array The array to be sorted
 * @param size The number of elements in the array
 */
void heapSort(int array[], int size) {
    int step = 1;
    
    // Build max heap
    for (int i = size / 2 - 1; i >= 0; i--)
        heapify(array, size, i);
    
    printArray(array, size, step++, "Heap Sort - After building max heap");
    
    // Extract elements one by one from heap
    for (int i = size - 1; i > 0; i--) {
        // Move current root (maximum element) to end
        swap(&array[0], &array[i]);
        
        // Call max heapify on the reduced heap
        heapify(array, i, 0);
        
        // Print array after each extraction
        printArray(array, size, step++, "Heap Sort");
    }
}

/**
 * Find the maximum element in an array
 * 
 * @param array The input array
 * @param size The number of elements in the array
 * @return The maximum value in the array
 */
int getMax(int array[], int size) {
    int max = array[0];
    for (int i = 1; i < size; i++)
        if (array[i] > max)
            max = array[i];
    return max;
}

/**
 * Counting Sort function for Radix Sort
 * - Sorts elements based on a specific digit place
 * 
 * @param array The array to be sorted
 * @param size The number of elements in the array
 * @param exp The current digit place value (1, 10, 100, etc.)
 */
void countingSort(int array[], int size, int exp) {
    // Define the radix (base) for counting sort
    const int RADIX = 10;
    
    // Create output array and count array
    int *output = (int *)malloc(size * sizeof(int));
    int count[RADIX] = {0};
    
    // Count occurrences of each digit at the specified place value
    for (int i = 0; i < size; i++)
        count[(array[i] / exp) % RADIX]++;
    
    // Update count to contain actual positions in output
    for (int i = 1; i < RADIX; i++)
        count[i] += count[i - 1];
    
    // Build the output array
    for (int i = size - 1; i >= 0; i--) {
        output[count[(array[i] / exp) % RADIX] - 1] = array[i];
        count[(array[i] / exp) % RADIX]--;
    }
    
    // Copy output array to original array
    for (int i = 0; i < size; i++)
        array[i] = output[i];
    
    // Free dynamically allocated memory
    free(output);
}

/**
 * Radix Sort Algorithm
 * - Sorts elements by processing individual digits from least to most significant
 * - Time Complexity: O(d * (n + k)) where d is the number of digits, n is array size, k is range
 * - Space Complexity: O(n + k)
 * - Stable: Yes
 * 
 * @param array The array to be sorted
 * @param size The number of elements in the array
 */
void radixSort(int array[], int size) {
    // Find the maximum number to determine number of digits
    int max = getMax(array, size);
    int step = 1;
    
    // Perform counting sort for every digit place (1s, 10s, 100s, etc.)
    for (int exp = 1; max / exp > 0; exp *= 10) {
        countingSort(array, size, exp);
        printArray(array, size, step++, "Radix Sort - Digit place value: 10^");
    }
}

/**
 * Generate a random array of integers
 * 
 * @param size The number of elements to generate
 * @param min The minimum possible value
 * @param max The maximum possible value
 * @return A dynamically allocated array of random integers
 */
int* generateRandomArray(int size, int min, int max) {
    int* array = (int*)malloc(size * sizeof(int));
    
    // Seed the random number generator
    srand((unsigned int)time(NULL));
    
    // Generate random values
    for (int i = 0; i < size; i++) {
        array[i] = min + rand() % (max - min + 1);
    }
    
    return array;
}

/**
 * Creates a copy of an array
 * 
 * @param source The source array to copy
 * @param size The number of elements in the array
 * @return A new array with the same elements as the source
 */
int* copyArray(int source[], int size) {
    int* copy = (int*)malloc(size * sizeof(int));
    
    for (int i = 0; i < size; i++) {
        copy[i] = source[i];
    }
    
    return copy;
}

/**
 * Print sorting algorithm time complexity information
 */
void printTimeComplexityInfo() {
    printf("\n====== SORTING ALGORITHMS TIME COMPLEXITY ======\n");
    printf("| Algorithm      | Best Case | Average Case | Worst Case |  Space | Stable |\n");
    printf("|----------------|-----------|--------------|------------|--------|--------|\n");
    printf("| Bubble Sort    | O(n)      | O(n²)        | O(n²)      |  O(1)  |   Yes  |\n");
    printf("| Selection Sort | O(n²)     | O(n²)        | O(n²)      |  O(1)  |   No   |\n");
    printf("| Insertion Sort | O(n)      | O(n²)        | O(n²)      |  O(1)  |   Yes  |\n");
    printf("| Merge Sort     | O(n log n)| O(n log n)   | O(n log n) |  O(n)  |   Yes  |\n");
    printf("| Quick Sort     | O(n log n)| O(n log n)   | O(n²)      |O(log n)|   No   |\n");
    printf("| Heap Sort      | O(n log n)| O(n log n)   | O(n log n) |  O(1)  |   No   |\n");
    printf("| Radix Sort     | O(n*k)    | O(n*k)       | O(n*k)     | O(n+k) |   Yes  |\n");
    printf("===================================================\n");
    printf("Note: n = number of elements, k = max number of digits\n\n");
}

/**
 * Main function - entry point of the program
 */
int main() {
    int *originalArray = NULL;
    int *workingArray = NULL;
    int size = 0;
    int choice = 0;
    int exit = 0;
    int step = 1; 
    
    printf("===== SORTING ALGORITHMS DEMONSTRATION =====\n\n");
    
    while (!exit) {
        printf("\nMAIN MENU:\n");
        
        // Display the current array if it exists
        if (originalArray != NULL) {
            printf("Current array: ");
            for (int i = 0; i < size; i++) {
                printf("%d ", originalArray[i]);
            }
            printf("\n\n");
        }
        
        printf("1. Enter array manually\n");
        printf("2. Generate random array\n");
        printf("3. Bubble Sort\n");
        printf("4. Selection Sort\n");
        printf("5. Insertion Sort\n");
        printf("6. Merge Sort\n");
        printf("7. Quick Sort\n");
        printf("8. Heap Sort\n");
        printf("9. Radix Sort\n");
        printf("10. View time complexity information\n");
        printf("11. Add a number to array\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1: // Enter array manually
                printf("How many numbers do you want to input? (1-100): ");
                scanf("%d", &size);
                
                if (size < 1 || size > 100) {
                    printf("Invalid size. Please enter a number between 1 and 100.\n");
                    break;
                }
                
                // Free previous arrays if they exist
                if (originalArray != NULL) free(originalArray);
                if (workingArray != NULL) free(workingArray);
                
                // Allocate new arrays
                originalArray = (int*)malloc(size * sizeof(int));
                
                printf("Enter %d numbers:\n", size);
                for (int i = 0; i < size; i++) {
                    scanf("%d", &originalArray[i]);
                }
                
                printf("Array entered successfully!\n");
                break;
                
            case 2: // Generate random array
                printf("How many numbers to generate? (1-100): ");
                scanf("%d", &size);
                
                if (size < 1 || size > 100) {
                    printf("Invalid size. Please enter a number between 1 and 100.\n");
                    break;
                }
                
                printf("Enter minimum value: ");
                int min;
                scanf("%d", &min);
                
                printf("Enter maximum value: ");
                int max;
                scanf("%d", &max);
                
                if (min > max) {
                    printf("Minimum value cannot be greater than maximum value.\n");
                    break;
                }
                
                // Free previous arrays if they exist
                if (originalArray != NULL) free(originalArray);
                if (workingArray != NULL) free(workingArray);
                
                // Generate new random array
                originalArray = generateRandomArray(size, min, max);
                
                printf("Random array generated:\n");
                for (int i = 0; i < size; i++) {
                    printf("%d ", originalArray[i]);
                }
                printf("\n");
                break;
                
            case 3: // Bubble Sort
                if (originalArray == NULL) {
                    printf("Please create an array first (Options 1 or 2).\n");
                    break;
                }
                
                // Create a copy of the original array for sorting
                if (workingArray != NULL) free(workingArray);
                workingArray = copyArray(originalArray, size);
                
                printf("\nOriginal array: ");
                for (int i = 0; i < size; i++) {
                    printf("%d ", workingArray[i]);
                }
                printf("\n\n");
                
                printf("=== BUBBLE SORT ===\n");
                bubbleSort(workingArray, size);
                
                printf("\nFinal sorted array: ");
                for (int i = 0; i < size; i++) {
                    printf("%d ", workingArray[i]);
                }
                printf("\n");
                break;
                
            case 4: // Selection Sort
                if (originalArray == NULL) {
                    printf("Please create an array first (Options 1 or 2).\n");
                    break;
                }
                
                // Create a copy of the original array for sorting
                if (workingArray != NULL) free(workingArray);
                workingArray = copyArray(originalArray, size);
                
                printf("\nOriginal array: ");
                for (int i = 0; i < size; i++) {
                    printf("%d ", workingArray[i]);
                }
                printf("\n\n");
                
                printf("=== SELECTION SORT ===\n");
                selectionSort(workingArray, size);
                
                printf("\nFinal sorted array: ");
                for (int i = 0; i < size; i++) {
                    printf("%d ", workingArray[i]);
                }
                printf("\n");
                break;
                
            case 5: // Insertion Sort
                if (originalArray == NULL) {
                    printf("Please create an array first (Options 1 or 2).\n");
                    break;
                }
                
                // Create a copy of the original array for sorting
                if (workingArray != NULL) free(workingArray);
                workingArray = copyArray(originalArray, size);
                
                printf("\nOriginal array: ");
                for (int i = 0; i < size; i++) {
                    printf("%d ", workingArray[i]);
                }
                printf("\n\n");
                
                printf("=== INSERTION SORT ===\n");
                insertionSort(workingArray, size);
                
                printf("\nFinal sorted array: ");
                for (int i = 0; i < size; i++) {
                    printf("%d ", workingArray[i]);
                }
                printf("\n");
                break;
                
            case 6: // Merge Sort
                if (originalArray == NULL) {
                    printf("Please create an array first (Options 1 or 2).\n");
                    break;
                }
                
                // Create a copy of the original array for sorting
                if (workingArray != NULL) free(workingArray);
                workingArray = copyArray(originalArray, size);
                
                printf("\nOriginal array: ");
                for (int i = 0; i < size; i++) {
                    printf("%d ", workingArray[i]);
                }
                printf("\n\n");
                
                printf("=== MERGE SORT ===\n");
                step = 1; // Reset step to 1
                mergeSort(workingArray, 0, size - 1, &step);
                
                printf("\nFinal sorted array: ");
                for (int i = 0; i < size; i++) {
                    printf("%d ", workingArray[i]);
                }
                printf("\n");
                break;
                
            case 7: // Quick Sort
                if (originalArray == NULL) {
                    printf("Please create an array first (Options 1 or 2).\n");
                    break;
                }
                
                // Create a copy of the original array for sorting
                if (workingArray != NULL) free(workingArray);
                workingArray = copyArray(originalArray, size);
                
                printf("\nOriginal array: ");
                for (int i = 0; i < size; i++) {
                    printf("%d ", workingArray[i]);
                }
                printf("\n\n");
                
                printf("=== QUICK SORT ===\n");
                step = 1; // Reset step to 1
                quickSort(workingArray, 0, size - 1, &step);
                
                printf("\nFinal sorted array: ");
                for (int i = 0; i < size; i++) {
                    printf("%d ", workingArray[i]);
                }
                printf("\n");
                break;
                
            case 8: // Heap Sort
                if (originalArray == NULL) {
                    printf("Please create an array first (Options 1 or 2).\n");
                    break;
                }
                
                // Create a copy of the original array for sorting
                if (workingArray != NULL) free(workingArray);
                workingArray = copyArray(originalArray, size);
                
                printf("\nOriginal array: ");
                for (int i = 0; i < size; i++) {
                    printf("%d ", workingArray[i]);
                }
                printf("\n\n");
                
                printf("=== HEAP SORT ===\n");
                heapSort(workingArray, size);
                
                printf("\nFinal sorted array: ");
                for (int i = 0; i < size; i++) {
                    printf("%d ", workingArray[i]);
                }
                printf("\n");
                break;
                
            case 9: // Radix Sort
                if (originalArray == NULL) {
                    printf("Please create an array first (Options 1 or 2).\n");
                    break;
                }
                
                // Create a copy of the original array for sorting
                if (workingArray != NULL) free(workingArray);
                workingArray = copyArray(originalArray, size);
                
                printf("\nOriginal array: ");
                for (int i = 0; i < size; i++) {
                    printf("%d ", workingArray[i]);
                }
                printf("\n\n");
                
                printf("=== RADIX SORT ===\n");
                radixSort(workingArray, size);
                
                printf("\nFinal sorted array: ");
                for (int i = 0; i < size; i++) {
                    printf("%d ", workingArray[i]);
                }
                printf("\n");
                break;
                
            case 10: // View time complexity information
                printTimeComplexityInfo();
                break;
                
            case 11: // Add a number to array
                if (originalArray == NULL) {
                    printf("Please create an array first (Options 1 or 2).\n");
                    break;
                }
                
                // Resize the array to add one more element
                size++;
                originalArray = (int*)realloc(originalArray, size * sizeof(int));
                
                printf("Enter the number to add: ");
                scanf("%d", &originalArray[size - 1]);
                
                printf("Number added successfully! Updated array:\n");
                for (int i = 0; i < size; i++) {
                    printf("%d ", originalArray[i]);
                }
                printf("\n");
                break;
                
            case 0: // Exit
                exit = 1;
                printf("Thank you for using the Sorting Algorithms Demonstration!\n");
                break;
                
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    
    // Free dynamically allocated memory before exiting
    if (originalArray != NULL) free(originalArray);
    if (workingArray != NULL) free(workingArray);
    
    return 0;
}
