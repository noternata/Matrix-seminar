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

        if (rA > 0 && cA > 0) {
            std::cout << "A.at(0, 0) = " << A.at(0, 0) << "\n"; 
            std::cout << "A[{0, 0}] = " << A[{0, 0}] << "\n";
        }

        Matrix* Aclone = A.clone();
        std::cout << "\nClone of A:\n" << *Aclone << "\n";
        //delete Aclone;
        
        std::complex<double> dA = A.det();
        std::cout << "det(A) = (" << dA.real() << ", " << dA.imag() << ")\n";

        // Считываем вторую матрицу B
        std::cout << "Enter rows and cols for matrix B: ";
        size_t rB, cB;
        std::cin >> rB >> cB;
        Matrix B(rB, cB);

        std::cout << "Enter B elements in format (re, im):\n";
        std::cin >> B;

        std::cout << "Matrix B:\n" << B << "\n";

        // Сложение/вычитание (если размеры совпадают)
        if (rA == rB && cA == cB) {
            Matrix Sum = A + B;
            std::cout << "A + B:\n" << Sum << "\n";

            Matrix Diff = A - B;
            std::cout << "A - B:\n" << Diff << "\n";

            *Aclone += B;
            std::cout << "A += B:\n" << *Aclone << "\n";

            Aclone = A.clone();
            *Aclone -= B;
            std::cout << "A -= B:\n" << *Aclone << "\n";

        }
        delete Aclone;

        Matrix negA = -A;
        std::cout << "(-A):\n" << negA << "\n";

        // Умножение матрицы A на число
        std::complex<double> num(2.0, -1.0);
        Matrix New_matr = A * num;
        std::cout << "A * (2 - i):\n" << New_matr << "\n";

        // Матричное умножение A и B (если cols A == rows B)
        if (cA == rB) {
            Matrix Proizv = A * B;
            std::cout << "A * B:\n" << Proizv << "\n";
        }

    }
    catch (std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }
    return 0;
}
