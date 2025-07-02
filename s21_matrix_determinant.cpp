#include "s21_matrix_oop.h"

double S21Matrix::Determinant() const {
  if (rows != columns)
    throw std::runtime_error("Матрица не является квадратной.");

  S21Matrix copy(*this);
  double result = 1.0;
  for (size_t i = 0; i < copy.columns - 1; i++) {
    size_t index = i;  // индекс строки с наиб. значением
    for (size_t j = i; j < copy.rows; j++) {
      if (fabs(copy.matrix[j][i]) > fabs(copy.matrix[index][i])) index = j;
    }
    if (fabs(copy.matrix[i][index]) < EPS) {
      result = 0.0;
    } else {
      if (index != i) {
        std::vector<double> tmp = copy.matrix[i];
        copy.matrix[i] = copy.matrix[index];
        copy.matrix[index] = tmp;
        result = -result;
      }
      for (size_t j = i + 1; j < copy.rows; j++) {
        double hz = copy.matrix[j][i] / copy.matrix[i][i];
        for (size_t k = i; k < copy.columns; k++) {
          copy.matrix[j][k] -= hz * copy.matrix[i][k];
        }
      }
    }
  }
  for (size_t i = 0; i < copy.rows; i++) result *= copy.matrix[i][i];
  if (std::isinf(result))
    throw std::runtime_error("Ошибка при вычислении определителя");
  return result;
}

/*
-
7 8 9
4 5 6
1 2 3
*/