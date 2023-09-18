#include "../src/matrix.h"

#include <gtest/gtest.h>

class MatrixTests : public ::testing::Test {
protected:
  math::Matrix empty;     // 0x0
  math::Matrix obj_one;   // 1x1
  math::Matrix obj_two;   // 2x2
  math::Matrix obj_three; // 3x3
  math::Matrix obj_four;  // 4x4
  math::Matrix obj_five;  // 5x6

  MatrixTests()
      : obj_one(1, 1), obj_two(2, 2), obj_three(3, 3), obj_four(4, 4),
        obj_five(5, 5) {}

  void SetUp() override {
    // 1x1
    obj_one(0, 0) = 9;
    // 2x2
    obj_two(0, 0) = 4;
    obj_two(0, 1) = -3;
    obj_two(1, 0) = 2;
    obj_two(1, 1) = 1;
  }
};

void ComparisonOfRowsAndCols(const math::Matrix obj, int rows, int cols) {
  EXPECT_EQ(obj.GetRows(), rows);
  EXPECT_EQ(obj.GetColumns(), cols);
}

void ComparisonMethodsWithThrow(math::Matrix obj) {
  EXPECT_ANY_THROW(obj.MulNumber(3));
  EXPECT_ANY_THROW(obj.SumMatrix(obj));
  EXPECT_ANY_THROW(obj.SubMatrix(obj));
  EXPECT_ANY_THROW(obj.Determinant());
  EXPECT_ANY_THROW(obj.Transponse());
  EXPECT_ANY_THROW(obj.InverseMatrix());
  EXPECT_ANY_THROW(obj.CalcComplements());
}

TEST(BasicConstructor, test_one) {
  math::Matrix obj;
  const math::Matrix const_obj;
  ComparisonOfRowsAndCols(obj, 0, 0);
  ComparisonOfRowsAndCols(const_obj, 0, 0);
  EXPECT_ANY_THROW(obj(0, 0));
  EXPECT_ANY_THROW(const_obj(0, 0));
}

TEST(ParameterizedConstructor, test_one) {
  EXPECT_ANY_THROW(math::Matrix obj_two(-1, -1));
  EXPECT_ANY_THROW(math::Matrix obj_three(-1, 0));
  EXPECT_ANY_THROW(math::Matrix obj_four(0, -1));
  EXPECT_ANY_THROW(math::Matrix obj_five(0, -1));
  EXPECT_ANY_THROW(math::Matrix obj_six(0, -1));
  math::Matrix obj(0, 0);
  math::Matrix obj_one(1, 0);
  math::Matrix obj_two(0, 1);
  math::Matrix obj_seven(1, 1);
  ComparisonOfRowsAndCols(obj, 0, 0);
  ComparisonOfRowsAndCols(obj_one, 0, 0);
  ComparisonOfRowsAndCols(obj_two, 0, 0);
  ComparisonOfRowsAndCols(obj_seven, 1, 1);
  EXPECT_EQ(obj_seven(0, 0), 0);
}

// Copy Constructor_____________________________________________________
TEST(CopyConstructur, test_one) {
  math::Matrix a(1, 1);
  a(0, 0) = -123.0092;
  EXPECT_DOUBLE_EQ(a(0, 0), -123.0092);
  math::Matrix b(a);
  EXPECT_EQ(b.GetRows(), a.GetRows());
  EXPECT_EQ(b.GetColumns(), a.GetColumns());
  EXPECT_DOUBLE_EQ(b(0, 0), a(0, 0));
}

TEST(CopyConstructur, test_two) {
  math::Matrix *a = nullptr;
  a = new math::Matrix(1, 1);
  if (a != nullptr) {
    (*a)(0, 0) = -123.0092;
    EXPECT_EQ((*a)(0, 0), -123.0092);
    math::Matrix b(*a);
    EXPECT_EQ(b.GetRows(), a->GetRows());
    EXPECT_EQ(b.GetColumns(), a->GetColumns());
    EXPECT_EQ(b(0, 0), (*a)(0, 0));
    delete a;
  }
}

TEST(CopyConstructur, test_three) {
  math::Matrix a(4, 6);
  // 1 x 6
  a(0, 0) = -93.000;
  a(0, 1) = -93.001;
  a(0, 2) = -93.002;
  a(0, 3) = -93.003;
  a(0, 4) = -93.004;
  a(0, 5) = -93.005;
  // 2 x 6
  a(1, 0) = -93.010;
  a(1, 1) = -93.011;
  a(1, 2) = -93.012;
  a(1, 3) = -93.013;
  a(1, 4) = -93.014;
  a(1, 5) = -93.015;
  // 3 x 6
  a(2, 0) = -93.020;
  a(2, 1) = -93.021;
  a(2, 2) = -93.022;
  a(2, 3) = -93.023;
  a(2, 4) = -93.024;
  a(2, 5) = -93.025;
  // 4 x 6
  a(3, 0) = -93.030;
  a(3, 1) = -93.031;
  a(3, 2) = -93.032;
  a(3, 3) = -93.033;
  a(3, 4) = -93.034;
  a(3, 5) = -93.035;
  math::Matrix b(a);
  EXPECT_EQ(b.GetRows(), a.GetRows());
  EXPECT_EQ(b.GetColumns(), a.GetColumns());

  for (int i = 0; i < b.GetRows(); i++) {
    for (int j = 0; j < b.GetColumns(); j++) {
      EXPECT_EQ(b(i, j), a(i, j));
    }
  }
}

// Transfer Constructor_________________________________________________
TEST(CopyConstructur, test_four) {
  math::Matrix a;
  a.SetRows(3);
  a.SetColumns(3);
  math::Matrix b(std::move(a));
  EXPECT_EQ(b.GetRows(), 3);
  EXPECT_EQ(b.GetColumns(), 3);
  EXPECT_EQ(a.GetRows(), 0);
  EXPECT_EQ(a.GetColumns(), 0);
  for (int i = 0; i < b.GetRows(); i++) {
    for (int j = 0; j < b.GetColumns(); j++) {
      EXPECT_EQ(b(i, j), 0);
    }
  }
}

TEST(CopyConstructur, test_five) {
  math::Matrix a(12, 3);
  a(0, 0) = 154;
  a(0, 1) = -1234;
  a(1, 0) = 0.0003;
  math::Matrix b(std::move(a));
  EXPECT_EQ(b.GetRows(), 12);
  EXPECT_EQ(b.GetColumns(), 3);
  EXPECT_EQ(a.GetRows(), 0);
  EXPECT_EQ(a.GetColumns(), 0);
  EXPECT_DOUBLE_EQ(b(0, 0), 154);
  EXPECT_DOUBLE_EQ(b(0, 1), -1234);
  EXPECT_DOUBLE_EQ(b(1, 0), 0.0003);
  for (int i = 1; i < b.GetRows(); i++) {
    for (int j = 1; j < b.GetColumns(); j++) {
      EXPECT_EQ(b(i, j), 0);
    }
  }
}

TEST(CopyConstructur, test_six) {
  math::Matrix *a = nullptr;
  a = new math::Matrix(12, 3);
  if (a != nullptr) {
    (*a)(0, 0) = 154;
    (*a)(0, 1) = -1234;
    (*a)(1, 0) = 0.0003;
    math::Matrix *b = nullptr;
    b = new math::Matrix(std::move(*a));
    if (b != nullptr) {
      EXPECT_EQ(b->GetRows(), 12);
      EXPECT_EQ(b->GetColumns(), 3);
      EXPECT_EQ(a->GetRows(), 0);
      EXPECT_EQ(a->GetColumns(), 0);
      EXPECT_DOUBLE_EQ((*b)(0, 0), 154);
      EXPECT_DOUBLE_EQ((*b)(0, 1), -1234);
      EXPECT_DOUBLE_EQ((*b)(1, 0), 0.0003);
      for (int i = 1; i < b->GetRows(); i++) {
        for (int j = 1; j < b->GetColumns(); j++) {
          EXPECT_EQ((*b)(i, j), 0);
        }
      }
      delete b;
    }
    delete a;
  }
}

TEST_F(MatrixTests, test_one) {
  EXPECT_EQ(obj_one.GetRows(), 1);
  EXPECT_EQ(obj_one.GetColumns(), 1);
  EXPECT_EQ(obj_one(0, 0), 1);
}

TEST(SetRowsCols, test_one) {
  math::Matrix a;
  a.SetRows(3);
  a.SetColumns(3);
  EXPECT_EQ(a.GetRows(), 0);
  EXPECT_EQ(a.GetColumns(), 0);
}

TEST(SetRowsCols, test_two) {
  math::Matrix a(3, 3);
  EXPECT_EQ(a.GetRows(), 3);
  EXPECT_EQ(a.GetColumns(), 3);
  a.SetRows(1);
  EXPECT_EQ(a.GetRows(), 1);
  EXPECT_EQ(a.GetColumns(), 3);
  a.SetColumns(1);
  EXPECT_EQ(a.GetRows(), 1);
  EXPECT_EQ(a.GetColumns(), 1);
  a.SetRows(2);
  EXPECT_EQ(a.GetRows(), 2);
  EXPECT_EQ(a.GetColumns(), 1);
}

TEST(SetRowsCols, test_three) {
  math::Matrix a(6, 6);
  math::Matrix b(6, 6);
  EXPECT_ANY_THROW(a.SetRows(0));
  EXPECT_ANY_THROW(a.SetColumns(0));
  EXPECT_ANY_THROW(b.SetRows(-1));
  EXPECT_ANY_THROW(b.SetColumns(-1));
}

TEST(MulMatrix, test_one) {
  math::Matrix a(1, 1);
  math::Matrix b(1, 1);
  a(0, 0) = 5;
  b(0, 0) = 5;
  b.MulMatrix(a);
  EXPECT_EQ(b.GetRows(), 1);
  EXPECT_EQ(b.GetColumns(), 1);
  EXPECT_DOUBLE_EQ(b(0, 0), 25);
}

TEST(MulMatrix, test_two) {
  math::Matrix a(1, 2);
  math::Matrix b(2, 1);
  a(0, 0) = -5;
  a(0, 1) = -5;
  b(0, 0) = +5;
  b(1, 0) = +2.5;
  b.MulMatrix(a);
  EXPECT_EQ(b.GetRows(), 2);
  EXPECT_EQ(b.GetColumns(), 2);
  EXPECT_DOUBLE_EQ(b(0, 0), -25);
  EXPECT_DOUBLE_EQ(b(0, 1), -25);
  EXPECT_DOUBLE_EQ(b(1, 0), -12.5);
  EXPECT_DOUBLE_EQ(b(1, 1), -12.5);
}

TEST(MulMatrix, test_three) {
  math::Matrix a(1, 2);
  math::Matrix b(2, 1);
  a(0, 0) = -5;
  a(0, 1) = -5;
  b(0, 0) = +5;
  b(1, 0) = +2.5;
  a.MulMatrix(b);
  EXPECT_EQ(a.GetRows(), 1);
  EXPECT_EQ(a.GetColumns(), 1);
  EXPECT_DOUBLE_EQ(a(0, 0), -37.5);
}

TEST(MulMatrix, test_four) {
  math::Matrix a(1, 2);
  math::Matrix b(2, 2);
  a(0, 0) = -5;
  a(0, 1) = -5;
  b(0, 0) = +5;
  b(1, 0) = +2.5;
  a.MulMatrix(b);
  EXPECT_EQ(a.GetRows(), 1);
  EXPECT_EQ(a.GetColumns(), 2);
  EXPECT_DOUBLE_EQ(a(0, 0), -37.5);
  EXPECT_DOUBLE_EQ(a(0, 1), 0);
}

TEST(MulMatrix, test_five) {
  math::Matrix a(2, 1);
  math::Matrix b(2, 2);
  a(0, 0) = -5;
  EXPECT_THROW(a(0, 1) = -5, std::invalid_argument); // becose a(1,0) = 0;
  b(0, 0) = +5;
  b(1, 0) = +2.5;
  EXPECT_THROW(a.MulMatrix(b), std::invalid_argument);
  EXPECT_EQ(a.GetRows(), 2);
  EXPECT_EQ(a.GetColumns(), 1);
  EXPECT_DOUBLE_EQ(a(0, 0), -5);
  EXPECT_THROW(a(0, 0) = a(0, 1),
               std::invalid_argument); // becose a(1,0) = 0;
}

TEST(MulMatrix, test_62) {
  math::Matrix a(2, 2);
  math::Matrix b(2, 2);
  for (int i = 0; i < a.GetRows(); i++)
    for (int j = 0; j < a.GetColumns(); j++)
      a(i, j) = i + j;

  a.MulMatrix(b);
  EXPECT_EQ(a.GetRows(), 2);
  EXPECT_EQ(a.GetColumns(), 2);
  for (int i = 0; i < a.GetRows(); i++)
    for (int j = 0; j < a.GetColumns(); j++)
      EXPECT_DOUBLE_EQ(a(i, j), 0);
}

TEST(MulMatrix, test_63) {
  math::Matrix a(2, 2);
  math::Matrix b(2, 2);
  for (int i = 0; i < a.GetRows(); i++)
    for (int j = 0; j < a.GetColumns(); j++)
      a(i, j) = i + j;

  for (int i = 0; i < b.GetRows(); i++)
    for (int j = 0; j < b.GetColumns(); j++)
      b(i, j) = (i + j) * (-1) - 10;

  a.MulMatrix(b);
  EXPECT_EQ(a.GetRows(), 2);
  EXPECT_EQ(a.GetColumns(), 2);
  EXPECT_DOUBLE_EQ(a(0, 0), -11);
  EXPECT_DOUBLE_EQ(a(0, 1), -12);
  EXPECT_DOUBLE_EQ(a(1, 0), -32);
  EXPECT_DOUBLE_EQ(a(1, 1), -35);
}

TEST(MulMatrix, test_64) {
  math::Matrix a(3, 1);
  math::Matrix b(1, 3);
  for (int i = 0; i < a.GetRows(); i++)
    for (int j = 0; j < a.GetColumns(); j++)
      a(i, j) = i + j;

  for (int i = 0; i < b.GetRows(); i++)
    for (int j = 0; j < b.GetColumns(); j++)
      b(i, j) = i + j;

  a.MulMatrix(b);
  EXPECT_EQ(a.GetRows(), 3);
  EXPECT_EQ(a.GetColumns(), 3);
  EXPECT_DOUBLE_EQ(a(0, 0), 0);
  EXPECT_DOUBLE_EQ(a(0, 1), 0);
  EXPECT_DOUBLE_EQ(a(0, 2), 0);
  EXPECT_DOUBLE_EQ(a(1, 0), 0);
  EXPECT_DOUBLE_EQ(a(1, 1), 1);
  EXPECT_DOUBLE_EQ(a(1, 2), 2);
  EXPECT_DOUBLE_EQ(a(2, 0), 0);
  EXPECT_DOUBLE_EQ(a(2, 1), 2);
  EXPECT_DOUBLE_EQ(a(2, 2), 4);
}

TEST(MulMatrix, test_65) {
  math::Matrix a(1, 3);
  math::Matrix b(3, 2);
  for (int i = 0; i < a.GetRows(); i++)
    for (int j = 0; j < a.GetColumns(); j++)
      a(i, j) = i + j;

  for (int i = 0; i < b.GetRows(); i++)
    for (int j = 0; j < b.GetColumns(); j++)
      b(i, j) = i + j;

  a.MulMatrix(b);
  EXPECT_EQ(a.GetRows(), 1);
  EXPECT_EQ(a.GetColumns(), 2);
  EXPECT_DOUBLE_EQ(a(0, 0), 5);
  EXPECT_DOUBLE_EQ(a(0, 1), 8);
}

TEST(MulMatrix, test_66) {
  math::Matrix a(3, 3);
  math::Matrix b(3, 3);
  for (int i = 0; i < a.GetRows(); i++)
    for (int j = 0; j < a.GetColumns(); j++)
      a(i, j) = i + j;

  for (int i = 0; i < b.GetRows(); i++)
    for (int j = 0; j < b.GetColumns(); j++)
      b(i, j) = i + j;

  a.MulMatrix(b);
  EXPECT_EQ(a.GetRows(), 3);
  EXPECT_EQ(a.GetColumns(), 3);
  EXPECT_DOUBLE_EQ(a(0, 0), 5);
  EXPECT_DOUBLE_EQ(a(0, 1), 8);
  EXPECT_DOUBLE_EQ(a(0, 2), 11);
  EXPECT_DOUBLE_EQ(a(1, 0), 8);
  EXPECT_DOUBLE_EQ(a(1, 1), 14);
  EXPECT_DOUBLE_EQ(a(1, 2), 20);
  EXPECT_DOUBLE_EQ(a(2, 0), 11);
  EXPECT_DOUBLE_EQ(a(2, 1), 20);
  EXPECT_DOUBLE_EQ(a(2, 2), 29);
}

TEST(MulMatrix, test_67) {
  math::Matrix a(4, 1);
  math::Matrix b(1, 4);
  for (int i = 0; i < a.GetRows(); i++)
    for (int j = 0; j < a.GetColumns(); j++)
      a(i, j) = i + j;

  for (int i = 0; i < b.GetRows(); i++)
    for (int j = 0; j < b.GetColumns(); j++)
      b(i, j) = i + j;

  a.MulMatrix(b);
  EXPECT_EQ(a.GetRows(), 4);
  EXPECT_EQ(a.GetColumns(), 4);
  EXPECT_DOUBLE_EQ(a(0, 0), 0);
  EXPECT_DOUBLE_EQ(a(0, 1), 0);
  EXPECT_DOUBLE_EQ(a(0, 2), 0);
  EXPECT_DOUBLE_EQ(a(0, 3), 0);
  EXPECT_DOUBLE_EQ(a(1, 0), 0);
  EXPECT_DOUBLE_EQ(a(1, 1), 1);
  EXPECT_DOUBLE_EQ(a(1, 2), 2);
  EXPECT_DOUBLE_EQ(a(1, 3), 3);
  EXPECT_DOUBLE_EQ(a(2, 0), 0);
  EXPECT_DOUBLE_EQ(a(2, 1), 2);
  EXPECT_DOUBLE_EQ(a(2, 2), 4);
  EXPECT_DOUBLE_EQ(a(2, 3), 6);
  EXPECT_DOUBLE_EQ(a(3, 0), 0);
  EXPECT_DOUBLE_EQ(a(3, 1), 3);
  EXPECT_DOUBLE_EQ(a(3, 2), 6);
  EXPECT_DOUBLE_EQ(a(3, 3), 9);
}

TEST(MulMatrix, test_68) {
  math::Matrix a(1, 4);
  math::Matrix b(4, 1);
  for (int i = 0; i < a.GetRows(); i++)
    for (int j = 0; j < a.GetColumns(); j++)
      a(i, j) = i + j;

  for (int i = 0; i < b.GetRows(); i++)
    for (int j = 0; j < b.GetColumns(); j++)
      b(i, j) = i + j;

  a.MulMatrix(b);
  EXPECT_EQ(a.GetRows(), 1);
  EXPECT_EQ(a.GetColumns(), 1);
  EXPECT_DOUBLE_EQ(a(0, 0), 14);
}

TEST(MulMatrix, test_69) {
  math::Matrix *a = nullptr;
  math::Matrix *b = nullptr;
  a = new math::Matrix(5, 5);
  b = new math::Matrix(5, 1);
  if (a != nullptr && b != nullptr) {
    for (int i = 0; i < a->GetRows(); i++)
      for (int j = 0; j < a->GetColumns(); j++)
        (*a)(i, j) = i + j;

    for (int i = 0; i < b->GetRows(); i++)
      for (int j = 0; j < b->GetColumns(); j++)
        (*b)(i, j) = i + j;

    a->MulMatrix(*b);
    EXPECT_EQ(a->GetRows(), 5);
    EXPECT_EQ(a->GetColumns(), 1);
    EXPECT_DOUBLE_EQ((*a)(0, 0), 30);
    EXPECT_DOUBLE_EQ((*a)(1, 0), 40);
    EXPECT_DOUBLE_EQ((*a)(2, 0), 50);
    EXPECT_DOUBLE_EQ((*a)(3, 0), 60);
    EXPECT_DOUBLE_EQ((*a)(4, 0), 70);
    delete a;
    delete b;
  }
}

// Multiplication on Number_____________________________________________
TEST(MulNumber, test_70) {
  math::Matrix a;
  a.SetRows(3);
  a.SetColumns(3);
  for (int i = 0; i < a.GetRows(); i++)
    for (int j = 0; j < a.GetColumns(); j++)
      a(i, j) = i + j;

  a.MulNumber(0.1);
  for (int i = 0; i < a.GetRows(); i++)
    for (int j = 0; j < a.GetColumns(); j++)
      EXPECT_DOUBLE_EQ(a(i, j), (i + j) * 0.1);
}

TEST(MulNumber, test_71) {
  math::Matrix a(4, 2);
  for (int i = 0; i < a.GetRows(); i++)
    for (int j = 0; j < a.GetColumns(); j++)
      a(i, j) = i + j;

  a.MulNumber(0.126);
  for (int i = 0; i < a.GetRows(); i++)
    for (int j = 0; j < a.GetColumns(); j++)
      EXPECT_DOUBLE_EQ(a(i, j), (i + j) * 0.126);
}

TEST(MulNumber, test_72) {
  math::Matrix a(14, 9);
  for (int i = 0; i < a.GetRows(); i++)
    for (int j = 0; j < a.GetColumns(); j++)
      a(i, j) = i + j;

  a.MulNumber(1.5);
  for (int i = 0; i < a.GetRows(); i++)
    for (int j = 0; j < a.GetColumns(); j++)
      EXPECT_DOUBLE_EQ(a(i, j), (i + j) * 1.5);
}

/* #####################################################################
   ########################  A D D I T I O N  ##########################
   ##################################################################### */

TEST(SumMatrix, test_74) {
  math::Matrix a;
  a.SetRows(3);
  a.SetColumns(3);
  math::Matrix b(1, 1);
  b(0, 0) = 100;
  EXPECT_THROW(a.SumMatrix(b), std::invalid_argument);
  EXPECT_DOUBLE_EQ(a(0, 0), 0);
}

TEST(SumMatrix, test_75) {
  math::Matrix a(1, 1);
  math::Matrix b(1, 1);
  b(0, 0) = 100;
  a.SumMatrix(b);
  EXPECT_DOUBLE_EQ(a(0, 0), 100);
}

TEST(SumMatrix, test_77) {
  math::Matrix a(4, 4);
  math::Matrix b(2, 2);
  for (int i = 0; i < a.GetRows(); i++)
    for (int j = 0; j < a.GetColumns(); j++)
      a(i, j) = i + j;

  for (int i = 0; i < b.GetRows(); i++)
    for (int j = 0; j < b.GetColumns(); j++)
      b(i, j) = i + j;
  EXPECT_THROW(a.SumMatrix(b), std::invalid_argument);

  for (int i = 0; i < a.GetRows(); i++)
    for (int j = 0; j < a.GetColumns(); j++)
      EXPECT_DOUBLE_EQ(a(i, j), i + j);
}

TEST(SumMatrix, test_78) {
  math::Matrix a(4, 4);
  math::Matrix b(4, 4);
  for (int i = 0; i < a.GetRows(); i++)
    for (int j = 0; j < a.GetColumns(); j++)
      a(i, j) = i + j;

  for (int i = 0; i < b.GetRows(); i++)
    for (int j = 0; j < b.GetColumns(); j++)
      b(i, j) = i + j;
  a.SumMatrix(b);
  for (int i = 0; i < a.GetRows(); i++)
    for (int j = 0; j < a.GetColumns(); j++)
      EXPECT_DOUBLE_EQ(a(i, j), (i + j) * 2);
}

TEST(SumMatrix, test_79) {
  math::Matrix a(15, 1);
  math::Matrix b(15, 1);
  for (int i = 0; i < a.GetRows(); i++)
    for (int j = 0; j < a.GetColumns(); j++)
      a(i, j) = i + j;

  for (int i = 0; i < b.GetRows(); i++)
    for (int j = 0; j < b.GetColumns(); j++)
      b(i, j) = i + j;
  a.SumMatrix(b);
  for (int i = 0; i < a.GetRows(); i++)
    for (int j = 0; j < a.GetColumns(); j++)
      EXPECT_DOUBLE_EQ(a(i, j), (i + j) * 2);
}

TEST(SumMatrix, test_80) {
  math::Matrix a(1, 15);
  math::Matrix b(1, 15);
  for (int i = 0; i < a.GetRows(); i++)
    for (int j = 0; j < a.GetColumns(); j++)
      a(i, j) = i + j;

  for (int i = 0; i < b.GetRows(); i++)
    for (int j = 0; j < b.GetColumns(); j++)
      b(i, j) = i + j;
  a.SumMatrix(b);
  for (int i = 0; i < a.GetRows(); i++)
    for (int j = 0; j < a.GetColumns(); j++)
      EXPECT_DOUBLE_EQ(a(i, j), (i + j) * 2);
}

/* #####################################################################
   #####################  S U B T R A C T I O N  #######################
   ##################################################################### */

TEST(SubMatrix, test_81) {
  math::Matrix a;
  a.SetRows(3);
  a.SetColumns(3);
  math::Matrix b(1, 1);
  b(0, 0) = 100;
  EXPECT_THROW(a.SubMatrix(b), std::invalid_argument);
  EXPECT_DOUBLE_EQ(a(0, 0), 0);
}

TEST(SubMatrix, test_82) {
  math::Matrix a(1, 1);
  math::Matrix b(1, 1);
  b(0, 0) = 100;
  a.SubMatrix(b);
  EXPECT_DOUBLE_EQ(a(0, 0), -100);
}

TEST(SubMatrix, test_84) {
  math::Matrix a(4, 4);
  math::Matrix b(2, 2);
  for (int i = 0; i < a.GetRows(); i++)
    for (int j = 0; j < a.GetColumns(); j++)
      a(i, j) = i + j;

  for (int i = 0; i < b.GetRows(); i++)
    for (int j = 0; j < b.GetColumns(); j++)
      b(i, j) = i + j;
  EXPECT_THROW(a.SubMatrix(b), std::invalid_argument);
  for (int i = 0; i < a.GetRows(); i++)
    for (int j = 0; j < a.GetColumns(); j++)
      EXPECT_DOUBLE_EQ(a(i, j), i + j);
}

TEST(SubMatrix, test_85) {
  math::Matrix a(4, 4);
  math::Matrix b(4, 4);
  for (int i = 0; i < a.GetRows(); i++)
    for (int j = 0; j < a.GetColumns(); j++)
      a(i, j) = i + j;

  for (int i = 0; i < b.GetRows(); i++)
    for (int j = 0; j < b.GetColumns(); j++)
      b(i, j) = i + j;
  a.SubMatrix(b);
  for (int i = 0; i < a.GetRows(); i++)
    for (int j = 0; j < a.GetColumns(); j++)
      EXPECT_DOUBLE_EQ(a(i, j), 0);
}

TEST(SubMatrix, test_86) {
  math::Matrix a(15, 1);
  math::Matrix b(15, 1);
  for (int i = 0; i < a.GetRows(); i++)
    for (int j = 0; j < a.GetColumns(); j++)
      a(i, j) = i + j;

  for (int i = 0; i < b.GetRows(); i++)
    for (int j = 0; j < b.GetColumns(); j++)
      b(i, j) = i + j * 0.12;
  a.SubMatrix(b);
  for (int i = 0; i < a.GetRows(); i++)
    for (int j = 0; j < a.GetColumns(); j++)
      EXPECT_DOUBLE_EQ(a(i, j), (i + j) - (i + j * 0.12));
}

TEST(SubMatrix, test_87) {
  math::Matrix a(1, 15);
  math::Matrix b(1, 15);
  for (int i = 0; i < a.GetRows(); i++)
    for (int j = 0; j < a.GetColumns(); j++)
      a(i, j) = i + j * 1.33;

  for (int i = 0; i < b.GetRows(); i++)
    for (int j = 0; j < b.GetColumns(); j++)
      b(i, j) = i * 0.12 + j;
  a.SubMatrix(b);
  for (int i = 0; i < a.GetRows(); i++)
    for (int j = 0; j < a.GetColumns(); j++)
      EXPECT_DOUBLE_EQ(a(i, j), (i + j * 1.33) - (i * 0.12 + j));
}

/* #####################################################################
   #####################  C O M P A R I S I O N  #######################
   ##################################################################### */

TEST(EqMatrix, test_89) {
  math::Matrix a;
  a.SetRows(3);
  a.SetColumns(3);
  math::Matrix b;
  b.SetRows(1);
  b.SetColumns(3);
  for (int i = 0; i < a.GetRows(); i++) {
    for (int j = 0; j < a.GetColumns(); j++) {
      a(i, j) = i + j * 1.33;
    }
  }
  for (int i = 0; i < b.GetRows(); i++) {
    for (int j = 0; j < b.GetColumns(); j++) {
      b(i, j) = i * 0.12 + j;
    }
  }
  EXPECT_FALSE(a.EqMatrix(b));
}

TEST(EqMatrix, test_90) {
  math::Matrix a;
  a.SetRows(3);
  a.SetColumns(3);
  math::Matrix b;
  b.SetRows(3);
  b.SetColumns(3);
  for (int i = 0; i < a.GetRows(); i++)
    for (int j = 0; j < a.GetColumns(); j++)
      a(i, j) = i;
  for (int i = 0; i < b.GetRows(); i++)
    for (int j = 0; j < b.GetColumns(); j++)
      b(i, j) = i;
  EXPECT_TRUE(a.EqMatrix(b));
}

TEST(EqMatrix, test_91) {
  math::Matrix a(6, 1);
  math::Matrix b(6, 1);
  for (int i = 0; i < a.GetRows(); i++)
    for (int j = 0; j < a.GetColumns(); j++)
      a(i, j) = i + j + j * 0.123;
  for (int i = 0; i < b.GetRows(); i++)
    for (int j = 0; j < b.GetColumns(); j++)
      b(i, j) = i + j + j * 0.123;
  EXPECT_TRUE(a.EqMatrix(b));
}

TEST(EqMatrix, test_92) {
  math::Matrix a(6, 8);
  math::Matrix b(6, 8);
  for (int i = 0; i < a.GetRows(); i++)
    for (int j = 0; j < a.GetColumns(); j++)
      a(i, j) = i + j + j * 0.123;
  for (int i = 0; i < b.GetRows(); i++)
    for (int j = 0; j < b.GetColumns(); j++)
      b(i, j) = i + j + j * 0.123;
  EXPECT_TRUE(a.EqMatrix(b));
}

/* #####################################################################
   #####################  D E T E R M I N A N T  #######################
   ##################################################################### */

TEST(Determinant, test_93) {
  math::Matrix a(6, 8);
  for (int i = 0; i < a.GetRows(); i++)
    for (int j = 0; j < a.GetColumns(); j++)
      a(i, j) = i + j + j * 0.123;
  EXPECT_THROW(a.Determinant(), std::invalid_argument);
}

TEST(Determinant, test_94) {
  math::Matrix a(6, 6);
  for (int i = 0; i < a.GetRows(); i++)
    for (int j = 0; j < a.GetColumns(); j++)
      a(i, j) = i + j;
  EXPECT_DOUBLE_EQ(a.Determinant(), 0);
}

TEST(Determinant, test_95) {
  math::Matrix a(5, 5);
  a(0, 0) = 13;
  a(0, 1) = 1;
  a(0, 2) = 1;
  a(0, 3) = 1;
  a(0, 4) = 0;
  a(1, 0) = 2;
  a(1, 1) = 21;
  a(1, 2) = 3;
  a(1, 3) = 2;
  a(1, 4) = 2;
  a(2, 0) = 3;
  a(2, 1) = 33;
  a(2, 2) = 33;
  a(2, 3) = 2;
  a(2, 4) = 2;
  a(3, 0) = 1;
  a(3, 1) = 1;
  a(3, 2) = 1;
  a(3, 3) = 22;
  a(3, 4) = 2;
  a(4, 0) = 2;
  a(4, 1) = 2;
  a(4, 2) = 2;
  a(4, 3) = 2;
  a(4, 4) = 51;
  EXPECT_DOUBLE_EQ(a.Determinant(), 8508996);
}

TEST(Determinant, test_96) {
  math::Matrix a(5, 5);
  a(0, 0) = 13;
  a(0, 1) = 1;
  a(0, 2) = 1;
  a(0, 3) = 1;
  a(0, 4) = 0;
  a(1, 0) = 2;
  a(1, 1) = 21;
  a(1, 2) = 3;
  a(1, 3) = 2;
  a(1, 4) = 2;
  a(2, 0) = 3;
  a(2, 1) = 33;
  a(2, 2) = 33;
  a(2, 3) = 2;
  a(2, 4) = 2;
  a(3, 0) = 1;
  a(3, 1) = 1;
  a(3, 2) = 1;
  a(3, 3) = 2;
  a(3, 4) = 2;
  a(4, 0) = 2;
  a(4, 1) = 2;
  a(4, 2) = 2;
  a(4, 3) = 2;
  a(4, 4) = 51;
  EXPECT_DOUBLE_EQ(a.Determinant(), 704916);
}

TEST(Determinant, test_97) {
  math::Matrix a(4, 4);
  a(0, 0) = -1;
  a(0, 1) = 1;
  a(0, 2) = -0.21;
  a(0, 3) = 1;
  a(1, 0) = -3;
  a(1, 1) = -2;
  a(1, 2) = -6;
  a(1, 3) = -5;
  a(2, 0) = 1;
  a(2, 1) = 33;
  a(2, 2) = 33;
  a(2, 3) = 1;
  a(3, 0) = -2;
  a(3, 1) = -0.1;
  a(3, 2) = 0.11;
  a(3, 3) = 2.004;
  EXPECT_DOUBLE_EQ(a.Determinant(), 667.10348);
}

TEST(Determinant, test_98) {
  math::Matrix a(3, 3);
  a(0, 0) = -11.0543;
  a(0, 1) = 1.234445;
  a(0, 2) = -0.9999;
  a(1, 0) = -313;
  a(1, 1) = -2.002;
  a(1, 2) = -63;
  a(2, 0) = 1.01;
  a(2, 1) = 7.01;
  a(2, 2) = 25.0003;
  EXPECT_DOUBLE_EQ(a.Determinant(), 7444.35291845008);
}

TEST(Determinant, test_99) {
  math::Matrix a(2, 2);
  a(0, 0) = -11.0543;
  a(0, 1) = 1.234445;
  a(1, 0) = 313;
  a(1, 1) = 2.002;
  EXPECT_DOUBLE_EQ(a.Determinant(), -408.5119936);
}

TEST(Determinant, test_100) {
  math::Matrix a(1, 1);
  a(0, 0) = -5;
  EXPECT_DOUBLE_EQ(a.Determinant(), -5);
}

TEST(Determinant, test_101) {
  math::Matrix a;
  a.SetRows(3);
  a.SetColumns(3);
  a(0, 0) = -5;
  EXPECT_DOUBLE_EQ(a.Determinant(), 0);
}

/* #####################################################################
   #######################  T R A N S P O N S E  #######################
   ##################################################################### */

TEST(Transponse, test_105) {
  math::Matrix a(1, 1);
  a(0, 0) = -5;
  a = a.Transponse();
  EXPECT_EQ(a.GetRows(), 1);
  EXPECT_EQ(a.GetColumns(), 1);
  EXPECT_DOUBLE_EQ(a(0, 0), -5);
}

TEST(Transponse, test_106) {
  math::Matrix a(2, 1);
  a(0, 0) = -5;
  a(1, 0) = -5;
  a = a.Transponse();
  EXPECT_EQ(a.GetRows(), 1);
  EXPECT_EQ(a.GetColumns(), 2);
  EXPECT_DOUBLE_EQ(a(0, 0), -5);
  EXPECT_DOUBLE_EQ(a(0, 1), -5);
}

TEST(Transponse, test_107) {
  math::Matrix a(2, 1);
  a(0, 0) = -5;
  a(1, 0) = -6;
  a = a.Transponse();
  EXPECT_EQ(a.GetRows(), 1);
  EXPECT_EQ(a.GetColumns(), 2);
  EXPECT_DOUBLE_EQ(a(0, 0), -5);
  EXPECT_DOUBLE_EQ(a(0, 1), -6);
}

TEST(Transponse, test_108) {
  math::Matrix a(1, 2);
  a(0, 0) = -5;
  a(0, 1) = -6;
  a = a.Transponse();
  EXPECT_EQ(a.GetRows(), 2);
  EXPECT_EQ(a.GetColumns(), 1);
  EXPECT_DOUBLE_EQ(a(0, 0), -5);
  EXPECT_DOUBLE_EQ(a(1, 0), -6);
}

TEST(Transponse, test_109) {
  math::Matrix a(2, 2);
  a(0, 0) = -5;
  a(0, 1) = -6;
  a(1, 0) = 5;
  a(1, 1) = 6;
  a = a.Transponse();
  EXPECT_EQ(a.GetRows(), 2);
  EXPECT_EQ(a.GetColumns(), 2);
  EXPECT_DOUBLE_EQ(a(0, 0), -5);
  EXPECT_DOUBLE_EQ(a(1, 0), -6);
  EXPECT_DOUBLE_EQ(a(0, 1), 5);
  EXPECT_DOUBLE_EQ(a(1, 1), 6);
}

TEST(Transponse, test_110) {
  math::Matrix a(6, 2);
  for (int i = 0; i < a.GetRows(); i++)
    for (int j = 0; j < a.GetColumns(); j++)
      a(i, j) = i + j + 1;
  a = a.Transponse();
  EXPECT_EQ(a.GetRows(), 2);
  EXPECT_EQ(a.GetColumns(), 6);
  for (int i = 0; i < a.GetRows(); i++)
    for (int j = 0; j < a.GetColumns(); j++)
      EXPECT_DOUBLE_EQ(a(i, j), i + j + 1);
}

TEST(Transponse, test_111) {
  math::Matrix a(2, 6);
  for (int i = 0; i < a.GetRows(); i++)
    for (int j = 0; j < a.GetColumns(); j++)
      a(i, j) = i + j + 1;
  a = a.Transponse();
  EXPECT_EQ(a.GetRows(), 6);
  EXPECT_EQ(a.GetColumns(), 2);
  for (int i = 0; i < a.GetRows(); i++)
    for (int j = 0; j < a.GetColumns(); j++)
      EXPECT_DOUBLE_EQ(a(i, j), i + j + 1);
}

TEST(Transponse, test_112) {
  math::Matrix a(6, 6);
  for (int i = 0; i < a.GetRows(); i++)
    for (int j = 0; j < a.GetColumns(); j++)
      a(i, j) = i + 1 - j / 2;
  a = a.Transponse();
  EXPECT_EQ(a.GetRows(), 6);
  EXPECT_EQ(a.GetColumns(), 6);
  for (int i = 0; i < a.GetRows(); i++)
    for (int j = 0; j < a.GetColumns(); j++)
      EXPECT_DOUBLE_EQ(a(i, j), j + 1 - i / 2);
}

/* #####################################################################
   ##########################  I N V E R S E  ##########################
   ##################################################################### */

TEST(InverseMatrix, test_115) {
  math::Matrix a(1, 1);
  a(0, 0) = -2;
  a = a.InverseMatrix();
  EXPECT_EQ(a.GetRows(), 1);
  EXPECT_EQ(a.GetColumns(), 1);
  EXPECT_DOUBLE_EQ(a(0, 0), -0.5);
}

TEST(InverseMatrix, test_116) {
  math::Matrix a(1, 2);
  a(0, 0) = -2;
  EXPECT_THROW(a.InverseMatrix(), std::invalid_argument);
  EXPECT_EQ(a.GetRows(), 1);
  EXPECT_EQ(a.GetColumns(), 2);
  EXPECT_DOUBLE_EQ(a(0, 0), -2);
  EXPECT_DOUBLE_EQ(a(0, 1), 0);
}

TEST(InverseMatrix, test_117) {
  math::Matrix a(2, 2);
  a(0, 0) = -2;
  EXPECT_THROW(a.InverseMatrix(), std::invalid_argument);
  EXPECT_EQ(a.GetRows(), 2);
  EXPECT_EQ(a.GetColumns(), 2);
  EXPECT_DOUBLE_EQ(a(0, 0), -2);
}

TEST(InverseMatrix, test_118) {
  math::Matrix a(2, 2);
  a(0, 0) = -2;
  a(0, 1) = 2.5;
  a(1, 0) = 13;
  a(1, 1) = 250;
  a = a.InverseMatrix();
  EXPECT_EQ(a.GetRows(), 2);
  EXPECT_EQ(a.GetColumns(), 2);
  EXPECT_NEAR(a(0, 0), -0.469483568075, 1E-12);
  EXPECT_NEAR(a(0, 1), 0.0046948356807, 1E-12);
  EXPECT_NEAR(a(1, 0), 0.0244131455399, 1E-12);
  EXPECT_NEAR(a(1, 1), 0.0037558685446, 1E-12);
}

TEST(InverseMatrix, test_119) {
  math::Matrix a(3, 3);
  a(0, 0) = -2;
  a(0, 1) = 2.5;
  a(1, 0) = 13;
  a(1, 1) = 250;
  EXPECT_THROW(a.InverseMatrix(), std::invalid_argument);
  EXPECT_EQ(a.GetRows(), 3);
  EXPECT_EQ(a.GetColumns(), 3);
  EXPECT_DOUBLE_EQ(a(0, 0), -2);
  EXPECT_DOUBLE_EQ(a(0, 1), 2.5);
  EXPECT_DOUBLE_EQ(a(1, 0), 13);
  EXPECT_DOUBLE_EQ(a(1, 1), 250);
}

TEST(InverseMatrix, test_120) {
  math::Matrix a(5, 5);
  a(0, 0) = -2;
  a(0, 1) = 2.5;
  a(0, 2) = 1;
  a(0, 3) = 1;
  a(0, 4) = 1;
  a(1, 0) = 13;
  a(1, 1) = 250;
  a(1, 2) = 1;
  a(1, 3) = 0;
  a(1, 4) = 1;
  a(2, 0) = 3;
  a(2, 1) = 0.2;
  a(2, 2) = 2.1;
  a(2, 3) = 3.001;
  a(2, 4) = 3;
  a(3, 0) = -11;
  a(3, 1) = 0;
  a(3, 2) = 0;
  a(3, 3) = -12;
  a(3, 4) = 10;
  a(4, 0) = 3.25;
  a(4, 1) = 1.125;
  a(4, 2) = 3;
  a(4, 3) = 3.33;
  a(4, 4) = 3;
  a = a.InverseMatrix();
  EXPECT_EQ(a.GetRows(), 5);
  EXPECT_EQ(a.GetColumns(), 5);
  EXPECT_NEAR(a(0, 0), -0.324204159634, 1E-10);
  EXPECT_NEAR(a(0, 1), 0.0027159680675, 1E-10);
  EXPECT_NEAR(a(0, 2), -0.018655847431, 1E-10);
  EXPECT_NEAR(a(0, 3), 0.0016790262688, 1E-10);
  EXPECT_NEAR(a(0, 4), 0.1202218237242, 1E-10);
  EXPECT_NEAR(a(1, 0), 0.0169149942471, 1E-10);
  EXPECT_NEAR(a(1, 1), 0.0038702955304, 1E-10);
  EXPECT_NEAR(a(1, 2), 0.0035181013748, 1E-10);
  EXPECT_NEAR(a(1, 3), -0.000316629123, 1E-10);
  EXPECT_NEAR(a(1, 4), -0.009391100888, 1E-10);
  EXPECT_NEAR(a(2, 0), -0.045548328926, 1E-10);
  EXPECT_NEAR(a(2, 1), -0.00423423011, 1E-10);
  EXPECT_NEAR(a(2, 2), -1.3255487494883, 1E-10);
  EXPECT_NEAR(a(2, 3), 0.0192993874539, 1E-10);
  EXPECT_NEAR(a(2, 4), 1.2778116443209, 1E-10);
  EXPECT_NEAR(a(3, 0), 0.3233986816534, 1E-10);
  EXPECT_NEAR(a(3, 1), -0.001362335206, 1E-10);
  EXPECT_NEAR(a(3, 2), 0.5908923788014, 1E-10);
  EXPECT_NEAR(a(3, 3), -0.053180314092, 1E-10);
  EXPECT_NEAR(a(3, 4), -0.520970113976, 1E-10);
  EXPECT_NEAR(a(4, 0), 0.031453842386, 1E-10);
  EXPECT_NEAR(a(4, 1), 0.0013527626262, 1E-10);
  EXPECT_NEAR(a(4, 2), 0.6885494223872, 1E-10);
  EXPECT_NEAR(a(4, 3), 0.0380305519851, 1E-10);
  EXPECT_NEAR(a(4, 4), -0.492920130675, 1E-10);
}

TEST(InverseMatrix, test_121) {
  math::Matrix a(3, 3);
  a(0, 0) = -2;
  a(0, 1) = 2.5;
  a(0, 2) = 3;
  a(1, 0) = 13;
  a(1, 1) = 250;
  a(1, 2) = 487;
  a(2, 0) = -0.001;
  a(2, 1) = 0.987;
  a(2, 2) = 13.456;
  a = a.InverseMatrix();
  EXPECT_EQ(a.GetRows(), 3);
  EXPECT_EQ(a.GetColumns(), 3);
  EXPECT_NEAR(a(0, 0), -0.467621041439, 1E-12);
  EXPECT_NEAR(a(0, 1), 0.0049755459676, 1E-12);
  EXPECT_NEAR(a(0, 2), -0.075819542353, 1E-12);
  EXPECT_NEAR(a(1, 0), 0.0284489519184, 1E-12);
  EXPECT_NEAR(a(1, 1), 0.0043641242036, 1E-12);
  EXPECT_NEAR(a(1, 2), -0.164289190168, 1E-12);
  EXPECT_NEAR(a(2, 0), -0.002121487558, 1E-12);
  EXPECT_NEAR(a(2, 1), -0.000319739524, 1E-12);
  EXPECT_NEAR(a(2, 2), 0.086361296905, 1E-12);
}

/* #####################################################################
   ################  C A L C . C O M P L E M E N T S  ##################
   ##################################################################### */

TEST(CalcComplements, test_124) {
  math::Matrix a(1, 1);
  a(0, 0) = -8;
  a = a.CalcComplements();
  EXPECT_EQ(a.GetRows(), 1);
  EXPECT_EQ(a.GetColumns(), 1);
  EXPECT_DOUBLE_EQ(a(0, 0), -0.125);
}

TEST(CalcComplements, test_125) {
  math::Matrix a(2, 1);
  a(0, 0) = -8;
  EXPECT_THROW(a.CalcComplements(), std::invalid_argument);
  EXPECT_EQ(a.GetRows(), 2);
  EXPECT_EQ(a.GetColumns(), 1);
  EXPECT_DOUBLE_EQ(a(0, 0), -8);
  EXPECT_DOUBLE_EQ(a(1, 0), 0);
}

TEST(CalcComplements, test_126) {
  math::Matrix a(2, 2);
  a(0, 0) = -8;
  a(0, 1) = -18.91;
  a(1, 0) = 80.2;
  a(1, 1) = -1;
  a = a.CalcComplements();
  EXPECT_EQ(a.GetRows(), 2);
  EXPECT_EQ(a.GetColumns(), 2);
  EXPECT_NEAR(a(0, 0), -1, 1E-10);
  EXPECT_NEAR(a(0, 1), -80.2, 1E-10);
  EXPECT_NEAR(a(1, 0), 18.91, 1E-10);
  EXPECT_NEAR(a(1, 1), -8, 1E-10);
}

TEST(CalcComplements, test_127) {
  math::Matrix a;
  a.SetRows(3);
  a.SetColumns(3);
  for (int i = 0; i < a.GetRows(); i++) {
    for (int j = 0; j < a.GetColumns(); j++) {
      a(i, j) = i + j + 1;
    }
  }
  a = a.CalcComplements();
  EXPECT_EQ(a.GetRows(), 3);
  EXPECT_EQ(a.GetColumns(), 3);
  EXPECT_NEAR(a(0, 0), -1, 1E-10);
  EXPECT_NEAR(a(0, 1), 2, 1E-10);
  EXPECT_NEAR(a(0, 2), -1, 1E-10);
  EXPECT_NEAR(a(1, 0), 2, 1E-10);
  EXPECT_NEAR(a(1, 1), -4, 1E-10);
  EXPECT_NEAR(a(1, 2), 2, 1E-10);
  EXPECT_NEAR(a(2, 0), -1, 1E-10);
  EXPECT_NEAR(a(2, 1), 2, 1E-10);
  EXPECT_NEAR(a(2, 2), -1, 1E-10);
}

TEST(CalcComplements, test_128) {
  math::Matrix a(5, 5);
  for (int i = 0; i < a.GetRows(); i++) {
    for (int j = 0; j < a.GetColumns(); j++) {
      a(i, j) = (double)(i + j / 100 + 1);
    }
  }
  a = a.CalcComplements();
  EXPECT_EQ(a.GetRows(), 5);
  EXPECT_EQ(a.GetColumns(), 5);
  for (int i = 0; i < a.GetRows(); i++) {
    for (int j = 0; j < a.GetColumns(); j++) {
      EXPECT_DOUBLE_EQ(a(i, j), 0);
    }
  }
}

TEST(CalcComplements, test_129) {
  math::Matrix a(4, 4);
  a(0, 0) = 1;
  a(0, 1) = 2.0009;
  a(0, 2) = 3.125;
  a(0, 3) = 4.1111;
  a(1, 0) = 2.0002;
  a(1, 1) = 3.1101;
  a(1, 2) = 4.9899;
  a(1, 3) = 1.333333;
  a(2, 0) = 13.123;
  a(2, 1) = 11.5;
  a(2, 2) = 11.23;
  a(2, 3) = 13.01;
  a(3, 0) = 11.05;
  a(3, 1) = 11.06;
  a(3, 2) = 11.07;
  a(3, 3) = 11.0008;
  a = a.CalcComplements();
  EXPECT_EQ(a.GetRows(), 4);
  EXPECT_EQ(a.GetColumns(), 4);
  EXPECT_NEAR(a(0, 0), 27.166195228, 1E-10);
  EXPECT_NEAR(a(0, 1), 15.73629045273, 1E-10);
  EXPECT_NEAR(a(0, 2), -12.5544942923, 1E-10);
  EXPECT_NEAR(a(0, 3), -30.475199791, 1E-10);
  EXPECT_NEAR(a(1, 0), -26.0843527756, 1E-10);
  EXPECT_NEAR(a(1, 1), 64.707464221, 1E-10);
  EXPECT_NEAR(a(1, 2), -55.68064421944, 1E-10);
  EXPECT_NEAR(a(1, 3), 17.176230401, 1E-10);
  EXPECT_NEAR(a(2, 0), -65.876557117151, 1E-10);
  EXPECT_NEAR(a(2, 1), 118.23792444285, 1E-10);
  EXPECT_NEAR(a(2, 2), -45.418483405759, 1E-10);
  EXPECT_NEAR(a(2, 3), -6.9988434379, 1E-10);
  EXPECT_NEAR(a(3, 0), 70.917587014731, 1E-10);
  EXPECT_NEAR(a(3, 1), -153.556601162995, 1E-10);
  EXPECT_NEAR(a(3, 2), 65.1541788772669, 1E-10);
  EXPECT_NEAR(a(3, 3), 7.96064490303, 1E-10);
}

/* #####################################################################
   #######################  O P E R A T O R S  #########################
   ##################################################################### */

// Operator()___________________________________________________________
TEST(Parenthesis_operator, test_132) {
  math::Matrix a(1, 1);
  a(0, 0) = -1;
  EXPECT_THROW(a(0, 0) = a(1, 1), std::invalid_argument);
}

TEST(Parenthesis_operator, test_133) {
  math::Matrix a(1, 1);
  a(0, 0) = -1;
  EXPECT_EQ(a.GetRows(), 1);
  EXPECT_EQ(a.GetColumns(), 1);
  EXPECT_DOUBLE_EQ(a(0, 0), -1);
}

TEST(Parenthesis_operator, test_134) {
  math::Matrix a(6, 6);
  a(0, 3) = -1;
  EXPECT_EQ(a.GetRows(), 6);
  EXPECT_EQ(a.GetColumns(), 6);
  for (int i = 0; i < a.GetRows(); i++) {
    for (int j = 0; j < a.GetColumns(); j++) {
      if (i != 0 && j != 3) {
        EXPECT_DOUBLE_EQ(a(0, 0), 0);
      }
    }
  }
  EXPECT_DOUBLE_EQ(a(0, 3), -1);
}

TEST(Parenthesis_operator, test_135) {
  const math::Matrix a(1, 1);
  EXPECT_EQ(a.GetRows(), 1);
  EXPECT_EQ(a.GetColumns(), 1);
  EXPECT_DOUBLE_EQ(a(0, 0), 0);
}

// Operator!=___________________________________________________________
TEST(Operator_is_not_equal, test_136) {
  math::Matrix a(6, 6);
  math::Matrix b(6, 6);
  a(0, 0) = 51;
  b(5, 5) = 51;
  EXPECT_TRUE(a != b);
}

TEST(Operator_is_not_equal, test_137) {
  math::Matrix a(6, 6);
  math::Matrix b(6, 6);
  a(0, 0) = 51;
  b(0, 0) = 51;
  EXPECT_FALSE(a != b);
}

// Operator==___________________________________________________________
TEST(The_equals_operator, test_139) {
  math::Matrix a(6, 6);
  math::Matrix b(6, 6);
  a(0, 0) = 51;
  b(5, 5) = 51;
  EXPECT_FALSE(a == b);
}

TEST(The_equals_operator, test_140) {
  math::Matrix a(6, 6);
  math::Matrix b(6, 6);
  a(0, 0) = 51;
  b(0, 0) = 51;
  EXPECT_TRUE(a == b);
}

// Operator*____________________________________________________________
TEST(The_multiply_operator_matrix, test_141) {
  math::Matrix a;
  a.SetRows(3);
  a.SetColumns(3);
  math::Matrix b;
  b.SetRows(3);
  b.SetColumns(3);
  math::Matrix c;
  for (int i = 0; i < a.GetRows(); i++) {
    for (int j = 0; j < a.GetColumns(); j++) {
      a(i, j) = i + j + 0.5;
      b(i, j) = a(i, j);
    }
  }
  c = a * b;
  EXPECT_EQ(a.GetRows(), 3);
  EXPECT_EQ(a.GetColumns(), 3);
  EXPECT_EQ(b.GetRows(), 3);
  EXPECT_EQ(b.GetColumns(), 3);
  for (int i = 0; i < a.GetRows(); i++) {
    for (int j = 0; j < a.GetColumns(); j++) {
      EXPECT_DOUBLE_EQ(a(i, j), b(i, j));
      EXPECT_DOUBLE_EQ(a(i, j), i + j + 0.5);
    }
  }
  EXPECT_EQ(c.GetRows(), 3);
  EXPECT_EQ(c.GetColumns(), 3);
  EXPECT_DOUBLE_EQ(c(0, 0), 8.75);
  EXPECT_DOUBLE_EQ(c(0, 1), 13.25);
  EXPECT_DOUBLE_EQ(c(0, 2), 17.75);
  EXPECT_DOUBLE_EQ(c(1, 0), 13.25);
  EXPECT_DOUBLE_EQ(c(1, 1), 20.75);
  EXPECT_DOUBLE_EQ(c(1, 2), 28.25);
  EXPECT_DOUBLE_EQ(c(2, 0), 17.75);
  EXPECT_DOUBLE_EQ(c(2, 1), 28.25);
  EXPECT_DOUBLE_EQ(c(2, 2), 38.75);
}

TEST(The_multiply_operator_matrix, test_142) {
  math::Matrix a(1, 3);
  math::Matrix b(3, 1);
  math::Matrix c;
  for (int i = 0; i < a.GetRows(); i++) {
    for (int j = 0; j < a.GetColumns(); j++) {
      a(i, j) = i + j + 0.0125;
    }
  }
  for (int i = 0; i < b.GetRows(); i++) {
    for (int j = 0; j < b.GetColumns(); j++) {
      b(i, j) = i + j + 0.075;
    }
  }
  c = a * b;
  EXPECT_EQ(a.GetRows(), 1);
  EXPECT_EQ(a.GetColumns(), 3);
  EXPECT_EQ(b.GetRows(), 3);
  EXPECT_EQ(b.GetColumns(), 1);
  EXPECT_EQ(c.GetRows(), 1);
  EXPECT_EQ(c.GetColumns(), 1);
  EXPECT_NEAR(c(0, 0), 5.2653125, 1E-7);
}

TEST(The_multiply_operator_matrix, test_143) {
  math::Matrix a(2, 1);
  math::Matrix b(1, 2);
  math::Matrix c;
  for (int i = 0; i < a.GetRows(); i++) {
    for (int j = 0; j < a.GetColumns(); j++) {
      a(i, j) = i + j + 0.0125;
    }
  }
  for (int i = 0; i < b.GetRows(); i++) {
    for (int j = 0; j < b.GetColumns(); j++) {
      b(i, j) = i + j + 0.075;
    }
  }
  c = a * b;
  EXPECT_EQ(a.GetRows(), 2);
  EXPECT_EQ(a.GetColumns(), 1);
  EXPECT_EQ(b.GetRows(), 1);
  EXPECT_EQ(b.GetColumns(), 2);
  EXPECT_EQ(c.GetRows(), 2);
  EXPECT_EQ(c.GetColumns(), 2);
  EXPECT_NEAR(c(0, 0), 0.0009375, 1E-7);
  EXPECT_NEAR(c(0, 1), 0.0134375, 1E-7);
  EXPECT_NEAR(c(1, 0), 0.0759375, 1E-7);
  EXPECT_NEAR(c(1, 1), 1.0884375, 1E-7);
}

TEST(The_multiply_operator_number, test_144) {
  math::Matrix a(12, 8);
  math::Matrix c;
  for (int i = 0; i < a.GetRows(); i++) {
    for (int j = 0; j < a.GetColumns(); j++) {
      a(i, j) = i + j + 0.0125;
    }
  }
  c = a * 13.099388;
  EXPECT_EQ(a.GetRows(), 12);
  EXPECT_EQ(a.GetColumns(), 8);
  EXPECT_EQ(c.GetRows(), 12);
  EXPECT_EQ(c.GetColumns(), 8);
  for (int i = 0; i < a.GetRows(); i++) {
    for (int j = 0; j < a.GetColumns(); j++) {
      EXPECT_DOUBLE_EQ(a(i, j), i + j + 0.0125);
    }
  }
  for (int i = 0; i < c.GetRows(); i++) {
    for (int j = 0; j < c.GetColumns(); j++) {
      EXPECT_DOUBLE_EQ(c(i, j), (i + j + 0.0125) * 13.099388);
    }
  }
}

// Operator+____________________________________________________________
TEST(MatrixAddition, test_145) {
  math::Matrix a(5, 8);
  math::Matrix b(5, 8);
  math::Matrix c;
  for (int i = 0; i < a.GetRows(); i++) {
    for (int j = 0; j < a.GetColumns(); j++) {
      a(i, j) = i + j + 0.0125;
      b(i, j) = i + j + 0.9975;
    }
  }
  c = a + b;
  EXPECT_EQ(a.GetRows(), 5);
  EXPECT_EQ(a.GetColumns(), 8);
  EXPECT_EQ(b.GetRows(), 5);
  EXPECT_EQ(b.GetColumns(), 8);
  EXPECT_EQ(c.GetRows(), 5);
  EXPECT_EQ(c.GetColumns(), 8);
  for (int i = 0; i < a.GetRows(); i++) {
    for (int j = 0; j < a.GetColumns(); j++) {
      EXPECT_DOUBLE_EQ(a(i, j), i + j + 0.0125);
      EXPECT_DOUBLE_EQ(b(i, j), i + j + 0.9975);
      EXPECT_DOUBLE_EQ(c(i, j), i + j + 0.0125 + i + j + 0.9975);
    }
  }
}

// Operator-____________________________________________________________
TEST(MatrixSubtraction, test_146) {
  math::Matrix a(5, 8);
  math::Matrix b(5, 8);
  math::Matrix c;
  for (int i = 0; i < a.GetRows(); i++) {
    for (int j = 0; j < a.GetColumns(); j++) {
      a(i, j) = i + j + 0.0125;
      b(i, j) = i + j + 0.9975;
    }
  }
  c = a - b;
  EXPECT_EQ(a.GetRows(), 5);
  EXPECT_EQ(a.GetColumns(), 8);
  EXPECT_EQ(b.GetRows(), 5);
  EXPECT_EQ(b.GetColumns(), 8);
  EXPECT_EQ(c.GetRows(), 5);
  EXPECT_EQ(c.GetColumns(), 8);
  for (int i = 0; i < a.GetRows(); i++) {
    for (int j = 0; j < a.GetColumns(); j++) {
      EXPECT_DOUBLE_EQ(a(i, j), i + j + 0.0125);
      EXPECT_DOUBLE_EQ(b(i, j), i + j + 0.9975);
      EXPECT_DOUBLE_EQ(c(i, j), i + j + 0.0125 - (i + j + 0.9975));
    }
  }
}

// Operator*=____________________________________________________________
TEST(MatrixMultiplyM, test_147) {
  math::Matrix a(1, 4);
  math::Matrix b(4, 1);
  for (int i = 0; i < a.GetRows(); i++) {
    for (int j = 0; j < a.GetColumns(); j++) {
      a(i, j) = j + 0.9999;
      b(j, i) = a(i, j);
    }
  }
  a *= b;
  EXPECT_EQ(a.GetRows(), 1);
  EXPECT_EQ(a.GetColumns(), 1);
  EXPECT_EQ(b.GetRows(), 4);
  EXPECT_EQ(b.GetColumns(), 1);
  EXPECT_NEAR(a(0, 0), 29.99800004, 1E-8);
}

TEST(MatrixMultiplyN, test_148) {
  math::Matrix a(1, 6);
  for (int i = 0; i < a.GetRows(); i++) {
    for (int j = 0; j < a.GetColumns(); j++) {
      a(i, j) = j + 0.9999;
    }
  }
  a *= 0.999993;
  EXPECT_EQ(a.GetRows(), 1);
  EXPECT_EQ(a.GetColumns(), 6);
  for (int i = 0; i < a.GetRows(); i++) {
    for (int j = 0; j < a.GetColumns(); j++) {
      EXPECT_NEAR(a(i, j), (j + 0.9999) * 0.999993, 1E-8);
    }
  }
}

// Operator+=____________________________________________________________
TEST(MatrixAddEq, test_149) {
  math::Matrix a(4, 2);
  math::Matrix b(4, 2);
  for (int i = 0; i < a.GetRows(); i++) {
    for (int j = 0; j < a.GetColumns(); j++) {
      a(i, j) = i + j;
      b(i, j) = a(i, j);
    }
  }
  a += b;
  EXPECT_EQ(a.GetRows(), 4);
  EXPECT_EQ(a.GetColumns(), 2);
  EXPECT_EQ(b.GetRows(), 4);
  EXPECT_EQ(b.GetColumns(), 2);
  for (int i = 0; i < a.GetRows(); i++) {
    for (int j = 0; j < a.GetColumns(); j++) {
      EXPECT_DOUBLE_EQ(a(i, j), (i + j) * 2);
    }
  }
}

// Operator-=____________________________________________________________
TEST(MatrixSubEq, test_150) {
  math::Matrix a(4, 2);
  math::Matrix b(4, 2);
  for (int i = 0; i < a.GetRows(); i++) {
    for (int j = 0; j < a.GetColumns(); j++) {
      a(i, j) = i + j;
      b(i, j) = a(i, j);
    }
  }
  a -= b;
  EXPECT_EQ(a.GetRows(), 4);
  EXPECT_EQ(a.GetColumns(), 2);
  EXPECT_EQ(b.GetRows(), 4);
  EXPECT_EQ(b.GetColumns(), 2);
  for (int i = 0; i < a.GetRows(); i++) {
    for (int j = 0; j < a.GetColumns(); j++) {
      EXPECT_DOUBLE_EQ(a(i, j), 0);
    }
  }
}

// Operator=____________________________________________________________
TEST(Assignment_Operator, test_151) {
  math::Matrix a(4, 2);
  math::Matrix b;
  b.SetRows(3);
  b.SetColumns(3);
  a(0, 1) = -4;
  b = a;
  EXPECT_EQ(a.GetRows(), 4);
  EXPECT_EQ(a.GetColumns(), 2);
  EXPECT_EQ(b.GetRows(), 4);
  EXPECT_EQ(b.GetColumns(), 2);
  for (int i = 0; i < b.GetRows(); i++) {
    for (int j = 0; j < b.GetColumns(); j++) {
      if (i != 0 && j != 1) {
        EXPECT_DOUBLE_EQ(b(i, j), 0);
      } else if (i == 0 && j == 1) {
        EXPECT_DOUBLE_EQ(b(i, j), -4);
      }
    }
  }
}

TEST(Assignment_Operator, test_152) {
  math::Matrix a(4, 2);
  math::Matrix b;
  b.SetRows(3);
  b.SetColumns(3);
  b(0, 1) = -4;
  a = b;
  EXPECT_EQ(a.GetRows(), 3);
  EXPECT_EQ(a.GetColumns(), 3);
  EXPECT_EQ(b.GetRows(), 3);
  EXPECT_EQ(b.GetColumns(), 3);
  for (int i = 0; i < a.GetRows(); i++) {
    for (int j = 0; j < a.GetColumns(); j++) {
      if (i != 0 && j != 1) {
        EXPECT_DOUBLE_EQ(a(i, j), 0);
      } else if (i == 0 && j == 1) {
        EXPECT_DOUBLE_EQ(a(i, j), -4);
      }
    }
  }
}

TEST(Assignment_Operator, test_155) {
  math::Matrix a(12, 12);
  math::Matrix b;
  b = a;
  EXPECT_EQ(a.GetRows(), 12);
  EXPECT_EQ(a.GetColumns(), 12);
  EXPECT_EQ(b.GetRows(), 12);
  EXPECT_EQ(b.GetColumns(), 12);
}
// create by lynseypi (@JoKeRooo7)