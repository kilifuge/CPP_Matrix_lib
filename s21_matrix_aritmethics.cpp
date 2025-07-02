#include "s21_matrix_oop.h"

void S21Matrix::SumMatrix(const S21Matrix& other) {
  if ((columns != other.columns || rows != other.rows))
    throw std::runtime_error("различная размерность матриц.");
  for (size_t i = 0; i < rows; i++)
    for (size_t j = 0; j < columns; j++) {
      matrix[i][j] += other.matrix[i][j];
      if (std::isinf(matrix[i][j]))
        throw std::runtime_error("Ошибка вычислений при сложении");
    }
}

void S21Matrix::SubMatrix(const S21Matrix& other) {
  if ((columns != other.columns || rows != other.rows))
    throw std::runtime_error("различная размерность матриц.");
  for (size_t i = 0; i < rows; i++)
    for (size_t j = 0; j < columns; j++) {
      matrix[i][j] -= other.matrix[i][j];
      if (std::isinf(matrix[i][j]))
        throw std::runtime_error("Ошибка вычислений при сложении");
    }
}

void S21Matrix::MulMatrix(const S21Matrix& other) {
  if (columns != other.rows)
    throw std::runtime_error(
        "число столбцов первой матрицы не равно числу строк второй матрицы.");

  S21Matrix result(rows, other.columns);
  for (size_t i = 0; i < rows; i++)
    for (size_t j = 0; j < other.columns; j++) {
      for (size_t k = 0; k < columns; k++)
        result.matrix[i][j] += matrix[i][k] * other.matrix[k][j];
    }
  *this = result;
}

void S21Matrix::MulNumber(double number) {
  for (size_t i = 0; i < rows; i++)
    for (size_t j = 0; j < columns; j++) {
      matrix[i][j] *= number;
      if (std::isinf(matrix[i][j]))
        throw std::runtime_error("Ошибка вычислений при умножении на число");
    }
}

S21Matrix S21Matrix::operator+(const S21Matrix& other) const {
  if ((columns != other.columns || rows != other.rows))
    throw std::runtime_error("различная размерность матриц.");

  S21Matrix result(rows, columns);
  for (size_t i = 0; i < rows; i++)
    for (size_t j = 0; j < columns; j++) {
      result.matrix[i][j] = matrix[i][j] + other.matrix[i][j];
      if (std::isinf(result.matrix[i][j]))
        throw std::runtime_error("Ошибка вычислений при сложении");
    }
  return result;
}

S21Matrix S21Matrix::operator-(const S21Matrix& other) const {
  if ((columns != other.columns || rows != other.rows))
    throw std::runtime_error("различная размерность матриц.");

  S21Matrix result(rows, columns);
  for (size_t i = 0; i < rows; i++)
    for (size_t j = 0; j < columns; j++) {
      result.matrix[i][j] = matrix[i][j] - other.matrix[i][j];
      if (std::isinf(result.matrix[i][j]))
        throw std::runtime_error("Ошибка вычислений при вычитании");
    }
  return result;
}

S21Matrix S21Matrix::operator*(const S21Matrix& other) const {
  if (columns != other.rows)
    throw std::runtime_error(
        "число столбцов первой матрицы не равно числу строк второй матрицы.");

  S21Matrix result(rows, other.columns);
  for (size_t i = 0; i < rows; i++)
    for (size_t j = 0; j < other.columns; j++) {
      for (size_t k = 0; k < columns; k++)
        result.matrix[i][j] += matrix[i][k] * other.matrix[k][j];
    }
  return result;
}

S21Matrix S21Matrix::operator*(double number) const {
  S21Matrix result(rows, columns);
  for (size_t i = 0; i < rows; i++)
    for (size_t j = 0; j < columns; j++) {
      result.matrix[i][j] = matrix[i][j] * number;
      if (std::isinf(result.matrix[i][j]))
        throw std::runtime_error("Ошибка вычислений при умножении на число");
    }
  return result;
}

S21Matrix& S21Matrix::operator+=(const S21Matrix& other) {
  if ((columns != other.columns || rows != other.rows))
    throw std::runtime_error("различная размерность матриц.");

  for (size_t i = 0; i < rows; i++)
    for (size_t j = 0; j < columns; j++) {
      matrix[i][j] += other.matrix[i][j];
      if (std::isinf(matrix[i][j]))
        throw std::runtime_error("Ошибка вычислений при сложении");
    }
  return *this;
}

S21Matrix& S21Matrix::operator-=(const S21Matrix& other) {
  if ((columns != other.columns || rows != other.rows))
    throw std::runtime_error("различная размерность матриц.");

  for (size_t i = 0; i < rows; i++)
    for (size_t j = 0; j < columns; j++) {
      matrix[i][j] -= other.matrix[i][j];
      if (std::isinf(matrix[i][j]))
        throw std::runtime_error("Ошибка вычислений при сложении");
    }
  return *this;
}

S21Matrix& S21Matrix::operator*=(const S21Matrix& other) {
  if (columns != other.rows)
    throw std::runtime_error(
        "число столбцов первой матрицы не равно числу строк второй матрицы.");

  S21Matrix result(rows, other.columns);
  for (size_t i = 0; i < rows; i++)
    for (size_t j = 0; j < other.columns; j++) {
      for (size_t k = 0; k < columns; k++)
        result.matrix[i][j] += matrix[i][k] * other.matrix[k][j];
    }
  *this = result;
  return *this;
}

S21Matrix& S21Matrix::operator*=(double number) {
  for (size_t i = 0; i < rows; i++)
    for (size_t j = 0; j < columns; j++) {
      matrix[i][j] *= number;
      if (std::isinf(matrix[i][j]))
        throw std::runtime_error("Ошибка вычислений при умножении на число");
    }
  return *this;
}