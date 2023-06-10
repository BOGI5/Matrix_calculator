#include <stdio.h>
#include <stdlib.h>
#include "bogi.h"


float** input_matrix(int* rows, int* colls)
{
    int check = 0;
    do {
        if(check)printf("Number of rows must be between 1 and 3!\n");
        check = 1;
        printf("Input the number of rows: ");
        scanf("%d", rows);
    }while(*rows >= 4 || *rows <= 0);
    check = 0;
    do {
        if(check)printf("Number of colls must be between 1 and 3!\n");
        check = 1;
        printf("Input the number of colls: ");
        scanf("%d", colls);
    }while(*colls >= 4 || *colls <= 0);
    float** matrix = (float**) malloc(sizeof(float*) * *rows);
    for(int i = 0; i < *rows; i++)
    {
        matrix[i] = (float*)malloc(sizeof(float) * *colls);
        for(int j = 0; j < *colls; j++)
        {
            printf("Input [%d][%d]: ", i, j);
            scanf("%f", &matrix[i][j]);
        }
    }
    return matrix;
}


void save_matrix(float** matrix, int rows, int colls, char* filename)
{
    upload(filename, encrypt(float_to_char(matrix, rows, colls)));
}


float** load_matrix(char* filename, int* rows, int* colls)
{
    return char_to_float(decrypt(download(filename)), rows, colls);
}


char* download(char* filename)
{
    FILE* file = fopen(filename, "r");
    if(!file)
    {
        printf("No such file or directory! (%s)\n", filename);
        return NULL;
    }
    char *array = (char*)malloc(sizeof(char) * 100);
    struct vector_t* vector = init();
    while(fgets(array, 100, file))
    {
        for(int i = 0; array[i] != '\0'; i++)
        {
            append(vector, array[i]);
        }
    }
    fclose(file);
    return vector->array;
}


char* encrypt(char* array)
{
    char* key = (char*)malloc(sizeof(char) * 100);
    printf("Input the key: ");
    scanf("%s", key);
    int size = 0;
    for(; array[size] != '\0'; size++);
    for(int i = 1; key[i] != '\0'; i++)
    {
        *key |= key[i];
    }
    for(int i = 0; i < size; i++)
    {
        array[i] = array[i] ^ *key;
        array[i] = ~array[i];
    }
    return array;
}


char* decrypt(char* array)
{
    char* key = (char*)malloc(sizeof(char) * 100);
    printf("Input the key: ");
    scanf("%s", key);
    int size = 0;
    for(; array[size] != '\0'; size++);
    for(int i = 1; key[i] != '\0'; i++)
    {
        *key |= key[i];
    }
    for(int i = 0; array[i] != '\0'; i++)
    {
        array[i] = ~array[i];
        array[i] = array[i] ^ *key;
    }
    return array;
}


// create matrix from char array
float** char_to_float(char* array, int* rows, int* colls)
{
    *colls = 0, *rows = 0;
    int idx = 0;
    for(int i = 0; array[i] != '\0'; i++)
    {
        if(array[i] == ';')*colls += 1;
        else if(array[i] == '\n')*rows += 1;
    }
    *colls /= *rows;
    float** matrix = (float**)malloc(sizeof(float*) * *rows);
    for(int i = 0; i < *rows; i++)
    {
        matrix[i] = (float*)malloc(sizeof(float) * *colls);
        for(int j = 0; j < *colls; j++)
        {
            matrix[i][j] = atof(&array[idx]);
            for(; array[idx] != ';'; idx++);
            idx += 1;
        }
    }
    return matrix;
}


// transform matrix to char array
char* float_to_char(float** matrix, int rows, int colls)
{
    struct vector_t* char_matrix = init();
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < colls; j++)
        {
            char* character = (char*)malloc(sizeof(char) * 100);
            sprintf(character, "%.*f", 2, matrix[i][j]);
            for(int x = 0; character[x] != '\0'; x++)
            {
                append(char_matrix, character[x]);
            }
            append(char_matrix, ';');
        }
        append(char_matrix, '\n');
    }
    return char_matrix->array;
}


void upload(char* filename, char* array)
{
    FILE* file = fopen(filename, "w");
    if(!file)
    {
        printf("No such file or directory! (%s)\n", filename);
        return;
    }
    fprintf(file, "%s", array);
    fclose(file);
}


struct vector_t* init()
{
    struct vector_t* vector = (struct vector_t*)malloc(sizeof(struct vector_t));
    vector->capacity = 2;
    vector->size = 0;
    vector->array = (char*)malloc(sizeof(char) * vector->capacity);
    return vector;
}


void append(struct vector_t* vector, char character)
{
    if(vector->size == vector->capacity)resize(vector);
    vector->array[vector->size] = character;
    vector->size += 1;
}


void resize(struct vector_t* vector)
{
    vector->capacity *= 2;
    char* array = (char*)malloc(sizeof(char) * vector->capacity);
    for(int i = 0; i < vector->size; i++)
    {
        array[i] = vector->array[i];
    }
    free(vector->array);
    vector->array = array;
}
