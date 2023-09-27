# Matrix

---

Matrices in C++. Using an object-oriented approach. By [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html )
This project was made with the aim of creating libraries for studying oop, where there will be operations for working with matrices.

---

* [Exceptions](#exceptions)
* [Oop in matrices](#oop-in-matrices)
* [Matrix assignment](#matrix-assignment)
* [Creating a matrix](#creating-a-matrix)
* [Removing a matrix](#removing-a-matrix)
* [Assessors](#assessorshttpsenwikipediaorgwikiassessorlaw)
* [Mutator](#mutatorhttpsenwikipediaorgwikimutatormethod)
* [Multiplying a matrix by a number](#multiplying-a-matrix-by-a-number)
* [Addition and subtraction of matrices](#addition-and-subtraction-of-matrices)
* [Matrix multiplication by matrix](#matrix-multiplication-by-matrix)
* [Matrix comparison](#matrix-comparison)
* [Determinant](#determinant)
* [Transpose](#transpose)
* [Inverse matrix](#inverse-matrix)
* [Matrix of algebraic additions](#matrix-of-algebraic-additions)
* [Matrix output](#matrix-output)
* [Input to matrix](#input-to-matrix)
* [Library](#library)

---

## Exceptions

In the case when these operations or functions are not possible, I have exceptions that interrupt the operation of the program. (you can catch them and continue working).

```cpp
throw std::invalid_argument("No correct")
```

---

## oop in matrices

The matrix is represented as a class.

```cpp
class Matrix {...};
```

The class is located in math shells

```cpp
namespace math {
    class Matrix {
        ....
    };
}  // namespace math
```

Since it was necessary to implement a destructor, all constructs corresponding to the [rule of three](https://en.wikipedia.org/wiki/Rule_of_three_(C%2B%2B_programming))

The parameterized constructor is represented as 

```cpr
explicit Matrix(int rows, int cols);
```

---

## Matrix assignment

To assign one matrix to another, there are overloaded `=` operators. Operators are overloaded only for assigning matrices and moving one matrix to another 

```cpp
Matrix &operator=(const Matrix &other) noexcept;
Matrix &operator=(Matrix &&other) noexcept;
```

---

## Creating a matrix

Creating an empty matrix.

```cpp
int main() {
    math::Matrix my_matrix;
}
```

Creating a matrix of size 4 by 9.

```cpp
int main() {
    math::Matrix my_matrix(4, 9);
}
```

Creating a matrix based on another matrix

```cpp
int main() {
    math::Matrix my_matrix(4, 9);
    math::Matrix my_new_matrix(my_matrix);
}
```

Creating a new matrix with the removal of the old one

```cpp
int main() {
    math::Matrix my_matrix(4, 9);
    math::Matrix my_new_matrix = std::move(my_matrix);
}
```

---

## Removing a matrix

The object is deleted automatically when it goes out of sight. To do this, a destructor is used. In no case should it be explicitly called. To clear matrix elements, there is a function ``Clear()``

```cpp
int main() {
    math::Matrix my_matrix(4, 9);
    my_matrix.Clear()
}
```

---

## [Assessors](https://en.wikipedia.org/wiki/Assessor_(law))

Assessors - are used to get elements from the protected fields of the class. 

There are 3 assessors in the class:

```cpp
GetRows() // getting the size of the matrix row
getColumns() // getting the size of the matrix
columns double &operator()(int i, int j) // Getting an element and accessing it
``

Usage example:

``cpp
int main() {
math::Matrix my_matrix(4,9);
// access to element 0, 0
std::cout << my_matrix(0,0) << std::endl; 
    std::cout << my_matrix.GetRows() << std::endl;
}
```

    There is an overloaded[] operator in the code, it is not recommended for use, since there is access to uninitialized memory.

---

## [Mutator](https://en.wikipedia.org/wiki/Mutator_method)

Mutators - for assigning a value.

There are 3 assessors in the class:

```cpp
SetRows() // Set the size of the matrix row
setColumns() // Set the size of the matrix columns
SetRowsColumns(int rows, int cols);
double &operator()(int i, int j) // Adding an element and accessing it
``

Usage example:

``cpp
int main() {
math::Matrix my_matrix(4,9);
// access to element 0, 1
    my_matrix(0, 1) = 5; // Now he's a raver 5
    my_matrix.SetRows() = 3;
}
```

    There is an overloaded[] operator in the code, it is not recommended for use, since there is access to uninitialized memory.

---

## Multiplying a matrix by a number

To multiply a matrix by a number, I have the following constructions:

```cpp
// multiplies the current matrix by a number by changing its value
void MulNumber(const double num) noexcept; 

// multiplies the current matrix by a number without changing its value and returns a new matrix
Matrix operator*(const double numbers) const noexcept;

// multiplies the number by the matrix without changing it and returns a new matrix
friend Matrix operator*(const double num, const Matrix& matrix);
```

```cpp
int main() {
    math::Matrix my_matrix(2, 2);
    math::Matrix new_matrix;
    new_matrix = my_matrix * 4.2;
    mew_matrix = 4.2 * my_matrix;
    my_matrix.MulNumber(4.2); // my_matrix == new_matrix
}
```

---

## Addition and subtraction of matrices

For addition and subtraction of matrices, there are overloaded functions and operators.

```cpp
// Adding or subtracting to or from the current matrix with overwriting
void SumMatrix(const Matrix &other); // +
void SubMatrix(const Matrix &othet); // -
Matrix &operator+=(const Matrix &other); // +=
Matrix &operator-=(const Matrix &other); // -=

// Without overwriting with the return of a new one 
Matrix operator+(const Matrix &other) const noexcept; // +
Matrix operator-(const Matrix &other) const noexcept; // -

```

```cpp
int main() {
    math::Matrix my_matrix(3,3);
    math::Matrix old_matrix(3,3);
    math::Matrix new_matrix;

    new_matrix = my_matrix + old_matrix;
    new_matrix.SubMatrix(old_matrix);
    new_matrix.SumMatrix(old_matrix);
    new_matrix = my_matrix - old_matrix;
    new_matrix -= old_matrix;
    new_matrix += my_matrix;
}

```

---

## Matrix multiplication by matrix

Constructions:

```cpp
// overwriting the current
void MulMatrix(const Matrix &other);
Matrix &operator*=(const Matrix &other);
// without overwriting
Matrix operator*(const double numbers) const;
```

```cpp
int main() {
    math::Matrix my_first_matrix(1, 9);
    math::Matrix my_second_matrix(9, 1);

    math::Matrix matrix = my_first_matrix * my_second_matrix;

    my_first_matrix *= my_second_matrix;
    matri.MulMatrix(my_first_matrix);
}
```

---

## Matrix comparison

Constructions:

```cpp
bool EqMatrix(const Matrix &other) const noexcept;
bool operator!=(const Matrix &other) const noexcept;
bool operator==(const Matrix &other) const noexcept;
```

```cpp
int main() {
    math::Matrix first_matrix(3,3);
    math::Matrix second_matrix(3,3);
    
    bool result;
    first_matrix.EqMatrix(second_matrix);
    result = (first_matrix == second_matrix);
    result = (first_matrix != second_matrix);
}
```

---

## Determinant

To find the determinant:

```cpp
double Determinant() const;
```

```cpp
int main() {
    math::Matrix my_matrix;
    double result;
    result = my_matrix.Determinant();
}
```

One of the fastest algorithms is used - the Gaus algorithm.

---

## Transpose 

To find the transposed matrix:

```cpp
Matrix Transponse() const noexcept;
```

```cpp
int main() {
    math::Matrix my_matrix;
    math::Matrix new_matrix;

    new_matrix = my_matrix.Transponse();
}

```

when transposed, it will return a new matrix.

---

## Inverse matrix

To find the inverse matrix:

```cpp
Matrix InverseMatrix() const;
```

```cpp
int main() {
    math::Matrix my_matrix(4,4);
    math::Matrix in_matrix;

    in_matrix = my_matrix.InverseMatrix();
}

```

---

## Matrix of algebraic additions

To find the matrix of algebraic complements:

```cpp
Matrix CalcComplements() const;
```

```cpp
int main() {
    math::Matrix my_matrix(4, 4);
    math::Matrix in_matrix;

}

```

---

## Matrix output

Output of the entire matrix:

```cpp
friend std::ostream &operator<<(std::ostream &os, const Matrix &other);
```

```cpp
int main() {
    math::Matrix matrix(2, 3);

    std::cout << matrix << std::endl;
    /*0 0 0 
      0 0 0*/
}

```

---

## Input to matrix

```cpp
int main() {
    math::Matrix matrix(2, 2);

    std::cin >> matrix;
}
```

---

## Library

It is enough to download two header files for yourself to use. Files with the extension .h .tpp. and connect .h, .tpp in the project file does not need to be connected, it is connected in .h. .h and .tpp should be located in the same directory.
