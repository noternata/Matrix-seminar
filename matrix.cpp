#include "matrix.hpp"
#include <iostream>
#include <cmath>
#include <stdexcept>

// Конструктор
Matrix::Matrix(size_t rows, size_t cols)
    : m_rows(rows), m_cols(cols)
{
    // Выделяем память под rows * cols комплексных чисел
    m_data = new std::complex<double>[m_rows * m_cols];
    for (size_t i = 0; i < m_rows * m_cols; i++) {
        m_data[i] = std::complex<double>(0.0, 0.0);
    }
}

// Копирующий конструктор
Matrix::Matrix(Matrix&& other) noexcept
    : m_rows(other.m_rows),
      m_cols(other.m_cols),
      m_data(other.m_data)
{
    other.m_data = nullptr;
    other.m_rows = 0;
    other.m_cols = 0;
}

// Перегрузка оператора присваивания
Matrix& Matrix::operator=(Matrix&& other) noexcept {
    if (this != &other) {
        delete[] m_data;
        m_rows = other.m_rows;
        m_cols = other.m_cols;
        m_data = other.m_data;
        // Обнуляем исходный объект
        other.m_data = nullptr;
        other.m_rows = 0;
        other.m_cols = 0;
    }
    return *this;
}

// Деструктор
Matrix::~Matrix() {
    delete[] m_data;  // Освобождаем память
}

// operator[]
std::complex<double>& Matrix::operator[](const Index& idx) {
    return m_data[index(idx.i, idx.j)];
}
const std::complex<double>& Matrix::operator[](const Index& idx) const {
    return m_data[index(idx.i, idx.j)];
}

// at()
std::complex<double>& Matrix::at(size_t row, size_t col) {
    // Если индексы некорректны, бросаем исключение
    if (row >= m_rows || col >= m_cols) {
        throw std::out_of_range("Index out of range");
    }
    // Возвращаем элемент из одномерного массива
    return m_data[index(row, col)];
}
const std::complex<double>& Matrix::at(size_t row, size_t col) const {
    if (row >= m_rows || col >= m_cols) {
        throw std::out_of_range("Index out of range");
    }
    return m_data[index(row, col)];
}

// clone()
Matrix* Matrix::clone() const {
    // Создаём объект таких же размеров
    Matrix* newMat = new Matrix(m_rows, m_cols);
    // Копируем все элементы
    for (size_t i = 0; i < m_rows * m_cols; i++) {
        newMat->m_data[i] = m_data[i];
    }
    return newMat;
}

// operator+
// возвращаемы тип - матрица, оператор принадлежит классу Matrix::
// this - первая матрица, other- вторая матрица передается в качестве параметра
Matrix Matrix::operator+(const Matrix& other) const {
    // сравнение размерностей первой и второй матриц
    if (m_rows != other.m_rows || m_cols != other.m_cols)
        throw std::invalid_argument("Dimension mismatch for +");
    // матрица результат операции
    Matrix result(m_rows, m_cols);
    for (size_t i = 0; i < m_rows * m_cols; i++) {
        result.m_data[i] = m_data[i] + other.m_data[i];
    }
    return result;
}

//operator-
Matrix Matrix::operator-(const Matrix& other) const{
    if (m_rows != other.m_rows || m_cols != other.m_cols)
        throw std::invalid_argument("Dimension mismatch for -");
    Matrix result(m_rows, m_cols);
    for (size_t i = 0; i < m_rows * m_cols; i++) {
        result.m_data[i] = m_data[i] - other.m_data[i];
    }
    return result;
}

//operator+=
Matrix& Matrix::operator+=(const Matrix& other){
    if (m_rows != other.m_rows || m_cols != other.m_cols)
        throw std::invalid_argument("Dimension mismatch for +=");
    for(size_t i =0 ; i < m_rows * m_cols; i++) {
        m_data[i] += other.m_data[i];
    }
    return *this; 
}

//operator-=
Matrix& Matrix::operator-=(const Matrix& other){
    if (m_rows != other.m_rows || m_cols != other.m_cols)
        throw std::invalid_argument("Dimension mismatch for -=");
    for(size_t i =0 ; i < m_rows * m_cols; i++) {
        m_data[i] -= other.m_data[i];
    }
    return *this; 
}

//operator- унарный
Matrix Matrix::operator-() const{
    Matrix result(m_rows, m_cols);
    for (size_t i = 0; i < m_rows * m_cols; i++) {
        result.m_data[i] = -m_data[i];
    }
    return result;
}

//oprator* 2 матриц
Matrix Matrix::operator*(const Matrix& other) const{
    // Если кол-во элементов в столбце не равно кол-ву элементов в строке
    if ( m_cols != other.m_rows)
        throw std::invalid_argument("Dimension mismatch for *");
    Matrix result(m_rows, m_cols);
    for (size_t i = 0 ; i < m_rows; i++) {
        for (size_t j = 0 ; j < other.m_cols; j++) {
            for (size_t k = 0 ; k < m_cols; k++) {
                result.m_data[result.index(i, j)] += (m_data[index(i, k)] * other.m_data[other.index(k, j)]);
            }
        }
    }
    return result;
}

//operator* на число
Matrix Matrix::operator*(const std::complex<double>& num) const{
    Matrix result(m_rows, m_cols);
    for (size_t i = 0 ; i < m_rows * m_cols; i++) {
        result.m_data[i] = m_data[i] * num;
    }
    return result;
}

//operator/ на число
Matrix Matrix::operator/(const std::complex<double>& num) const{
    Matrix result(m_rows, m_cols);
    for (size_t i = 0 ; i < m_rows * m_cols; i++) {
        result.m_data[i] = m_data[i] / num;
    }
    return result;
}

// det()
std::complex<double> Matrix::det() const {
    if (m_rows != m_cols)
        throw std::invalid_argument("Not a square matrix!");
    // Делаем копию
    Matrix* temp = this->clone();
    std::complex<double> determinant(1, 0);

    for (size_t i = 0; i < m_rows; i++) {
        // Ищем ненулевой elem
        size_t elem = i;
        while (elem < m_rows && std::abs(temp->m_data[temp->index(elem, i)]) < 1e-10)
            elem++;
        if (elem == m_rows) {
            delete temp;
            return 0; 
        }
        if (elem != i) {
            for (size_t j = 0; j < m_rows; j++) {
                std::swap(temp->m_data[temp->index(i, j)], temp->m_data[temp->index(elem, j)]);
            }
            determinant = -determinant; 
        }
        std::complex<double> diagVal = temp->m_data[temp->index(i, i)];
        determinant *= diagVal;
        // Нормируем строку
        for (size_t j = i; j < m_rows; j++) {
            temp->m_data[temp->index(i, j)] /= diagVal;
        }
        // Обнуляем элементы ниже текущего
        for (size_t row = i+1; row < m_rows; row++) {
            std::complex<double> factor = temp->m_data[temp->index(row, i)];
            for (size_t col = i; col < m_rows; col++) {
                temp->m_data[temp->index(row, col)] -= factor * temp->m_data[temp->index(i, col)];
            }
        }
    }
    delete temp;
    return determinant;
}

// operator>>
// Формат ввода матрицы (1, 2) (9, 10) (11, 12) (13, 14)
std::istream& operator>>(std::istream& in, Matrix& matrix) {
    for (size_t i = 0; i < matrix.m_rows; i++) {
        for (size_t j = 0; j < matrix.m_cols; j++) {
            char ch;
            in >> ch; // '('
            if (ch != '(') {
                //устанавливаем ошибку
                in.setstate(std::ios::failbit);
                return in;
            }
            // действительная и мнимая части
            double real, imag;
            in >> real;
            in >> ch; // через ','
            if (ch != ',') {
                in.setstate(std::ios::failbit);
                return in;
            }
            in >> imag;
            in >> ch; // ')'
            if (ch != ')') {
                in.setstate(std::ios::failbit);
                return in;
            }
            matrix.m_data[matrix.index(i, j)] = std::complex<double>(real, imag);
        }
    }
    return in;
}

// operator<<
std::ostream& operator<<(std::ostream& out, const Matrix& matrix) {
    for (size_t i = 0; i < matrix.m_rows; i++) {
        for (size_t j = 0; j < matrix.m_cols; j++) {
            std::complex<double> val = matrix.m_data[matrix.index(i, j)];
            out << "(" << val.real() << ", " << val.imag() << ") ";
        }
        out << "\m_rows";
    }
    return out;
}