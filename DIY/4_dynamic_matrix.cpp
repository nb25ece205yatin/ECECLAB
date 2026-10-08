#include <iostream>
using namespace std;

class Matrix
{
    int rows, cols;
    int **data;

public:
    Matrix(int r, int c)
    {
        rows = r;
        cols = c;

        data = new int*[rows];

        for (int i = 0; i < rows; i++)
            data[i] = new int[cols];
    }

    void input()
    {
        cout << "Enter matrix elements:" << endl;

        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                cin >> data[i][j];
            }
        }
    }

    void display()
    {
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                cout << data[i][j] << " ";
            }

            cout << endl;
        }
    }

    Matrix(const Matrix &m)
    {
        rows = m.rows;
        cols = m.cols;

        data = new int*[rows];

        for (int i = 0; i < rows; i++)
        {
            data[i] = new int[cols];

            for (int j = 0; j < cols; j++)
            {
                data[i][j] = m.data[i][j];
            }
        }
    }

    ~Matrix()
    {
        for (int i = 0; i < rows; i++)
            delete[] data[i];

        delete[] data;
    }
};

int main()
{
    Matrix m1(2, 3);

    m1.input();

    cout << "\nOriginal Matrix:" << endl;
    m1.display();

    Matrix m2 = m1;

    cout << "\nCopied Matrix:" << endl;
    m2.display();

    return 0;
}
