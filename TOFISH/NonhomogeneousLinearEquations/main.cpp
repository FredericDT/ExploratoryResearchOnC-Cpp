#include <iostream>

const unsigned rows = 4;
const unsigned columns = 5;

double matrix[rows][columns] = {
        {1.1161, 0.1254, 0.1397, 0.1490, 1.5471},
        {0.1582, 1.1675, 0.1768, 0.1871, 1.6471},
        {0.2368, 0.2471, 0.2568, 1.2671, 1.8471},
        {0.1968, 0.2071, 1.2168, 0.2271, 1.7471}
};

int main() {

    //print
    std::cout << "MAT A = " << std::endl;
    for (int i = 0; i < rows; ++i) {
        for (int j = 1; j < columns; ++j) {
            std::cout << "\t" << matrix[i][j - 1];
        }
        std::cout << std::endl;
    }
    std::cout << "MAT B = " << std::endl;
    for (int i = 0; i < rows; ++i) {
        std::cout << "\t" << matrix[i][columns - 1];
    }
    std::cout << std::endl;

    for (int i = 1; i < rows; ++i) {
        for (int j = i; j < rows; ++j) {
            double base = matrix[j][i - 1] / matrix[i - 1][i - 1];
            for (int k = i - 1; k < columns; ++k) {
                matrix[j][k] -= base * matrix[i - 1][k];
            }
        }
    }

    double x[columns - 1];
    for (int i = rows - 1; i >= 0; --i) {
        int j = rows - 1;
        double base = matrix[i][columns - 1];
        while(j > i) {
            base -= matrix[i][j] * x[j];
            --j;
        }
        x[i] = base / matrix[i][i];
    }

    for (int i = 0; i < rows; ++i) {
        std::cout << "x(" << i + 1 << ")=" << x[i] << std::endl;
    }

    return 0;
}