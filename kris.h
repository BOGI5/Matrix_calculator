float** allocateMatrix(int rows, int columns);

void deallocateMatrix(float*** matrix, int rows);

float** identityMatrix(int size);

int compareMatrices(float** matrix1, float** matrix2, int size);

int isInvertible(float** matrixA, float** matrixB, int size);

float** divideByScalar(float** matrix, int rows, int columns, float scalar);

float** transpose(float** matrix, int rows, int columns);

float** invert(float** matrix, int rows, int columns);


/* funkcii na joro


float** multiplyByScalar(float** matrix, int rows, int columns, float scalar);

float** multiplyByMatrix(float** matrix1, float** matrix2, int rows1, int columns1rows2, int columns2);

float determinantOf(float** matrix, int rows, int columns);

*/
