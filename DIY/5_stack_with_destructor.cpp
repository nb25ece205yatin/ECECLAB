#include <iostream>
using namespace std;

class Stack
{
    int *arr;
    int top;
    int size;

public:
    Stack(int s)
    {
        size = s;
        top = -1;
        arr = new int[size];
    }

    void push(int value)
    {
        if (top == size - 1)
        {
            cout << "Stack Overflow" << endl;
        }
        else
        {
            arr[++top] = value;
            cout << value << " pushed into stack" << endl;
        }
    }

    void pop()
    {
        if (top == -1)
        {
            cout << "Stack Underflow" << endl;
        }
        else
        {
            cout << arr[top--] << " popped from stack" << endl;
        }
    }

    ~Stack()
    {
        delete[] arr;
        cout << "Stack memory released." << endl;
    }
};

int main()
{
    Stack s(5);

    s.push(10);
    s.push(20);
    s.push(30);

    s.pop();
    s.pop();

    return 0;
}
