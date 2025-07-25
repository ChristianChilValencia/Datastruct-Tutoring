#include <stdio.h>
int main(){
    int i, j, k;//i si row, j si column, extra para sa results si k
    int matrix[3][3];//unang matrix
    int matrix2[3][3];//kaduha
    int result[3][3];//mao ma resulta gamitun

    //pang butang sa una ka matrix
    printf("Enter numbers for the matrix:\n");
    for(i = 0; i < 3; ++i){
        for(j = 0; j < 3; ++j){
            printf("Row %d, Column %d: ", i+1, j+1);
            scanf("%d", &matrix[i][j]);
        }
    }
    //ibutang nimung kaduha
    printf("Enter numbers for the 2nd matrix:\n");
    for(i = 0; i < 3; ++i){
        for(j = 0; j < 3; ++j){
            printf("Row %d, Column %d: ", i+1, j+1);
            scanf("%d", &matrix2[i][j]);
        }
    }
    //maoy processo ni resulta gamit sa una og kaduha
    for(i = 0; i < 3; ++i){
        for(j = 0; j < 3; ++j){
            result[i][j] = 0;// declare sa una nga si resulta kay 0 sa ni row og column
            for (k = 0; k < 3; ++k) {//gamit kang k na para maka lihuk ta sa resulta
                result[i][j] += matrix[i][k] * matrix2[k][j];//ang resulta daw kay plus or equals sa unang matrix
                                                            //sa row pero ang k kay gi gamit as column daw nya 
                                                            //pariha ras kaduha nya i times nimu silang duha
        }
            printf("\n\n");
        }
    }

    printf("1st matrix:\n");//printa syas una
    for(i = 0; i < 3; ++i){
        for(j = 0; j < 3; ++j){
            printf("%d\t", matrix[i][j]);
        }
        printf("\n\n");
    }
    printf("2nd matrix:\n");//printa syas kaduha
    for(i = 0; i < 3; ++i){
        for(j = 0; j < 3; ++j){
            printf("%d\t", matrix2[i][j]);
        }
        printf("\n\n");
    }


    printf("THIS IS THE RESULT:\n");//printa syas resulta dayun
    for(i = 0; i < 3; ++i){
        for(j = 0; j < 3; ++j){
            printf("%d\t", result[i][j]);
        }   
            printf("\n\n");
    }
    return 0;
}