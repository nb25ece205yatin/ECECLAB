#include <iostream>
#include <memory>
#include <stdexcept>
#include <vector>
using namespace std;

class Matrix {
    int rows;
    int cols;
    vector<unique_ptr<int[]>> data;

public:
    Matrix(int r, int c) : rows(r), cols(c) {
        for (int i = 0; i < rows; ++i) {
            data.push_back(make_unique<int[]>(cols));
        }
    }

    Matrix(const Matrix& other) : Matrix(other.rows, other.cols) {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                data[i][j] = other.data[i][j];
            }
        }
    }

    void input() {
        cout << "Enter " << rows * cols << " matrix elements:\n";
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (!(cin >> data[i][j])) {
                    throw runtime_error("invalid matrix input");
                }
            }
        }
    }

    void display() const {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                cout << data[i][j] << " ";
            }
            cout << '\n';
        }
    }
};

int main() {
    try {
        Matrix original(2, 3);
        original.input();
        cout << "Original matrix:\n";
        original.display();

        Matrix copy = original;
        cout << "Deep-copied matrix:\n";
        copy.display();
    }
    catch (const exception& e) {
        cerr << "Error: " << e.what() << '\n';
        return 1;
    }
    return 0;
}
