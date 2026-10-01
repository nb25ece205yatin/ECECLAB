#include <iostream>
using namespace std;

class widget {
    int id;
    static int count;
public:
 widget(){ id = ++count; cout << "created w1 " << id  << endl;}
 ~widget() {--count; cout << "Destryed w1 " << id << endl;  }
 static int alive() { return count; }
};

int widget::count = 0;
int main() {
    widget a, b;
    cout << "alive: " << widget::alive() << endl;
   { widget c; cout << "alive: " << widget::alive() << endl; }
    cout << "alive: " << widget::alive() << endl;
    return 0;
}
