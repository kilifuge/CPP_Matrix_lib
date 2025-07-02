#include "s21_matrix_oop.h"

S21Matrix::S21Matrix(size_t rows, size_t columns)
    : rows{rows}, columns{columns}, matrix(rows, std::vector<double>(columns)) {
  if (rows <= 0 || columns <= 0 || rows > 1000 || columns > 1000)
    throw std::runtime_error("Неправильный размер матрицы");
}

S21Matrix::S21Matrix(const S21Matrix& other)
    : rows{other.rows}, columns{other.columns}, matrix{other.matrix} {}

S21Matrix::S21Matrix(S21Matrix&& other)
    : rows{other.rows},
      columns{other.columns},
      matrix{std::move(other.matrix)} {}

S21Matrix::S21Matrix(std::vector<std::vector<double>>&& other)
    : rows{static_cast<size_t>(other.size())},
      columns{static_cast<size_t>(other[0].size())},
      matrix{std::move(other)} {
  if (matrix.empty()) throw std::runtime_error("Пустая матрица");
  for (size_t i{}; i < matrix.size(); i++)
    if (matrix[i].size() != columns) throw std::runtime_error("Не матрица");
}

S21Matrix::S21Matrix(const std::vector<std::vector<double>>& other)
    : rows{static_cast<size_t>(other.size())},
      columns{static_cast<size_t>(other[0].size())},
      matrix{other} {
  if (matrix.empty()) throw std::runtime_error("Пустая матрица");
  for (size_t i{}; i < matrix.size(); i++)
    if (matrix[i].size() != columns) throw std::runtime_error("Не матрица");
}

S21Matrix& S21Matrix::operator=(const S21Matrix& other) {
  rows = other.rows;
  columns = other.columns;
  matrix = other.matrix;
  for (size_t i{}; i < matrix.size(); i++) matrix[i].shrink_to_fit();
  matrix.shrink_to_fit();
  return *this;
}
