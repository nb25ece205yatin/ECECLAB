#include <cmath>
#include <iostream>
#include <memory>
#include <string>
#include <vector>
using namespace std;

class Shape {
public:
    virtual double area() const = 0;
    virtual string name() const = 0;
    virtual ~Shape() = default;
};

class Circle : public Shape {
    double radius;
public:
    explicit Circle(double value) : radius(value) {}
    double area() const override { return 3.14159 * radius * radius; }
    string name() const override { return "Circle"; }
};

class Square : public Shape {
    double side;
public:
    explicit Square(double value) : side(value) {}
    double area() const override { return side * side; }
    string name() const override { return "Square"; }
};

class Triangle : public Shape {
    double a;
    double b;
    double c;
public:
    Triangle(double first, double second, double third)
        : a(first), b(second), c(third) {}
    double area() const override {
        const double s = (a + b + c) / 2.0;
        return sqrt(s * (s - a) * (s - b) * (s - c));
    }
    string name() const override { return "Triangle"; }
};

int main() {
    vector<unique_ptr<Shape>> shapes;
    string kind;
    cout << "Enter circle, square, triangle, or done:\n";

    while (cin >> kind && kind != "done") {
        if (kind == "circle") {
            double radius;
            if (!(cin >> radius) || radius <= 0) {
                cerr << "Circle radius must be positive.\n";
                return 1;
            }
            shapes.push_back(make_unique<Circle>(radius));
        }
        else if (kind == "square") {
            double side;
            if (!(cin >> side) || side <= 0) {
                cerr << "Square side must be positive.\n";
                return 1;
            }
            shapes.push_back(make_unique<Square>(side));
        }
        else if (kind == "triangle") {
            double a, b, c;
            if (!(cin >> a >> b >> c) || a <= 0 || b <= 0 || c <= 0 ||
                a + b <= c || a + c <= b || b + c <= a) {
                cerr << "Enter three positive sides that form a triangle.\n";
                return 1;
            }
            shapes.push_back(make_unique<Triangle>(a, b, c));
        }
        else {
            cerr << "Unknown shape: " << kind << '\n';
            return 1;
        }
    }

    for (const auto& shape : shapes) {
        cout << shape->name() << " area = " << shape->area() << '\n';
    }
    return 0;
}
