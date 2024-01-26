#include "matrix.h"

#include <cmath>
#include <cstring>
#include <iostream>

namespace math {

void Matrix::MatrixCreate() noexcept {
  if (rows_ > 0 && cols_ > 0) {
    matrix_ = new double *[rows_];
    for (int i = 0; i < rows_; ++i) {
      matrix_[i] = new double[cols_]();
    }
  } else {
    rows_ = cols_ = 0;
  }
}

Matrix::Matrix() { MatrixCreate(); }

Matrix::Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  if (rows < 0 || cols < 0) {
    throw std::invalid_argument("Not correct dates");
  }
  MatrixCreate();
}

Matrix::Matrix(const Matrix &other) {
  rows_ = other.rows_;
  cols_ = other.cols_;
  MatrixCreate();
  for (int i = 0; i < rows_; ++i) {
    std::memcpy(matrix_[i], other.matrix_[i], cols_ * sizeof(double));
  }
}

Matrix::Matrix(Matrix &&other) noexcept {
  std::swap(matrix_, other.matrix_);
  std::swap(rows_, other.rows_);
  std::swap(cols_, other.cols_);
}

Matrix::~Matrix() { Clear(); }

int Matrix::GetRows() const noexcept { return rows_; }

int Matrix::GetColumns() const noexcept { return cols_; }

void Matrix::Clear() noexcept {
  if (matrix_ != nullptr) {
    for (int i = 0; i < rows_; ++i) {
      delete[] matrix_[i];
    }
    delete[] matrix_;
    matrix_ = nullptr;
  }
  rows_ = cols_ = 0;
}

void Matrix::SetRows(int rows) {
  if (rows != rows_) {
    ResizeMatrix(rows, cols_);
  }
}

void Matrix::SetColumns(int cols) {
  if (cols != cols_) {
    ResizeMatrix(rows_, cols);
  }
}

void Matrix::SetRowsColumns(int rows, int cols) {
  if (rows != rows_ && cols != cols_) {
    ResizeMatrix(rows, cols_);
  }
}

void Matrix::MulNumber(const double num) noexcept {
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] *= num;
    }
  }
}

void Matrix::SumMatrix(const Matrix &other) {
  if (rows_ != other.rows_ && cols_ != other.cols_) {
    throw std::invalid_argument("It matrix is not equal other matrix");
  }
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] += other.matrix_[i][j];
    }
  }
}

void Matrix::SubMatrix(const Matrix &other) {
  if (rows_ != other.rows_ && cols_ != other.cols_) {
    throw std::invalid_argument("It matrix is not equal other matrix");
  }
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] -= other.matrix_[i][j];
    }
  }
}

void Matrix::MulMatrix(const Matrix &other) {
  if (cols_ != other.rows_) {
    throw std::invalid_argument(
        "Error: this matrix cols != other matrix rows 1");
  }
  Matrix result(rows_, other.cols_);
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < other.cols_; ++j) {
      for (int k = 0; k < cols_; ++k) {
        result.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
      }
    }
  }
  *this = result;
}

bool Matrix::EqMatrix(const Matrix &other) const noexcept {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    return false;
  } else {
    for (int i = 0; i < rows_; ++i) {
      for (int j = 0; j < cols_; ++j) {
        if (fabs(matrix_[i][j] - other.matrix_[i][j]) > kDoubleEps) {
          return false;
        }
      }
    }
  }
  return true;
}

double Matrix::Determinant() const {
  if (rows_ != cols_) {
    throw std::invalid_argument("rows!= cols");
  }
  if (rows_ == 0 || cols_ == 0) {
    throw std::invalid_argument("rows = 0 or cols = 0");
  }
  Matrix new_object(rows_, cols_);
  for (int i = 0; i < rows_; ++i) {
    std::memcpy(new_object.matrix_[i], matrix_[i], cols_ * sizeof(double));
  }

  double coefficient = 0;
  short int sign = 1;
  for (int i = 0, j = 0; i < rows_; ++i) {
    for (j = i; j < rows_ && std::abs(new_object.matrix_[j][i]) < kDoubleEps;
         ++j)
      ;
    if (j == rows_) {
      return 0.0;
    } else if (j != i) {
      sign = -sign;
      std::swap(new_object.matrix_[i], new_object.matrix_[j]);
    }
    for (int j = i + 1; j < rows_; ++j) {
      coefficient = new_object.matrix_[j][i] / new_object.matrix_[i][i];
      for (int k = i; k < rows_; ++k) {
        new_object.matrix_[j][k] -= coefficient * new_object.matrix_[i][k];
      }
    }
  }
  double determinant = 1.0;
  for (int i = 0; i < rows_; ++i) {
    determinant *= new_object.matrix_[i][i];
  }

  return sign * determinant;
}

Matrix Matrix::Transponse() const noexcept {
  Matrix new_object(cols_, rows_);
  for (int i = 0; i < cols_; ++i) {
    for (int j = 0; j < rows_; ++j) {
      new_object.matrix_[i][j] = matrix_[j][i];
    }
  }

  return new_object;
}

Matrix Matrix::InverseMatrix() const {
  if (rows_ != cols_) {
    throw std::invalid_argument("rows is not equal cols");
  }
  Matrix new_object(rows_, cols_);
  if (rows_ > 1) {
    double det = Determinant();
    if (std::abs(det) < kDoubleEps) {
      throw std::invalid_argument("determinant is equal 0");
    } else {
      new_object = (CalcComplements().Transponse()) * (1 / det);
    }
  } else if (rows_ == 1) {
    new_object.matrix_[0][0] = 1 / matrix_[0][0];
  }

  return new_object;
}

Matrix Matrix::CalcComplements() const {
  if (rows_ != cols_) {
    throw std::invalid_argument("rows != cols\n");
  }
  Matrix new_object(rows_, cols_);
  if (rows_ > 1) {
    Matrix smaller_object(rows_ - 1, cols_ - 1);
    for (int i = 0; i < rows_; ++i) {
      for (int j = 0; j < cols_; ++j) {
        AssignMatrixCalcComp(smaller_object, i, j);
        new_object.matrix_[i][j] =
            std::pow(-1, i + j) * smaller_object.Determinant();
        if (new_object.matrix_[i][j] == -0) {
          new_object.matrix_[i][j] = 0;
        }
      }
    }
  } else if (rows_ == 1) {
    new_object.matrix_[0][0] = 1 / matrix_[0][0];
  }

  return new_object;
}

// Assigning one matrix to another by  new_object rank less
// el_rows - index elements main matrix
// el_cols - index elements main matrix
void Matrix::AssignMatrixCalcComp(Matrix &smaller_object, int el_rows,
                                  int el_cols) const noexcept {
  for (int i = 0, smaller_rows = 0; i < rows_; ++i) {
    if (i != el_rows) {
      for (int j = 0, smaller_cols = 0; j < cols_; ++j) {
        if (j != el_cols) {
          smaller_object.matrix_[smaller_rows][smaller_cols++] = matrix_[i][j];
        }
      }
      ++smaller_rows;
    }
  }
}

bool Matrix::operator!=(const Matrix &other) const noexcept {
  return !EqMatrix(other);
}

bool Matrix::operator==(const Matrix &other) const noexcept {
  return EqMatrix(other);
}

double &Matrix::operator()(int i, int j) {
  if (i < 0 || j < 0 || i >= rows_ || j >= cols_) {
    throw std::invalid_argument("There is no matrix element Matrix[" +
                                std::to_string(i) + ", " + std::to_string(j) +
                                "]\n");
  }

  return matrix_[i][j];
}

double Matrix::operator()(int i, int j) const {
  if (i < 0 || j < 0 || i >= rows_ || j >= cols_) {
    throw std::invalid_argument("There is no matrix element Matrix[" +
                                std::to_string(i) + ", " + std::to_string(j) +
                                "]\n");
  }

  return matrix_[i][j];
}

// double *Matrix::operator[](int row) {
//   if (row < 0 || row >= rows_) {
//     throw std::out_of_range("Invalid row index");
//   }
//   return matrix_[row];
// }

// const double *Matrix::operator[](int row) const {
//     if (row < 0 || row >= rows_) {
//     throw std::out_of_range("Invalid row index");
//   }
//   return matrix_[row];
// }

Matrix Matrix::operator*(const Matrix &other) const noexcept {
  Matrix new_object(*this);
  new_object *= other;
  return new_object;
}

Matrix Matrix::operator*(const double numbers) const noexcept {
  Matrix new_object(*this);
  new_object *= numbers;
  return new_object;
}

Matrix Matrix::operator+(const Matrix &other) const noexcept {
  Matrix new_object(*this);
  new_object += other;
  return new_object;
}

Matrix Matrix::operator-(const Matrix &other) const noexcept {
  Matrix new_object(*this);
  new_object -= other;
  return new_object;
}

Matrix &Matrix::operator*=(const Matrix &other) {
  MulMatrix(other);
  return *this;
}

Matrix &Matrix::operator*=(const double numbers) {
  MulNumber(numbers);
  return *this;
}

Matrix &Matrix::operator+=(const Matrix &other) {
  SumMatrix(other);
  return *this;
}

Matrix &Matrix::operator-=(const Matrix &other) {
  SubMatrix(other);
  return *this;
}

Matrix &Matrix::operator=(const Matrix &other) noexcept {
  if (this != &other) {
    this->Clear();
    rows_ = other.rows_;
    cols_ = other.cols_;
    MatrixCreate();
    for (int i = 0; i < rows_; ++i) {
      std::memcpy(matrix_[i], other.matrix_[i], cols_ * sizeof(double));
    }
  }

  return *this;
}

Matrix &Matrix::operator=(Matrix &&other) noexcept {
  if (this != &other) {
    this->Clear();
    std::swap(matrix_, other.matrix_);
    std::swap(rows_, other.rows_);
    std::swap(cols_, other.cols_);
  }

  return *this;
}

Matrix operator*(const double num, const Matrix& matrix) {
  return matrix * num;
}

std::ostream &operator<<(std::ostream &os, const Matrix &other) {
  for (int i = 0; i < other.rows_; ++i) {
    for (int j = 0; j < other.cols_; ++j) {
      os << other.matrix_[i][j] << " ";
    }
    os << std::endl;
  }

  return os;
}

std::istream &operator>>(std::istream &is, Matrix &other) {
  for (int i = 0; i < other.rows_; ++i) {
    for (int j = 0; j < other.cols_; ++j) {
      is >> other.matrix_[i][j];
    }
  }

  return is;
}

void Matrix::ResizeMatrix(int rows, int cols) {
  if (rows < 1 || cols < 1) {
    throw std::invalid_argument("Not correct dates");
  }

  Matrix new_obj(rows, cols);
  int min_rows = rows < rows_ ? rows : rows_;
  int min_cols = cols < cols_ ? cols : cols_;
  for (int i = 0; i < min_rows; ++i) {
    std::memcpy(new_obj.matrix_[i], matrix_[i], min_cols * sizeof(double));
  }
  this->Clear();
  *this = new_obj;
}

}  // namespace math
