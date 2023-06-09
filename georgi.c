#include <stdio.h>
#include <stdlib.h>
#include "georgi.h"

// Function to create new matrix
float** create_matrix(int rows, int cols){
    float** new_matrix = (float**)malloc(rows * sizeof(float*));

    // Check if new matrix is allocated
    if(new_matrix == NULL){
        printf("New matrix cannot be created!\nMemory cannot be allocated\n");
        return NULL;
    }

    for(int i = 0; i < rows; i++){
        new_matrix[i] = (float*)malloc(cols * sizeof(float));

        // Check if matrix[i] is allocated, otherwise delete the matrix
        if(new_matrix[i] == NULL){
            printf("New matrix cannot be created!\nMemory cannot be allocated\n");

            for(int j = 0; j < i; j++){
                free(new_matrix[j]);
            }
            free(new_matrix);

            return NULL;
        }
    }

    return new_matrix;
}

// Function to perform matrix scalar multiplication
float **matrix_scalar_multiplication(float** matrix, int rows, int cols, float scalar){
    // Check if matrix exists
    if(matrix == NULL){
        printf("Matrix does not exist!\n");
        return NULL;
    }

    float **new_matrix = create_matrix(rows, cols);

    // Check if new matrix is allocated
    if(new_matrix == NULL){
        return NULL;
    }

    // matrix scalar multiplication
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            new_matrix[i][j] = matrix[i][j] * scalar;
        }
    }

    return new_matrix;
}


// Function to multiply matrices
float **matrices_multiplication(float** matrix1, int rows1, int cols1, float** matrix2, int rows2, int cols2){
    // Check if matrices exist
    if(matrix1 == NULL){
        printf("The first matrix does not exist!\n");
        return NULL;
    }
    if(matrix2 == NULL){
        printf("The second matrix does not exist!\n");
        return NULL;
    }

    // Check if columns of the first matrix are equal to the rows of the second matrix
    if(cols1 != rows2){
        printf("Matrices cannot be multiplied!\n");
        return NULL;
    }

    float **new_matrix = create_matrix(rows1, cols2);

    // Check if new matrix is allocated
    if(new_matrix == NULL){
        return NULL;
    }

    // Multiply two matrices
    for(int i = 0; i < rows1; i++){
        for(int j = 0; j < cols2; j++){
            new_matrix[i][j] = 0;
            for(int k = 0; k < cols1; k++){
                new_matrix[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }

    return new_matrix;
}

// Function to find determinant of a matrix with size up to 4x4
float matrix_determinant(float** matrix, int rows, int cols){
    // Check if the matrix is square
    if(rows != cols){
        printf("The matrix is not square!\n");
        return 1;
    }

    // Check if the matrix is bigger than 3x3
    if(rows > 3){
        printf("The matrix is too big!\n");
        return 1;
    }

    // Find the determinant
    switch(rows){
        // Determinant of 1x1 matrix (scalar)
        case 1:
            return matrix[0][0];

        // Determinant of 2x2 matrix
        case 2:
            return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];

        // Determinant of 3x3 matrix
        case 3:
            return matrix[0][0] * (matrix[1][1] * matrix[2][2] - matrix[1][2] * matrix[2][1]) -
                   matrix[0][1] * (matrix[1][0] * matrix[2][2] - matrix[1][2] * matrix[2][0]) +
                   matrix[0][2] * (matrix[1][0] * matrix[2][1] - matrix[1][1] * matrix[2][0]);
    }
}
