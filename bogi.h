float** input_matrix(int* rows, int* colls);
void save_matrix(float** matrix, int rows, int colls, char* filename);
float** load_matrix(char* filename, int* rows, int* colls);
char* download(char* filename);
char* encrypt(char* array);
char* decrypt(char* array);
void upload(char* filename, char* array);
float** char_to_float(char* array, int* rows, int* colls);
char* float_to_char(float** matrix, int rows, int colls);
struct vector_t{
    char* array;
    int size;
    int capacity;
};
struct vector_t* init();
void append(struct vector_t* vector, char character);
void resize(struct vector_t* vector);
