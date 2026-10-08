#include <iostream>
using namespace std;

class Tracer
{
    int id;

public:
    Tracer(int i)
    {
        id = i;
        cout << "Tracer " << id << " created." << endl;
    }

    ~Tracer()
    {
        cout << "Tracer " << id << " destroyed." << endl;
    }
};

int main()
{
    for (int i = 1; i <= 5; i++)
    {
        Tracer *t = new Tracer(i);

        cout << "Tracer " << i << " is being used." << endl;

        delete t;
    }

    cout << "All tracers destroyed." << endl;

    return 0;
}
