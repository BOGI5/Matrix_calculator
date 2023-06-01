#include <stdio.h>
#include <stdlib.h>

#include "transpose.h"

void allocateMatrix(float** matrix, int rows, int columns) {
    matrix = (float**)malloc(rows * sizeof(float*));
    for(int i = 0; i < rows; i++) {
        matrix[i] = (float*)malloc(columns * sizeof(float));
    }
}

// float** allocateMatrix(int rows, int columns) {
//     float** matrix = (float**)malloc(rows * sizeof(float*));
//     for(int i = 0; i < rows; i++) {
//         matrix[i] = (float*)malloc(columns * sizeof(float));
//     }
//     return matrix;
// }

void freeMatrix(float** matrix, int rows) {
    for(int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

void transpose(float** matrix, int rows, int columns) {
    // creating a temp copy of the matrix to work with
    float** temp;
    allocateMatrix(temp, rows, columns);

    // copying the contents of the matrix
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < columns; j++) {
            temp[i][j] = matrix[i][j];
        }
    }

    // free the memory of the original matrix
    freeMatrix(matrix, rows);

    // allocationg memory for the matrix but with switched rows and columns
    allocateMatrix(temp, columns, rows);

    // transpose the numbers from temp into matrix
    for(int i = 0; i < columns; i++) {
        for(int j = 0; j < rows; j++) {
            matrix[i][j] = temp[j][i];
        }
    }

    // free temp
    freeMatrix(temp, rows);
}

void inverseOfAMatrix(float** matrix, int rows, int columns) {
    if(columns != rows) {
        printf("Error! Matrix is not square and cannot be inversed!\n");
        return;
    }
    
    if(rows > 4) {
        printf("Error! Matrix size cannot exceed 4x4!\n");
        return;
    }
    
    if(rows == 3) {
        float** matrixOfMinors;
        allocateMatrix(matrixOfMinors, rows, columns);

        for(int i = 0; i < rows; i++) {
            for(int j = 0; j < columns; j++) {
                float** temp;
                allocateMatrix(matrixOfMinors, rows - 1, columns - 1);
                
                for(int k = 0, currentRowIndex = 0; k < rows; k++) {
                    if(k == i) {
                        continue;
                    }
                    currentRowIndex++;

                    for(int l = 0, currentColumnIndex = 0; l < columns; l++) {
                        if(l == j) {
                            continue;
                        }
                        currentColumnIndex++;

                        temp[currentRowIndex][currentColumnIndex] = matrix[k][l];
                    }
                }

                matrixOfMinors[i][j] = determinantOfAMatrix(temp, rows - 1, columns - 1);
            }
        }
    }
}
