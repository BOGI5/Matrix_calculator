#include <stdio.h>
#include <stdlib.h>

#include "transpose.h"

void transpose(int** matrix, int rows, int columns) {
    // creating a temp copy of the matrix to work with
    int** temp = (int**)malloc(rows * sizeof(int*));
    for(int i = 0; i < rows; i++) {
        temp[i] = (int*)malloc(columns * sizeof(int));
    }

    // copying the contents of the matrix
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < columns; j++) {
            temp[i][j] = matrix[i][j];
        }
    }

    // free the memory of the original matrix
    for(int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);

    // allocationg memory for the matrix but with switched rows and columns
    matrix = (int**)malloc(columns * sizeof(int*));
    for(int i = 0; i < columns; i++) {
        matrix[i] = (int*)malloc(rows * sizeof(int));
    }

    // transpose the numbers from temp into matrix
    for(int i = 0; i < columns; i++) {
        for(int j = 0; j < rows; j++) {
            matrix[i][j] = temp[j][i];
        }
    }

    // free temp
    for(int i = 0; i < rows; i++) {
        free(temp[i]);
    }
    free(temp);
}
