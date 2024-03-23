#include <iostream>
#include <iomanip>
#include <random>
#include <ctime>
using namespace std;
template<typename T>
class Matrix {
private:
    T** data;
    size_t rows;
    size_t cols;
public:
    Matrix(size_t rows, size_t cols) : rows(rows), cols(cols) {
        data = new T * [rows];
        for (size_t i = 0; i < rows; ++i) {
            data[i] = new T[cols]();
        }
    }
    ~Matrix() {
        for (size_t i = 0; i < rows; ++i) {
            delete[] data[i];
        }
        delete[] data;
    }
    size_t getRows() const {
        return rows;
    }
    size_t getCols() const {
        return cols;
    }
    const T& operator()(size_t row, size_t col) const {
        return data[row][col];
    }
    T& operator()(size_t row, size_t col) {
        return data[row][col];
    }
    void fillFromKeyboard() {
        cout << "Enter matrix elements:" << endl;
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                std::cin >> data[i][j];
            }
        }
    }
    void fillWithRandom() {
        default_random_engine generator(time(nullptr));
        uniform_real_distribution<T> distribution(0.0, 100.0); 
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                data[i][j] = distribution(generator);
            }
        }
    }
    void print() const {
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                cout << setw(8) << data[i][j] << " ";
            }
            cout << endl;
        }
    }
    Matrix<T> operator+(const Matrix<T>& other) const {
        if (rows != other.getRows() || cols != other.getCols()) {
            throw invalid_argument("Matrix dimensions don't match");
        }
        Matrix<T> result(rows, cols);
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                result(i, j) = data[i][j] + other(i, j);
            }
        }
        return result;
    }
    Matrix<T> operator-(const Matrix<T>& other) const {
        if (rows != other.getRows() || cols != other.getCols()) {
            throw invalid_argument("Matrix dimensions don't match");
        }
        Matrix<T> result(rows, cols);
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                result(i, j) = data[i][j] - other(i, j);
            }
        }
        return result;
    }
    Matrix<T> operator*(const Matrix<T>& other) const {
        if (cols != other.getRows()) {
            throw invalid_argument("Incompatible matrix dimensions for multiplication");
        }
        Matrix<T> result(rows, other.getCols());
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < other.getCols(); ++j) {
                for (size_t k = 0; k < cols; ++k) {
                    result(i, j) += data[i][k] * other(k, j);
                }
            }
        }
        return result;
    }
    Matrix<T> operator/(const T& scalar) const {
        Matrix<T> result(rows, cols);
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                result(i, j) = data[i][j] / scalar;
            }
        }
        return result;
    }
    T findMax() const {
        T maxElement = data[0][0];
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                if (data[i][j] > maxElement) {
                    maxElement = data[i][j];
                }
            }
        }
        return maxElement;
    }
    T findMin() const {
        T minElement = data[0][0];
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                if (data[i][j] < minElement) {
                    minElement = data[i][j];
                }
            }
        }
        return minElement;
    }
};
int main() {
    Matrix<double> mat1(3, 3);
    Matrix<double> mat2(3, 3);
    mat1.fillWithRandom();
    mat2.fillWithRandom();
    cout << "Matrix 1:" << endl;
    mat1.print();
    cout << endl;
    cout << "Matrix 2:" << endl;
    mat2.print();
    cout << endl;
    Matrix<double> sum = mat1 + mat2;
    cout << "Sum of matrices:" << endl;
    sum.print();
    cout << endl;
    Matrix<double> difference = mat1 - mat2;
    cout << "Difference of matrices:" << endl;
    difference.print();
    Matrix<double> product = mat1 * mat2;
    cout << "Product of matrices:" << endl;
    product.print();
    cout << endl;
    double scalar = 2.0;
    Matrix<double> quotient = mat1 / scalar;
    cout << "Quotient of matrix 1 by scalar " << scalar << ":" << endl;
    quotient.print();
    cout << std::endl;
    cout << "Maximum element in matrix 1: " << mat1.findMax() << endl;
    cout << "Minimum element in matrix 1: " << mat1.findMin() << endl;
    return 0;
}

