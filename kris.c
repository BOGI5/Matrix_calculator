#include <stdio.h>
#include <stdlib.h>

#include "kris.h"

// private function for matrix memory allocation to prevent code repetition
float** allocateMatrix(int rows, int columns) {
    float** matrix = (float**)malloc(rows * sizeof(float*));
    for(int i = 0; i < rows; i++) {
        matrix[i] = (float*)malloc(columns * sizeof(float));
    }
    return matrix;
}

// private function for freeing matrix memory to prevent code repetition
void deallocateMatrix(float*** matrix, int rows) {
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

// private function to check if two matrices are identical
int compareMatrices(float** matrix1, float** matrix2, int size) {
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            if(matrix1[i][j] != matrix2[i][j]) {
                return 0;
            }
        }
    }

    return 1;
}

// private function that checks if a matrix is invertible 
int isInvertible(float** matrixA, float** matrixB, int size) {
    float** result1 = multiplyByMatrix(matrixA, matrixB, size, size, size);
    float** result2 = multiplyByMatrix(matrixB, matrixA, size, size, size);

    // if the original matrix multiplied by the temporary inverse matrix and vice versa is equal to the identity matrix and the determinant of the original matrix is not 0 it is invertible
    if(compareMatrices(result1, result2, size) == 1 && determinantOf(matrixA, size, size) != 0) {
        return 1;
    }

    return 0;
}

// function that returns a matrix divided by a scalar
float** divideByScalar(float** matrix, int rows, int columns, float scalar) {
    float** dividedMatrix = allocateMatrix(rows, columns);

    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < columns; j++) {
            dividedMatrix[i][j] = matrix[i][j] / scalar;
        }
    }

    return dividedMatrix;
}

// function that returns a transposed matrix
float** transpose(float** matrix, int rows, int columns) {
    // allocate memory for the transposed matrix
    float** transposedMatrix = allocateMatrix(columns, rows);

    // transposes the values
    for(int i = 0; i < columns; i++) {
        for(int j = 0; j < rows; j++) {
            transposedMatrix[i][j] = matrix[j][i];
        }
    }

    return transposedMatrix;
}

// function that returns an inverse matrix
float** invert(float** matrix, int rows, int columns) {
    // only square matrices can be inverted
    if(columns != rows) {
        printf("Error! Matrix is not square and cannot be inversed!\n");
        return NULL;
    }
    
    if(rows < 2 || rows > 4) {
        printf("Error! Matrix size must be between 2x2 and 4x4!\n");
        return NULL;
    }
    
    if(rows == 3) {
        // algorithm: https://www.mathsisfun.com/algebra/matrix-inverse-minors-cofactors-adjugate.html
        float** inverseMatrix = allocateMatrix(rows, columns);

        // creates a matrix of minors - each member is determinant of the rest that are not in the same row and column
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

                        temp[currentRowIndex][currentColumnIndex++] = matrix[k][l];
                    }
                    currentRowIndex++;
                }

                inverseMatrix[i][j] = /*determinantOf(temp, rows - 1, columns - 1)*/ 1;
                deallocateMatrix(temp, rows - 1);
            }
        }
        
        // the matrix of minors is turned into matrix of cofactors by applying this pattern:
        // + - + -
        // - + - +
        // + - + -
        // - + - +
        // to it
        for(int i = 0; i < rows; i++) {
            for(int j = 0; j < columns; j++) {
                if(i % 2 == 0 && j % 2 == 1 || i % 2 == 1 && j % 2 == 0) {
                    inverseMatrix[i][j] *= -1;
                }
            }
        }
        
        // then the matrix is transposed
        transpose(inverseMatrix, rows, columns);
        
        // and lastly the matrix is multiplied by the determinant of the original matrix
        //multiplyByScalar(inverseMatrix, rows, columns, 1 / determinantOf(matrix, rows, columns));
        
        // checks if the matrix is invertible because not all square matrices are invertible
        if(isInvertible(matrix, inverseMatrix, rows) == 0) {
            printf("Error! Matrix is not invertible\n");
            deallocateMatrix(inverseMatrix, rows);
            return NULL;
        }
        
        return inverseMatrix;
    }

    return NULL;
}
