#include <iostream>
using namespace std;

class Distance {
    int feet, inches;
public:
    Distance(int f=0, int i =0) : feet(f), inches(i) {}
    
    friend Distance add(const Distance &a, const Distance &b);
    void show() const { cout << feet << "ft " << inches<< "in\n";}
};

Distance add(const Distance &a, const Distance &b) {
    int TotalInches = (a.feet + b.feet) * 12 + (a.inches + b.inches);
    return Distance(TotalInches / 12, TotalInches % 12);
}

int main() {
    Distance d1(5 ,8),d2(3,7);
    Distance d3 = add(d1,d2);
    d3.show();
    return 0;
}