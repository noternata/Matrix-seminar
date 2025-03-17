#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <iostream>
#include <complex>
#include <stdexcept>
#include <cstddef>

// Индексы элемента
struct Index {
    size_t i;
    size_t j;
};

class Matrix {
public:
    // Конструктор
    Matrix(size_t rows, size_t cols);

    // Запрещаем копирование
    Matrix(const Matrix& other) = delete;
    Matrix& operator=(const Matrix& other) = delete;

    // Разрешаем перемещение
    Matrix(Matrix&& other) noexcept;
    Matrix& operator=(Matrix&& other) noexcept;

    // Деструктор
    ~Matrix();

    // Оператор доступа к элементам без проверки границ
    // Можно получить элемент так: A[{i, j}]
    // Возвращет ссылку на элемент типа complex c вещественной и действительной частями типа double
    std::complex<double>& operator[](const Index& idx);
    const std::complex<double>& operator[](const Index& idx) const;

    // Возвращает элемент с проверкой границ
    std::complex<double>& at(size_t row, size_t col);
    const std::complex<double>& at(size_t row, size_t col) const;

    // Получаем кол-во строк и столбцов
    size_t rows() const { return m_rows; }
    size_t cols() const { return m_cols; }

    // Возвращает указатель на копию матрицы
    Matrix* clone() const;

    // Перегрузка арифметических операторов
    // Сложение и вычитание матриц
    Matrix operator+(const Matrix& other) const;
    Matrix operator-(const Matrix& other) const;
    Matrix& operator+=(const Matrix& other);
    Matrix& operator-=(const Matrix& other);

    // Унарный минус
    // Возвращает матрицу с каждым элементом, умноженным на -1, не изменяя оригинал
    Matrix operator-() const;

    // Умножение матриц
    Matrix operator*(const Matrix& other) const;

    // Умножение матрицы на число
    Matrix operator*(const std::complex<double>& num) const;

    // Деление матрицы на число
    Matrix operator/(const std::complex<double>& num) const;

    // Вычисление детерминанта
    std::complex<double> det() const;

    // Решение СЛАУ Ax = b методом Гаусса
    // b должна быть вектор-столбцом с числом строк, равным числу строк матрицы A
    //Matrix solve(const Matrix& b) const;

    // Перегрузка операторов ввода/вывода.
    friend std::istream& operator>>(std::istream& in, Matrix& matrix);
    friend std::ostream& operator<<(std::ostream& out, const Matrix& matrix);

private:
    size_t m_rows;
    size_t m_cols;
    std::complex<double>* m_data;  // Указатель на динамический массив элементов

    // Вспомогательная функция, возвращающая индекс элемента (row, col)
    // в одномерном массиве m_data.
    size_t index(size_t row, size_t col) const {
        return row * m_cols + col;
    }
};

#endif // MATRIX_HPP
