#include <iostream>

class MatrixOperations {
    public:
        // free allocated memory
        static void deleteMatrix (int** matrix, int rows){
            for (int i = 0; i < rows; i++){
                delete [] matrix[i];    
            }
            delete[] matrix;
        }

        // create a new matrix
        static int** newMatrix (int rows, int cols){
            int **newMatrix = new int*[rows];   // allocates array of integer pointers
            for (int i = 0; i < rows; i++){
                newMatrix[i] = new int[cols]();  // integer array is allocated for current row
            }
            return newMatrix;   // return the new matrix
        }

        // perform scalar multiplication
        static int** scalarMultiply(int** matrix, int rows, int cols, int scalar){
            int **scaledMatrix = newMatrix(rows, cols); // matrix to store scaled result
            for (int i = 0; i < rows; i++){
                for (int j = 0; j < cols; j++){
                    scaledMatrix[i][j] = scalar * matrix[i][j]; // multiply all elements by scalar
                }
            }
            return scaledMatrix;
        }

        // transpose the matrix
        static int ** transposeMatrix(int** matrix, int rows, int cols){
            int** transposedMatrix = newMatrix(cols, rows);
            for (int i = 0; i < rows; i++){
                for (int j = 0; j < cols; j++){
                    transposedMatrix[j][i] = matrix[i][j];
                }
            }
            return transposedMatrix;    // return pointer to matrix
        }

        // check whether multiplication is possible
        static bool validMultiplication(int mat1cols, int mat2rows){
            // for two matrices to be multiplied first matrix num columns must equal second columns num of rows
            if (mat1cols != mat2rows){
                std::cout << "These two matrices cannot be multiplied" << std::endl;
                return false;   // invalid multiplication
            }
            return true;    // valid multiplication
        }
        
        // multiply two matrices
        static int** matrixMultiplication(int **matrix1, int** matrix2, int mat1rows, int mat1cols, int mat2rows, int mat2cols){
            int** productMatrix = newMatrix(mat1rows, mat2cols);
            if (validMultiplication(mat1cols, mat2rows)){
                for (int i = 0; i < mat1rows; i++){
                    for (int j = 0; j < mat2cols; j++){
                        productMatrix[i][j] = 0;    // initialize all values to zero
                        for (int k = 0; k < mat1cols; k++) {
                            productMatrix[i][j] += matrix1[i][k] * matrix2[k][j];   // perform matrix multiplication
                        }
                    }
                }
            }
            return productMatrix; // return pointer to matrix
        }
        
        static int** addMatrices(int **matrix1, int** matrix2, int rows, int cols){
            int** sumMatrix = newMatrix(rows, cols);    // new matrix containing summed values
            for (int i = 0; i < rows; i++){
                for (int j = 0; j < cols; j++){
                    sumMatrix[i][j] = matrix1[i][j] + matrix2[i][j];    // add elements
                }
            }
            return sumMatrix;
        }

        static void printMatrix(int** matrix, int rows, int cols){
            for (int i = 0; i < rows; i++){
                std::cout << "[ ";
                for (int j = 0; j < cols; j++){
                    std::cout << matrix[i][j] << ' ';
                }
                std::cout << " ]" << std::endl;
            }
        }
};

int main(){
    // test matrices
    int** A = MatrixOperations::newMatrix(2, 2);
    A[0][0] = 6; A[0][1] = 4;
    A[1][0] = 8; A[1][1] = 3;
    
    int** B = MatrixOperations::newMatrix(2, 3);
    B[0][0] = 1; B[0][1] = 2; B[0][2] = 3;
    B[1][0] = 4; B[1][1] = 5; B[1][2] = 6;
    
    int** C = MatrixOperations::newMatrix(2, 3);
    C[0][0] = 2; C[0][1] = 4; C[0][2] = 6;
    C[1][0] = 1; C[1][1] = 3; C[1][2] = 5;
    
    // D = A + (3 * B) * (C^T)
    int** cTransposed = MatrixOperations::transposeMatrix(C, 2, 3);
    int** scaledB = MatrixOperations::scalarMultiply(B, 2, 3, 3);
    int** product = MatrixOperations::matrixMultiplication(scaledB, cTransposed, 2, 3, 3, 2);
    int** D = MatrixOperations::addMatrices(A, product, 2, 2);
    
    std::cout << "D = " << std::endl;
    MatrixOperations::printMatrix(D, 2, 2); 
    return 0;
}
