#include <stdio.h>

int main() {
    int matrices[2][3][3];
    int result[3][3];
    int i, j, k;

    // Input
    for (int m = 0; m < 2; ++m) {
        printf("Enter numbers for matrix %d:\n", m + 1);
        for (i = 0; i < 3; ++i) {
            for (j = 0; j < 3; ++j) {
                printf("Matrix %d - Row %d, Column %d: ", m + 1, i + 1, j + 1);
                scanf("%d", &matrices[m][i][j]);
            }
        }
    }

    // Multiply
    for (i = 0; i < 3; ++i) {
        for (j = 0; j < 3; ++j) {
            result[i][j] = 0;
            for (k = 0; k < 3; ++k) {
                result[i][j] += matrices[0][i][k] * matrices[1][k][j];
            }
        }
    }

    // Output
    for (int m = 0; m < 2; ++m) {
        printf("Matrix %d:\n", m + 1);
        for (i = 0; i < 3; ++i) {
            for (j = 0; j < 3; ++j) {
                printf("%d\t", matrices[m][i][j]);
            }
            printf("\n");
        }
        printf("\n");
    }

    printf("Result matrix:\n");
    for (i = 0; i < 3; ++i) {
        for (j = 0; j < 3; ++j) {
            printf("%d\t", result[i][j]);
        }
        printf("\n");
    }

    return 0;
}

