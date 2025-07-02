#include "s21_matrix_oop.h"

S21Matrix S21Matrix::InverseMatrix() const {
  if (rows != columns) throw std::runtime_error("Матрица не квадратная");
  double det = Determinant();
  if (std::fabs(det) < EPS)
    throw std::runtime_error("Определитель матрицы равен 0.");
  if (rows == 1) return *this;
  S21Matrix result = CalcComplements();
  S21Matrix transPosed = result.Transpose();
  for (size_t i = 0; i < rows; i++) {
    for (size_t j = 0; j < columns; j++) {
      result.matrix[i][j] = transPosed.matrix[i][j] / det;
      if (std::isinf(result.matrix[i][j]))
        throw std::runtime_error("Ошибка вычисления обратной матрицы");
    }
  }
  return result;
}
