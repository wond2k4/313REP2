#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// free allocated memory
void deleteMatrix(int** matrix, int rows) {
    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

// create a new matrix
int** newMatrix(int rows, int cols) {
    int** newMatrix = (int**)malloc(rows * sizeof(int*));
    for (int i = 0; i < rows; i++) {
        newMatrix[i] = (int*)calloc(cols, sizeof(int));  // initialize to zero
    }
    return newMatrix;
}

// perform scalar multiplication
int** scalarMultiply(int** matrix, int rows, int cols, int scalar) {
    int** scaledMatrix = newMatrix(rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            scaledMatrix[i][j] = scalar * matrix[i][j];
        }
    }
    return scaledMatrix;
}

// transpose the matrix
int** transposeMatrix(int** matrix, int rows, int cols) {
    int** transposedMatrix = newMatrix(cols, rows);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            transposedMatrix[j][i] = matrix[i][j];
        }
    }
    return transposedMatrix;
}

// check whether multiplication is possible
bool validMultiplication(int mat1cols, int mat2rows) {
    // for two matrices to be multiplied first matrix num columns must equal second matrix num of rows
    if (mat1cols != mat2rows) {
        printf("These two matrices cannot be multiplied\n");
        return false;
    }
    return true;
}

// multiply two matrices
int** matrixMultiplication(int** matrix1, int** matrix2, int mat1rows, int mat1cols, int mat2rows, int mat2cols) {
    int** productMatrix = newMatrix(mat1rows, mat2cols);
    if (validMultiplication(mat1cols, mat2rows)) {
        for (int i = 0; i < mat1rows; i++) {
            for (int j = 0; j < mat2cols; j++) {
                productMatrix[i][j] = 0;  // initialize all values to zero
                for (int k = 0; k < mat1cols; k++) {
                    productMatrix[i][j] += matrix1[i][k] * matrix2[k][j];
                }
            }
        }
    }
    return productMatrix;
}

// add two matrices
int** addMatrices(int** matrix1, int** matrix2, int rows, int cols) {
    int** sumMatrix = newMatrix(rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            sumMatrix[i][j] = matrix1[i][j] + matrix2[i][j];
        }
    }
    return sumMatrix;
}

// print a matrix
void printMatrix(int** matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        printf("[ ");
        for (int j = 0; j < cols; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf(" ]\n");
    }
}

int main() {
    // test matrices
    int** A = newMatrix(2, 2);
    A[0][0] = 6; A[0][1] = 4;
    A[1][0] = 8; A[1][1] = 3;
    
    int** B = newMatrix(2, 3);
    B[0][0] = 1; B[0][1] = 2; B[0][2] = 3;
    B[1][0] = 4; B[1][1] = 5; B[1][2] = 6;
    
    int** C = newMatrix(2, 3);
    C[0][0] = 2; C[0][1] = 4; C[0][2] = 6;
    C[1][0] = 1; C[1][1] = 3; C[1][2] = 5;
    
    // D = A + (3 * B) * (C^T)
    int** cTransposed = transposeMatrix(C, 2, 3);
    int** scaledB = scalarMultiply(B, 2, 3, 3);
    int** product = matrixMultiplication(scaledB, cTransposed, 2, 3, 3, 2);
    int** D = addMatrices(A, product, 2, 2);
    
    printf("D = \n");
    printMatrix(D, 2, 2);
    
    // Free allocated memory
    deleteMatrix(A, 2);
    deleteMatrix(B, 2);
    deleteMatrix(C, 2);
    deleteMatrix(cTransposed, 3);
    deleteMatrix(scaledB, 2);
    deleteMatrix(product, 2);
    deleteMatrix(D, 2);
    
    return 0;
}
