#include <iostream>

class MatrixFunctions {
public:
  // result = scalar * matrix
  void mat2Multiplication(int result[][3], const int matrix[][3], int scalar, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
        result[i][j] = scalar * matrix[i][j];
      }
    }
  }

  // result = mat1 * mat2
  void multiplyMatrices(int result[][2], const int mat1[][3], const int mat2[][2],
                        int rows1, int cols1, int rows2) {
    for (int i = 0; i < rows1; i++) {
      for (int j = 0; j < 2; j++) {
        result[i][j] = 0;   // initialize values
        for (int k = 0; k < cols1; k++) {
          result[i][j] += mat1[i][k] * mat2[k][j];
        }
      }
    }
  }

  // result = mat1 + mat2
  void addMatrices(int result[][2], const int mat1[][2], const int mat2[][2], int rows, int cols) {
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
        result[i][j] = mat1[i][j] + mat2[i][j];
      }
    }
  }

  // transpose a matrix
  void transposeMatrix(int result[][2], const int matrix[][3], int rows, int cols) {
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
        result[j][i] = matrix[i][j];
      }
    }
  }

  void printMatrix(const int result[][2], int rows, int cols) {
    for (int i = 0; i < rows; i++) {
      std::cout << "[ ";
      for (int j = 0; j < cols; j++) {
        std::cout << result[i][j] << " ";
      }
      std::cout << "]" << std::endl;
    }
  }
};

int main() {
  MatrixFunctions matrixObj;

  int A[2][2] = {
    {6, 4},
    {8, 3}
  };
  int B[2][3] = {
    {1, 2, 3},
    {4, 5, 6}
  };
  int C[2][3] = {
    {2, 4, 6},
    {1, 3, 5}
  };

  // Transpose C
  int cTransposed[3][2];
  matrixObj.transposeMatrix(cTransposed, C, 2, 3);

  // 3 * B
  int mat2Updated[2][3];
  matrixObj.mat2Multiplication(mat2Updated, B, 3, 2, 3);

  // mat2Updated * cTransposed
  int product[2][2];
  matrixObj.multiplyMatrices(product, mat2Updated, cTransposed, 2, 3, 3);

  // A + product
  int D[2][2];
  matrixObj.addMatrices(D, A, product, 2, 2);

  std::cout << "D = " << std::endl;
  matrixObj.printMatrix(D, 2, 2);

  return 0;
}
