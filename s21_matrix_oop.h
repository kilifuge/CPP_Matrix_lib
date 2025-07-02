#ifndef S21_MATRIX
#define S21_MATRIX

#include <cmath>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

#define EPS 1E-9

class S21Matrix {
  size_t rows{}, columns{};
  std::vector<std::vector<double>> matrix;

 public:
  // конструкторы и деструктор и функции для них
  S21Matrix(size_t rows = 2, size_t columns = 2);
  S21Matrix(const S21Matrix& other);
  S21Matrix(S21Matrix&& other);
  S21Matrix(const std::vector<std::vector<double>>& other);
  S21Matrix(std::vector<std::vector<double>>&& other);
  ~S21Matrix() = default;
  // получение переменных
  size_t get_rows() const { return rows; }
  size_t get_cols() const { return columns; }
  // остальные операторы
  S21Matrix& operator=(const S21Matrix& other);
  // арифметика + перегруженные арифметические операторы
  void SumMatrix(const S21Matrix& other);
  void SubMatrix(const S21Matrix& other);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix& other);
  S21Matrix operator+(const S21Matrix& other) const;
  S21Matrix operator-(const S21Matrix& other) const;
  S21Matrix operator*(const S21Matrix& other) const;
  S21Matrix operator*(double number) const;
  S21Matrix& operator+=(const S21Matrix& other);
  S21Matrix& operator-=(const S21Matrix& other);
  S21Matrix& operator*=(const S21Matrix& other);
  S21Matrix& operator*=(double number);
  // алг. дополнения и миноры
  S21Matrix CalcMinor(size_t expRow, size_t expColumn) const;
  double FindAlgebraicDop(size_t expRow, size_t expColumn) const;
  S21Matrix CalcComplements() const;
  // определитель
  double Determinant() const;
  // обратная матрица
  S21Matrix InverseMatrix() const;
  // остальные
  S21Matrix Transpose() const;
  bool operator==(const S21Matrix& other) const;
  bool EqMatrix(const S21Matrix& other) const;
  double& operator()(size_t ind1, size_t ind2);
  void PrintMatrix() const;
};

#endif
