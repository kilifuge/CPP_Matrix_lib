#include "s21_matrix_oop.h"

S21Matrix S21Matrix::Transpose() const {
  S21Matrix result(columns, rows);
  for (size_t i = 0; i < columns; i++) {
    for (size_t j = 0; j < rows; j++) {
      result.matrix[i][j] = matrix[j][i];
    }
  }
  return result;
}

bool S21Matrix::operator==(const S21Matrix& other) const {
  if (rows != other.rows && columns != other.columns) return false;
  for (size_t i = 0; i < rows; i++) {
    for (size_t j = 0; j < columns; j++)
      if (std::fabs(matrix[i][j] - other.matrix[i][j]) >= 1e-7) return false;
  }
  return true;
}

bool S21Matrix::EqMatrix(const S21Matrix& other) const {
  if (rows != other.rows && columns != other.columns) return false;
  for (size_t i = 0; i < rows; i++) {
    for (size_t j = 0; j < columns; j++)
      if (std::fabs(matrix[i][j] - other.matrix[i][j]) >= 1e-7) return false;
  }
  return true;
}

double& S21Matrix::operator()(size_t ind1, size_t ind2) {
  if (ind1 >= matrix.size() || ind2 >= matrix[0].size())
    throw std::runtime_error("Индекс за пределами матрицы.");
  return matrix[ind1][ind2];
}

void S21Matrix::PrintMatrix() const {
  for (size_t i{}; i < rows; i++) {
    for (size_t j{}; j < columns; j++) {
      std::cout << matrix[i][j] << ' ';
    }
    std::cout << std::endl;
  }
}