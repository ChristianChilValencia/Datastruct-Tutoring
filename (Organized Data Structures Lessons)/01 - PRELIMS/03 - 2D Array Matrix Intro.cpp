#include <stdio.h>
int main(){
    int i, j, n;
    int matrix[3][3];
    printf("Enter numbers for the matrix:\n");
    for(i = 0; i < 3; ++i){
        for(j = 0; j < 3; ++j){
            printf("Row %d, Column %d: ", i+1, j+1);
            scanf("%d", &matrix[i][j]);
        }
    }

    for(i = 0; i < 3; ++i){
        printf("\n\n");
        for(j = 0; j < 3; ++j){
            printf("%d\t", matrix[i][j]);
        }
        printf("\n\n");
    }

    return 0;
}