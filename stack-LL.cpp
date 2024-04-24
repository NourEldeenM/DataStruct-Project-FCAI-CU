#include "singlyLL.cpp"

template <typename T>

class Stack
{
private:
    singlyLinkedList<T> linkedList;

public:
    void push(T element)
    {
        linkedList.insertAtHead(element);
    }

    T pop()
    {
        if (isEmpty())
        {
            cerr << "Stack is empty, Cannot pop the top element." << endl;
        }
        T element = linkedList.retrieveAt(1)->data;
        linkedList.removeAtHead();
        return element;
    }

    T top()
    {
        if (isEmpty())
        {
            cerr << "Stack is empty, Cannot get the top element." << endl;
        }
        return linkedList.retrieveAt(1)->data;
    }

    bool isEmpty()
    {
        return linkedList.isEmpty();
    }

    int stackSize()
    {
        return linkedList.linkedListSize();
    }

    void clear()
    {
        linkedList.clear();
    }

    void print()
    {
        linkedList.print();
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

    return 0;
}