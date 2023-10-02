# Матрица

---

Матрицы на языке C++. С применением объектно-ориентированного подхода. По [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html)
Данный проект сделан с целью создания библиотек изучения ооп, где будут операции по работе с матрицами.

---

* [Исключения](#исключения)
* [Ооп в матрицах](#ооп-в-матрицах)
* [Присваивание матрицы](#присваивание-матрицы)
* [Создание матрицы](#создание-матрицы)
* [Удаление матрицы](#удаление-матрицы)
* [Асессоры](#асессорыhttpsruwikipediaorgwikid090d181d0b5d181d181d0bed180)
* [Мутаторы](#мутаторыhttpsruwikipediaorgwikid0a1d0b5d182d182d0b5d180d0bfd180d0bed0b3d180d0b0d0bcd0bcd0b8d180d0bed0b2d0b0d0bdd0b8d0b5)
* [Умножение матрицы на число](#умножение-матрицы-на-число)
* [Cложение и вычитание матриц](#cложение-и-вычитание-матриц)
* [Умножение матрицы на матрицу](#умножение-матрицы-на-матрицу)
* [Сравнение матриц](#сравнение-матриц)
* [Определитель](#определитель)
* [Транспонирование](#транспонирование)
* [Обратная матрица](#обратная-матрица)
* [Матрица алгебраических дополнений](#матрица-алгебраических-дополнений)
* [Вывод матрицы](#вывод-матрицы)
* [Ввод в матрциу](#ввод-в-матрицу)
* [Библиотека](#библиотека)

---

## Исключения

В случае когда данные операции или функции невозможны ,у меня вызываются исключения, прерывающие работу программы. (их можно отлавливать и продолжать работу).

```cpp
throw std::invalid_argument("No correct")
```

---

## ооп в матрицах

Матрица представлена в виде класса.

```cpp
class Matrix {...};
```

Класс находится в оболочке math

```cpp
namespace math {
    class Matrix {
        ....
    };
}  // namespace math
```

Так как необходимо было реализовывать деструктор, были реализованы все конструкции соответсвующие [правилу пяти](https://ru.wikipedia.org/wiki/%D0%9F%D1%80%D0%B0%D0%B2%D0%B8%D0%BB%D0%BE_%D1%82%D1%80%D1%91%D1%85_(C%2B%2B)#%D0%9F%D1%80%D0%B0%D0%B2%D0%B8%D0%BB%D0%BE_%D0%BF%D1%8F%D1%82%D0%B8)

Параметризированный конструктор представлен в виде 

```сpp
explicit Matrix(int rows, int cols);
```

---

## Присваивание матрицы

Чтобы присвоить одну матрицу к другой, есть перегруженные операторы `=`. Операторы перегружены только для присваивания матриц и перемещения одной матрицы в другую 

```cpp
Matrix &operator=(const Matrix &other) noexcept;
Matrix &operator=(Matrix &&other) noexcept;
```

---

## Создание матрицы

Создание пустой матрицы.

```cpp
int main() {
    math::Matrix my_matrix;
}
```

Создание матрицы размера 4 на 9.

```cpp
int main() {
    math::Matrix my_matrix(4, 9);
}
```

Создание матрицы на основе другой матрицы

```cpp
int main() {
    math::Matrix my_matrix(4, 9);
    math::Matrix my_new_matrix(my_matrix);
}
```

Создание новой матрицы с удалением старой

```cpp
int main() {
    math::Matrix my_matrix(4, 9);
    math::Matrix my_new_matrix = std::move(my_matrix);
}
```

---

## Удаление матрицы

Удаление объекта происходит автоматически, когда он выходит за пределы видимости. Для этого используетс деструктор. Ни в коем случае его явно не вызывать. Для очистки элементов матрицы есть функция ```Clear()```

```cpp
int main() {
    math::Matrix my_matrix(4, 9);
    my_matrix.Clear()
}
```

---

## [Асессоры](https://ru.wikipedia.org/wiki/%D0%90%D1%81%D0%B5%D1%81%D1%81%D0%BE%D1%80)

Асессоры - используются для получения элементов из защищенный полей класса. 

В классе есть 3 асессора:

```cpp
GetRows() // получение размера строки матрицы
GetColumns() // получение размера стобцов матрицы
double &operator()(int i, int j) // Получение элемента и доступ к нему 
```

Пример использования:

```cpp
int main() {
    math::Matrix my_matrix(4,9);
    // доступ к элементу 0, 0
    std::cout << my_matrix(0,0) << std::endl; 
    std::cout << my_matrix.GetRows() << std::endl;
}
```

    Есть в коде перегруженный оператор[], он закоменчен не рекомедую к использованию, так как есть доступ к неинициализированной памяти.

---

## [Мутаторы](https://ru.wikipedia.org/wiki/%D0%A1%D0%B5%D1%82%D1%82%D0%B5%D1%80_(%D0%BF%D1%80%D0%BE%D0%B3%D1%80%D0%B0%D0%BC%D0%BC%D0%B8%D1%80%D0%BE%D0%B2%D0%B0%D0%BD%D0%B8%D0%B5))

Мутаторы - для присвоения значения.

В классе есть 3 асессора:

```cpp
SetRows() // Задать размер строки матрицы
SetColumns() // Задать размер стобцов матрицы
SetRowsColumns(int rows, int cols);
double &operator()(int i, int j) // Присовение элемента и доступ к нему 
```

Пример использования:

```cpp
int main() {
    math::Matrix my_matrix(4,9);
    // доступ к элементу 0, 1
    my_matrix(0, 1) = 5; // теперь он равер 5
    my_matrix.SetRows() = 3;
}
```

    Есть в коде перегруженный оператор[], он закоменчен не рекомедую к использованию, так как есть доступ к неинициализированной памяти.

---

## Умножение матрицы на число

Для умножения матрицы на число у меня есть следующие конструкции:

```cpp
// умножит текущую матрицу на число изменив ее значение
void MulNumber(const double num) noexcept; 

// умножит текущую матрицу на число не изменив ее значение и вернет новую матрицу
Matrix operator*(const double numbers) const noexcept;

// умножит число на матрицу не изменив ее и вернет новую матрицу
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

## Cложение и вычитание матриц

Для сложения и вычитания матриц, есть перегруженные функции и операторы.

```cpp
// Присвивание или вычитание к текущей или из текущей матрицы с перезаписыванием
void SumMatrix(const Matrix &other); // +
void SubMatrix(const Matrix &othet); // -
Matrix &operator+=(const Matrix &other); // +=
Matrix &operator-=(const Matrix &other); // -=

// Без перезаписи с возвращением новой 
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

## Умножение матрицы на матрицу

Конструкции:

```cpp
// перезаписывание текущей
void MulMatrix(const Matrix &other);
Matrix &operator*=(const Matrix &other);
// без перезаписывания
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

## Сравнение матриц

Конструкции:

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

## Определитель

Для нахождения определителя:

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

Использован один из быстрых алгоритмов - алгоритм гауса.

---

## Транспонирование 

Для нахождения транспонированной матрицы:

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

при транспонирвоаниии вернет новую матрицу.

---

## Обратная матрица

Для нахождения обратной матрицы:

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

## Матрица алгебраических дополнений

Для нахождения матрицы алгебраических дополнений:

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

## Вывод матрицы

Вывод всей матрицы:

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

## Ввод в матрицу

```cpp
int main() {
    math::Matrix matrix(2, 2);

    std::cin >> matrix;
}
```

---

## Библиотека

Достаточно скачать себе два заголовычных файла, чтобы исполььзовать. Файлы с расширением .h .tpp. и подключить .h, .tpp в файле с проектом подключать не надо, он подключен в .h. .h и .tpp должны распологаться в одной директории.
