#include <stdio.h>
#include <stdlib.h>

#include "transpose.h"

// private function for matrix memory allocation to prevent code repetition
float** allocateMatrix(int rows, int columns) {
    float** matrix = (float**)malloc(rows * sizeof(float*));
    for(int i = 0; i < rows; i++) {
        matrix[i] = (float*)malloc(columns * sizeof(float));
    }
    return matrix;
}

// private function for freeing matrix memory to prevent code repetition
void freeMatrix(float*** matrix, int rows) {
    for(int i = 0; i < rows; i++) {
        free((*matrix)[i]);
    }
    free(*matrix);
    *matrix = NULL;
}

// private function that generates an identity matrix
float** identityMatrix(int size) {
    // creates a new array
    float** identityMatrix = allocateMatrix(size, size);
    
    // filled with zeros
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            identityMatrix[i][j] = 0;
        }
    }
    
    // and ones on the diagonal
    for(int i = 0; i < size; i++) {
        identityMatrix[i][i] = 1;
    }
    
    return identityMatrix;
}

// private function that checks if a matrix is invertible - if the original matrix multiplied by the temporary inverse matrix and vice versa is equal to the identity matrix 
int isInvertible(float** matrixA, float** matrixB, int size) {
    if(umnojenieSMatrica(matrixA, size, size, matrixB) == umnojenieSMatrica(matrixB, size, size, matrixA) == identityMatrix(size) && determinant(matrixA) != 0) {
        return 1;
    }
    return 0;
}

void transpose(float*** matrix, int rows, int columns) {
    // creating a temp copy of the matrix to work with
    float** temp = allocateMatrix(rows, columns);

    // copying the contents of the matrix
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < columns; j++) {
            temp[i][j] = (*matrix)[i][j];
        }
    }

    // free the memory of the original matrix
    freeMatrix(*matrix, rows);

    // allocationg memory for the matrix but with switched rows and columns
    *matrix = allocateMatrix(columns, rows);

    // transpose the numbers from temp into matrix
    for(int i = 0; i < columns; i++) {
        for(int j = 0; j < rows; j++) {
            (*matrix)[i][j] = temp[j][i];
        }
    }

    // free temp
    freeMatrix(temp, rows);
}

void inverse(float*** matrix, int rows, int columns) {
    if(columns != rows) {
        printf("Error! Matrix is not square and cannot be inversed!\n");
        return;
    }
    
    if(rows > 4) {
        printf("Error! Matrix size cannot exceed 4x4!\n");
        return;
    }
    
    if(rows == 3) {
        float** inverse = allocateMatrix(rows, columns);

        for(int i = 0; i < rows; i++) {
            for(int j = 0; j < columns; j++) {
                float** temp = allocateMatrix(rows - 1, columns - 1);
                
                for(int k = 0, currentRowIndex = 0; k < rows; k++) {
                    if(k == i) {
                        continue;
                    }

                    for(int l = 0, currentColumnIndex = 0; l < columns; l++) {
                        if(l == j) {
                            continue;
                        }

                        temp[currentRowIndex][currentColumnIndex++] = (*matrix)[k][l];
                    }
                    currentRowIndex++;
                }

                inverse[i][j] = /*determinant(temp, rows - 1, columns - 1)*/ 1;
                freeMatrix(temp, rows - 1);
            }
        }
        
        for(int i = 0; i < rows; i++) {
            for(int j = 0; j < columns; j++) {
                if(i % 2 == 0 && j % 2 == 1 || i % 2 == 1 && j % 2 == 0) {
                    inverse[i][j] *= -1;
                }
            }
        }
        
        transpose(inverse, rows, columns);
        
        //umnojeniePoSkalar(inverse, rows, columns, 1 / determinant(*matrix, rows, columns));
        
        if(isInvertible(*matrix, inverse, size) == 0) {
           printf("Error! Matrix is not invertible\n");
           return;
        }
        
        for(int i = 0; i < rows; i++) {
            for(int j = 0; j < columns; j++) {
                (*matrix)[i][j] = inverse[i][j];
            }
        }
        freeMatrix(inverse, rows);
    }
}
