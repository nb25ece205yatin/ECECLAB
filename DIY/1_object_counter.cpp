#include <iostream>
using namespace std;

class Counter
{
    static int totalCreated;
    static int alive;

public:
    Counter()
    {
        totalCreated++;
        alive++;
    }

    ~Counter()
    {
        alive--;
    }

    static void showCount()
    {
        cout << "Total objects ever created: " << totalCreated << endl;
        cout << "Currently alive objects: " << alive << endl;
    }
};

int Counter::totalCreated = 0;
int Counter::alive = 0;

int main()
{
    Counter c1, c2;

    Counter::showCount();

    {
        Counter c3;
        Counter::showCount();
    }

    cout << "\nAfter c3 is destroyed:" << endl;
    Counter::showCount();

    return 0;
}
