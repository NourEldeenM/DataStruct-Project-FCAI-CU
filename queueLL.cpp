#include "singlyLL.cpp"

template <typename T>

class Queue
{
private:
    singlyLinkedList<T> linkedList;

public:
    void enqueue(T element)
    {
        linkedList.insertAtTail(element);
    }

    T dequeue()
    {
        if (isEmpty())
        {
            cerr << "Queue Underflow\n";
        }
        T element = linkedList.retrieveAt(1)->data;
        linkedList.removeAtHead();
        return element;
    }

    T first()
    {
        if (isEmpty())
        {
            cerr << "Queue is Empty\n";
        }
        return linkedList.retrieveAt(1)->data;
    }

    bool isEmpty()
    {
        return linkedList.isEmpty();
    }

    int queueSize()
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

// int main()
// {
//     Queue<int> q;
//     q.enqueue(2);
//     q.enqueue(4);
//     q.enqueue(6);
//     q.enqueue(9);
//     q.enqueue(31);
//     q.print();
//     cout << q.dequeue() << endl;
//     q.print();
//     cout << q.first() << endl;
//     cout << q.queueSize() << endl;
//     cout << q.isEmpty() << endl;
//     q.clear();

//     return 0;
// }

