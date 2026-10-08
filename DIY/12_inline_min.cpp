#include <iostream>
using namespace std;

inline int minVal(int a, int b)
{
    return (a < b) ? a : b;
}

inline int minVal(int a, int b, int c)
{
    return minVal(minVal(a, b), c);
}

int main()
{
    cout << "Minimum of 10 and 20 = "
         << minVal(10, 20) << endl;

    cout << "Minimum of 30, 15 and 25 = "
         << minVal(30, 15, 25) << endl;

    return 0;
}
