#include <iostream>
#include "matrix.hpp"

int main() {
    try {
        // Считываем размеры матрицы A
        std::cout << "Enter rows and cols for matrix A: ";
        size_t rA, cA;
        std::cin >> rA >> cA;

        // Создаём матрицу A
        Matrix A(rA, cA);

        // Считываем элементы
        std::cout << "Enter A elements in format (re, im):\n";
        std::cin >> A;

        std::cout << "Matrix A:\n" << A << "\n";

        // Считываем вторую матрицу B
        std::cout << "Enter rows and cols for matrix B: ";
        size_t rB, cB;
        std::cin >> rB >> cB;
        Matrix B(rB, cB);

        std::cout << "Enter B:\n";
        std::cin >> B;

        std::cout << "Matrix B:\n" << B << "\n";

        // Сложение/вычитание (если размеры совпадают)
        if (rA == rB && cA == cB) {
            Matrix Sum = A + B;
            std::cout << "A + B:\n" << Sum << "\n";

            Matrix Diff = A - B;
            std::cout << "A - B:\n" << Diff << "\n";
        }

        // Умножение матрицы A на скаляр
        std::complex<double> scalar(2.0, -1.0);
        Matrix Scaled = A * scalar;
        std::cout << "A * (2 - i):\n" << Scaled << "\n";

        // Матричное умножение A и B (если cols A == rows B)
        if (cA == rB) {
            Matrix Product = A * B;
            std::cout << "A * B:\n" << Product << "\n";
        }

    }
    catch (std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }
    return 0;
}
