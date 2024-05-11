#include <bits/stdc++.h>
using namespace std;

const int MAX_SIZE = 100;

template <typename T>
class Stack
{
private:
    T arr[MAX_SIZE];
    int topElement;

public:
    Stack()
    {
        topElement = -1;
    }

    bool isEmpty()
    {
        return topElement == -1;
    }

    int stackSize()
    {
        return topElement + 1;
    }

    void push(const T &element)
    {
        if (topElement == MAX_SIZE - 1)
        {
            cout << "Stack is full !" << endl;
            return;
        }
        arr[++topElement] = element;
    }

    T pop()
    {
        if (isEmpty())
        {
            cout << "Stack is empty !" << endl;
            return T();
        }
        return arr[topElement--];
    }

    T top()
    {
        if (isEmpty())
        {
            cout << "Stack is empty !" << endl;
            return T();
        }
        return arr[topElement];
    }

    void clear()
    {
        topElement = -1;
    }

    void print()
    {
        if (isEmpty())
        {
            cout << "Stack is empty !" << endl;
            return;
        }
        cout << "Stack elements: ";
        for (int i = topElement; i >= 0; --i)
        {
            cout << arr[i] << " ";
        }
        cout << endl;
    }
};

int main()
{
    Stack<int> st;
    st.push(2);
    st.push(4);
    st.push(6);
    st.push(9);
    st.push(31);
    st.print();
    cout << st.pop() << endl;
    st.print();
    cout << st.top() << endl;
    cout << st.stackSize() << endl;
    cout << st.isEmpty() << endl;
    st.clear();
    st.print();

    return 0;
}