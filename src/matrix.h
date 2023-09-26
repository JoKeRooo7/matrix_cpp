#ifndef MATRIX_CPP_MATRIX_H_
#define MATRIX_CPP_MATRIX_H_

#include <iostream>

namespace math {

const double kDoubleEps = 1E-15;

class Matrix {
 public:
  // constructors
  Matrix();
  Matrix(const Matrix &other);
  Matrix(Matrix &&other) noexcept;
  explicit Matrix(int rows, int cols);
  ~Matrix();
  // functions
  int GetRows() const noexcept;
  int GetColumns() const noexcept;
  void Clear() noexcept;
  void SetRows(int rows);
  void SetColumns(int cols);
  void SetRowsColumns(int rows, int cols);
  void MulNumber(const double num) noexcept;
  void SumMatrix(const Matrix &other);
  void SubMatrix(const Matrix &othet);
  void MulMatrix(const Matrix &other);
  bool EqMatrix(const Matrix &other) const noexcept;
  double Determinant() const;
  Matrix Transponse() const noexcept;
  Matrix InverseMatrix() const;
  Matrix CalcComplements() const;
  // operators
  bool operator!=(const Matrix &other) const noexcept;
  bool operator==(const Matrix &other) const noexcept;
  double &operator()(int i, int j);
  double operator()(int i, int j) const;
//   double *operator[](int row);
//   const double *operator[](int row) const;
  Matrix operator*(const Matrix &other) const;
  Matrix operator*(const double numbers) const;
  Matrix operator+(const Matrix &other) const;
  Matrix operator-(const Matrix &other) const;
  Matrix &operator*=(const Matrix &other);
  Matrix &operator*=(const double numbers);
  Matrix &operator+=(const Matrix &other);
  Matrix &operator-=(const Matrix &other);
  Matrix &operator=(const Matrix &other) noexcept;
  Matrix &operator=(Matrix &&other) noexcept;
  friend Matrix operator*(const double num, const Matrix& matrix);
  friend std::ostream &operator<<(std::ostream &os, const Matrix &other);
  friend std::istream &operator>>(std::istream &is, Matrix &other);

 private:
  int rows_{0}, cols_{0};
  double **matrix_{nullptr};
  void MatrixCreate() noexcept;
  void ResizeMatrix(int rows, int cols);
  void AssignMatrixCalcComp(Matrix &smaller_object, int el_rows,
                            int el_cols) const noexcept;
};

}  // namespace math

#endif  // MATRIX_CPP_MATRIX_H_
