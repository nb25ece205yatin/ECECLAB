#include <iostream>
using namespace std;

double volume(double side)
{
    return side * side * side;
}

double volume(double length, double width, double height)
{
    return length * width * height;
}

double volume(double radius, double height)
{
    return 3.14159 * radius * radius * height;
}

int main()
{
    cout << "Volume of cube = "
         << volume(5.0) << endl;

    cout << "Volume of cuboid = "
         << volume(5.0, 4.0, 3.0) << endl;

    cout << "Volume of cylinder = "
         << volume(3.0, 7.0) << endl;

    return 0;
}
