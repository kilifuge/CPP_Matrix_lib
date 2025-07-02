#include <gtest/gtest.h>

#include <limits>

#include "../s21_matrix_oop.h"

TEST(S21MatrixTest, DefaultConstructor) {
  S21Matrix m;
  EXPECT_EQ(m.get_rows(), 2);
  EXPECT_EQ(m.get_cols(), 2);
  S21Matrix expected(std::vector<std::vector<double>>{{0.0, 0.0}, {0.0, 0.0}});
  EXPECT_TRUE(m == expected);
}

TEST(S21MatrixTest, ParamConstructor) {
  S21Matrix m(3, 4);
  EXPECT_EQ(m.get_rows(), 3);
  EXPECT_EQ(m.get_cols(), 4);
  S21Matrix expected(std::vector<std::vector<double>>{
      {0.0, 0.0, 0.0, 0.0}, {0.0, 0.0, 0.0, 0.0}, {0.0, 0.0, 0.0, 0.0}});
  EXPECT_TRUE(m == expected);
}

TEST(S21MatrixTest, CopyConstructor) {
  S21Matrix m1(2, 2);
  m1(0, 0) = 1.0;
  m1(0, 1) = 2.0;
  m1(1, 0) = 3.0;
  m1(1, 1) = 4.0;
  S21Matrix m2(m1);
  EXPECT_TRUE(m1 == m2);
}

TEST(S21MatrixTest, MoveConstructor) {
  S21Matrix m1(2, 2);
  m1(0, 0) = 1.0;
  m1(0, 1) = 2.0;
  m1(1, 0) = 3.0;
  m1(1, 1) = 4.0;
  S21Matrix m2 = std::move(m1);
  S21Matrix expected(std::vector<std::vector<double>>{{1.0, 2.0}, {3.0, 4.0}});
  EXPECT_EQ(m2.get_rows(), 2);
  EXPECT_EQ(m2.get_cols(), 2);
  EXPECT_TRUE(m2 == expected);
}

TEST(S21MatrixTest, VectorConstructor) {
  std::vector<std::vector<double>> vec{{1.0, 2.0}, {3.0, 4.0}};
  S21Matrix m(vec);
  S21Matrix expected(std::vector<std::vector<double>>{{1.0, 2.0}, {3.0, 4.0}});
  EXPECT_EQ(m.get_rows(), 2);
  EXPECT_EQ(m.get_cols(), 2);
  EXPECT_TRUE(m == expected);
}

TEST(S21MatrixTest, AssignmentOperator) {
  S21Matrix m1(std::vector<std::vector<double>>{{1.0, 2.0}, {3.0, 4.0}});
  S21Matrix m2;
  m2 = m1;
  EXPECT_TRUE(m1 == m2);
}

TEST(S21MatrixTest, SumMatrix) {
  S21Matrix m1(std::vector<std::vector<double>>{{1.0, 2.0}, {3.0, 4.0}});
  S21Matrix m2(std::vector<std::vector<double>>{{2.0, 3.0}, {4.0, 5.0}});
  m1.SumMatrix(m2);
  S21Matrix expected(std::vector<std::vector<double>>{{3.0, 5.0}, {7.0, 9.0}});
  EXPECT_TRUE(m1 == expected);
}

TEST(S21MatrixTest, SumMatrix2) {
  S21Matrix m1(std::vector<std::vector<double>>{{1.0, 2.0}, {3.0, 4.0}});
  S21Matrix m2(
      std::vector<std::vector<double>>{{2.0, 3.0}, {4.0, 5.0}, {6.0, 7.0}});
  EXPECT_THROW(m1.SumMatrix(m2), std::runtime_error);
}

TEST(S21MatrixTest, SumMatrixInf) {
  S21Matrix m1(std::vector<std::vector<double>>{
      {std::numeric_limits<double>::max(), 2.0}, {3.0, 4.0}});
  S21Matrix m2(std::vector<std::vector<double>>{
      {std::numeric_limits<double>::max(), 3.0}, {4.0, 5.0}});
  EXPECT_THROW(m1.SumMatrix(m2), std::runtime_error);
}

TEST(S21MatrixTest, SubMatrix) {
  S21Matrix m1(std::vector<std::vector<double>>{{3.0, 3.0}, {3.0, 3.0}});
  S21Matrix m2(std::vector<std::vector<double>>{{1.0, 1.0}, {1.0, 1.0}});
  m1.SubMatrix(m2);
  S21Matrix expected(std::vector<std::vector<double>>{{2.0, 2.0}, {2.0, 2.0}});
  EXPECT_TRUE(m1 == expected);
}

TEST(S21MatrixTest, SubMatrix2) {
  S21Matrix m1(std::vector<std::vector<double>>{{1.0, 2.0}, {3.0, 4.0}});
  S21Matrix m2(
      std::vector<std::vector<double>>{{2.0, 3.0}, {4.0, 5.0}, {6.0, 7.0}});
  EXPECT_THROW(m1.SubMatrix(m2), std::runtime_error);
}

TEST(S21MatrixTest, SubMatrixInf) {
  S21Matrix m1(std::vector<std::vector<double>>{
      {std::numeric_limits<double>::max(), 2.0}, {3.0, 4.0}});
  S21Matrix m2(std::vector<std::vector<double>>{
      {-std::numeric_limits<double>::max(), 1.0}, {1.0, 1.0}});
  EXPECT_THROW(m1.SubMatrix(m2), std::runtime_error);
}

TEST(S21MatrixTest, MulNumber) {
  S21Matrix m(std::vector<std::vector<double>>{{1.0, 2.0}, {3.0, 4.0}});
  m.MulNumber(2.0);
  S21Matrix expected(std::vector<std::vector<double>>{{2.0, 4.0}, {6.0, 8.0}});
  EXPECT_TRUE(m == expected);
}

TEST(S21MatrixTest, MulNumber2) {
  S21Matrix m(std::vector<std::vector<double>>{{1.0, 2.0}, {3.0, 4.0}});
  double inf_number = std::numeric_limits<double>::max();
  EXPECT_THROW(m.MulNumber(inf_number), std::runtime_error);
}

TEST(S21MatrixTest, MulMatrix) {
  S21Matrix m1(
      std::vector<std::vector<double>>{{4.0, 2.0}, {7.0, 9.0}, {1.0, 4.0}});
  S21Matrix m2(
      std::vector<std::vector<double>>{{9.0, 1.0, 7.0}, {3.0, 7.0, 3.0}});
  m1.MulMatrix(m2);
  S21Matrix expected(std::vector<std::vector<double>>{
      {42.0, 18.0, 34.0}, {90.0, 70.0, 76.0}, {21.0, 29.0, 19.0}});
  EXPECT_TRUE(m1 == expected);
}

TEST(S21MatrixTest, MulMatrix2) {
  S21Matrix m1(std::vector<std::vector<double>>{{1.0, 2.0}, {3.0, 4.0}});
  S21Matrix m2(
      std::vector<std::vector<double>>{{2.0, 3.0}, {4.0, 5.0}, {6.0, 7.0}});
  EXPECT_THROW(m1.MulMatrix(m2), std::runtime_error);
}

TEST(S21MatrixTest, OperatorPlus) {
  S21Matrix m1(std::vector<std::vector<double>>{{1.0, 2.0}, {3.0, 4.0}});
  S21Matrix m2(std::vector<std::vector<double>>{{2.0, 3.0}, {4.0, 5.0}});
  S21Matrix result = m1 + m2;
  S21Matrix expected(std::vector<std::vector<double>>{{3.0, 5.0}, {7.0, 9.0}});
  EXPECT_TRUE(result == expected);
}

TEST(S21MatrixTest, OperatorPlus2) {
  S21Matrix m1(std::vector<std::vector<double>>{{1.0, 2.0}, {3.0, 4.0}});
  S21Matrix m2(
      std::vector<std::vector<double>>{{2.0, 3.0}, {4.0, 5.0}, {6.0, 7.0}});
  EXPECT_THROW(m1 + m2, std::runtime_error);
}

TEST(S21MatrixTest, OperatorPlusInf) {
  S21Matrix m1(std::vector<std::vector<double>>{
      {std::numeric_limits<double>::max(), 2.0}, {3.0, 4.0}});
  S21Matrix m2(std::vector<std::vector<double>>{
      {std::numeric_limits<double>::max(), 3.0}, {4.0, 5.0}});
  EXPECT_THROW(m1 + m2, std::runtime_error);
}

TEST(S21MatrixTest, OperatorMinus) {
  S21Matrix m1(std::vector<std::vector<double>>{{3.0, 3.0}, {3.0, 3.0}});
  S21Matrix m2(std::vector<std::vector<double>>{{1.0, 1.0}, {1.0, 1.0}});
  S21Matrix result = m1 - m2;
  S21Matrix expected(std::vector<std::vector<double>>{{2.0, 2.0}, {2.0, 2.0}});
  EXPECT_TRUE(result == expected);
}

TEST(S21MatrixTest, OperatorMinus2) {
  S21Matrix m1(std::vector<std::vector<double>>{{1.0, 2.0}, {3.0, 4.0}});
  S21Matrix m2(
      std::vector<std::vector<double>>{{2.0, 3.0}, {4.0, 5.0}, {6.0, 7.0}});
  EXPECT_THROW(m1 - m2, std::runtime_error);
}

TEST(S21MatrixTest, OperatorMinusInf) {
  S21Matrix m1(std::vector<std::vector<double>>{
      {std::numeric_limits<double>::max(), 2.0}, {3.0, 4.0}});
  S21Matrix m2(std::vector<std::vector<double>>{
      {-std::numeric_limits<double>::max(), 1.0}, {1.0, 1.0}});
  EXPECT_THROW(m1 - m2, std::runtime_error);
}

TEST(S21MatrixTest, OperatorMulMatrix) {
  S21Matrix m1(std::vector<std::vector<double>>{{1.0, 2.0}, {3.0, 4.0}});
  S21Matrix m2(std::vector<std::vector<double>>{{5.0, 6.0}, {7.0, 8.0}});
  S21Matrix result = m1 * m2;
  S21Matrix expected(
      std::vector<std::vector<double>>{{19.0, 22.0}, {43.0, 50.0}});
  EXPECT_TRUE(result == expected);
}

TEST(S21MatrixTest, OperatorMulMatrix2) {
  S21Matrix m1(std::vector<std::vector<double>>{{1.0, 2.0}, {3.0, 4.0}});
  S21Matrix m2(
      std::vector<std::vector<double>>{{2.0, 3.0}, {4.0, 5.0}, {6.0, 7.0}});
  EXPECT_THROW(m1 * m2, std::runtime_error);
}

TEST(S21MatrixTest, OperatorMulNumber) {
  S21Matrix m(std::vector<std::vector<double>>{{1.0, 2.0}, {3.0, 4.0}});
  S21Matrix result = m * 2.0;
  S21Matrix expected(std::vector<std::vector<double>>{{2.0, 4.0}, {6.0, 8.0}});
  EXPECT_TRUE(result == expected);
}

TEST(S21MatrixTest, OperatorMulNumber2) {
  S21Matrix m(std::vector<std::vector<double>>{{1.0, 2.0}, {3.0, 4.0}});
  double inf_number = std::numeric_limits<double>::max();
  EXPECT_THROW(m * inf_number, std::runtime_error);
}

TEST(S21MatrixTest, OperatorMulNumberInf) {
  S21Matrix m(std::vector<std::vector<double>>{{1.0, 2.0}, {3.0, 4.0}});
  double inf_number = std::numeric_limits<double>::max();
  EXPECT_THROW(m * inf_number, std::runtime_error);
}

TEST(S21MatrixTest, OperatorPlusEqual) {
  S21Matrix m1(std::vector<std::vector<double>>{{1.0, 2.0}, {3.0, 4.0}});
  S21Matrix m2(std::vector<std::vector<double>>{{2.0, 3.0}, {4.0, 5.0}});
  m1 += m2;
  S21Matrix expected(std::vector<std::vector<double>>{{3.0, 5.0}, {7.0, 9.0}});
  EXPECT_TRUE(m1 == expected);
}

TEST(S21MatrixTest, OperatorPlusEqual2) {
  S21Matrix m1(std::vector<std::vector<double>>{{1.0, 2.0}, {3.0, 4.0}});
  S21Matrix m2(
      std::vector<std::vector<double>>{{2.0, 3.0}, {4.0, 5.0}, {6.0, 7.0}});
  EXPECT_THROW(m1 += m2, std::runtime_error);
}

TEST(S21MatrixTest, OperatorPlusEqualInf) {
  S21Matrix m1(std::vector<std::vector<double>>{
      {std::numeric_limits<double>::max(), 2.0}, {3.0, 4.0}});
  S21Matrix m2(std::vector<std::vector<double>>{
      {std::numeric_limits<double>::max(), 3.0}, {4.0, 5.0}});
  EXPECT_THROW(m1 += m2, std::runtime_error);
}

TEST(S21MatrixTest, OperatorMinusEqual) {
  S21Matrix m1(std::vector<std::vector<double>>{{3.0, 3.0}, {3.0, 3.0}});
  S21Matrix m2(std::vector<std::vector<double>>{{1.0, 1.0}, {1.0, 1.0}});
  m1 -= m2;
  S21Matrix expected(std::vector<std::vector<double>>{{2.0, 2.0}, {2.0, 2.0}});
  EXPECT_TRUE(m1 == expected);
}

TEST(S21MatrixTest, OperatorMinusEqual2) {
  S21Matrix m1(std::vector<std::vector<double>>{{1.0, 2.0}, {3.0, 4.0}});
  S21Matrix m2(
      std::vector<std::vector<double>>{{2.0, 3.0}, {4.0, 5.0}, {6.0, 7.0}});
  EXPECT_THROW(m1 -= m2, std::runtime_error);
}

TEST(S21MatrixTest, OperatorMinusEqualInf) {
  S21Matrix m1(std::vector<std::vector<double>>{
      {std::numeric_limits<double>::max(), 2.0}, {3.0, 4.0}});
  S21Matrix m2(std::vector<std::vector<double>>{
      {-std::numeric_limits<double>::max(), 1.0}, {1.0, 1.0}});
  EXPECT_THROW(m1 -= m2, std::runtime_error);
}

TEST(S21MatrixTest, OperatorMulEqualMatrix) {
  S21Matrix m1(std::vector<std::vector<double>>{{1.0, 2.0}, {3.0, 4.0}});
  S21Matrix m2(std::vector<std::vector<double>>{{5.0, 6.0}, {7.0, 8.0}});
  m1 *= m2;
  S21Matrix expected(
      std::vector<std::vector<double>>{{19.0, 22.0}, {43.0, 50.0}});
  EXPECT_TRUE(m1 == expected);
}

TEST(S21MatrixTest, OperatorMulEqualMatrix2) {
  S21Matrix m1(std::vector<std::vector<double>>{{1.0, 2.0}, {3.0, 4.0}});
  S21Matrix m2(
      std::vector<std::vector<double>>{{2.0, 3.0}, {4.0, 5.0}, {6.0, 7.0}});
  EXPECT_THROW(m1 *= m2, std::runtime_error);
}

TEST(S21MatrixTest, OperatorMulEqualNumber) {
  S21Matrix m(std::vector<std::vector<double>>{{1.0, 2.0}, {3.0, 4.0}});
  m *= 2.0;
  S21Matrix expected(std::vector<std::vector<double>>{{2.0, 4.0}, {6.0, 8.0}});
  EXPECT_TRUE(m == expected);
}

TEST(S21MatrixTest, OperatorMulEqualNumber2) {
  S21Matrix m(std::vector<std::vector<double>>{{1.0, 2.0}, {3.0, 4.0}});
  double inf_number = std::numeric_limits<double>::max();
  EXPECT_THROW(m *= inf_number, std::runtime_error);
}

TEST(S21MatrixTest, OperatorMulEqualNumberInf) {
  S21Matrix m(std::vector<std::vector<double>>{{1.0, 2.0}, {3.0, 4.0}});
  double inf_number = std::numeric_limits<double>::max();
  EXPECT_THROW(m *= inf_number, std::runtime_error);
}

TEST(S21MatrixTest, Transpose) {
  S21Matrix m(
      std::vector<std::vector<double>>{{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}});
  S21Matrix result = m.Transpose();
  S21Matrix expected(
      std::vector<std::vector<double>>{{1.0, 4.0}, {2.0, 5.0}, {3.0, 6.0}});
  EXPECT_EQ(result.get_rows(), 3);
  EXPECT_EQ(result.get_cols(), 2);
  EXPECT_TRUE(result == expected);
}

TEST(S21MatrixTest, CalcComplements) {
  S21Matrix m(std::vector<std::vector<double>>{
      {1.0, 2.0, 3.0}, {0.0, 4.0, 2.0}, {5.0, 2.0, 1.0}});
  S21Matrix result = m.CalcComplements();
  S21Matrix expected(std::vector<std::vector<double>>{
      {0.0, 10.0, -20.0}, {4.0, -14.0, 8.0}, {-8.0, -2.0, 4.0}});
  EXPECT_TRUE(result == expected);
}

TEST(S21MatrixTest, CalcComplements2) {
  S21Matrix m(1, 1);
  S21Matrix result = m.CalcComplements();
  S21Matrix expected(std::vector<std::vector<double>>{{1.0}});
  EXPECT_TRUE(result == expected);
}

TEST(S21MatrixTest, CalcComplements3) {
  S21Matrix m(
      std::vector<std::vector<double>>{{1.0, 2.0, 3.0}, {0.0, 4.0, 2.0}});
  EXPECT_THROW(m.CalcComplements(), std::runtime_error);
}

TEST(S21MatrixTest, Determinant) {
  S21Matrix m(std::vector<std::vector<double>>{
      {1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}, {7.0, 8.0, 9.0}});
  double det = m.Determinant();
  EXPECT_NEAR(det, 0.0, EPS);
}

TEST(S21MatrixTest, Determinant2) {
  S21Matrix m(
      std::vector<std::vector<double>>{{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}});
  EXPECT_THROW(m.Determinant(), std::runtime_error);
}

TEST(S21MatrixTest, InverseMatrix) {
  S21Matrix m(std::vector<std::vector<double>>{
      {2.0, 5.0, 7.0}, {6.0, 3.0, 4.0}, {5.0, -2.0, -3.0}});
  S21Matrix result = m.InverseMatrix();
  S21Matrix expected(std::vector<std::vector<double>>{
      {1.0, -1.0, 1.0}, {-38.0, 41.0, -34.0}, {27.0, -29.0, 24.0}});
  EXPECT_TRUE(result == expected);
}

TEST(S21MatrixTest, InverseMatrix2) {
  S21Matrix m(std::vector<std::vector<double>>{{1.0}});
  S21Matrix result = m.InverseMatrix();
  S21Matrix expected(std::vector<std::vector<double>>{{1.0}});
  EXPECT_TRUE(result == expected);
}

TEST(S21MatrixTest, MatrixError) {
  S21Matrix m(std::vector<std::vector<double>>{{0.0, 0.0}, {0.0, 0.0}});
  EXPECT_THROW(m.InverseMatrix(), std::runtime_error);
}

TEST(S21MatrixTest, EqMatrix) {
  S21Matrix m1(std::vector<std::vector<double>>{{1.0, 2.0}, {3.0, 4.0}});
  S21Matrix m2(std::vector<std::vector<double>>{{1.0, 2.0}, {3.0, 4.0}});
  EXPECT_TRUE(m1.EqMatrix(m2));
}

TEST(S21MatrixTest, OperatorEqual) {
  S21Matrix m1(std::vector<std::vector<double>>{{1.0, 2.0}, {3.0, 4.0}});
  S21Matrix m2(std::vector<std::vector<double>>{{1.0, 2.0}, {3.0, 4.0}});
  EXPECT_TRUE(m1 == m2);
}

TEST(S21MatrixTest, PrintMatrixZaglushka) {
  S21Matrix m(std::vector<std::vector<double>>{{0.0, 0.0}, {0.0, 0.0}});
  m.PrintMatrix();
  EXPECT_TRUE(true);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}