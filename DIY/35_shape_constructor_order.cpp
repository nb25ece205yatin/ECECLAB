#include <iostream>
#include <string>
#include <utility>

class Shape {
public:
    explicit Shape(std::string name) : name_(std::move(name)) {
        std::cout << "Shape constructor: " << name_ << '\n';
    }

protected:
    std::string name_;
};

class Polygon : public Shape {
public:
    Polygon(std::string name, int sides) : Shape(std::move(name)), sides_(sides) {
        std::cout << "Polygon constructor: " << sides_ << " sides\n";
    }

protected:
    int sides_;
};

class Rectangle : public Polygon {
public:
    Rectangle(std::string name, int sides, double length, double width)
        : Polygon(std::move(name), sides), length_(length), width_(width) {
        std::cout << "Rectangle constructor: " << length_ << " x " << width_ << '\n';
    }

private:
    double length_;
    double width_;
};

int main() {
    Rectangle rectangle("Rectangle", 4, 8.0, 5.0);
    (void)rectangle;
    return 0;
}
