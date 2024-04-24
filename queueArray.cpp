#include <iostream>
using namespace std;

const int MAX_SIZE = 10000;

template <typename dataType>
class Queue
{
private:
    int front;
    int rear;
    int queueSize;
    dataType arr[MAX_SIZE];

public:
    Queue() : front(0), rear(-1), queueSize(0) {}

    bool isEmpty();
    dataType first();
    void enqueue(dataType element);
    void dequeue();
    void print();
};
template <typename dataType>
void Queue<dataType>::print()
{
    if (isEmpty())
    {
        cerr << "Queue is Empty\n";
        return;
    }
    for (size_t i = front; i <= rear; i++)
    {
        cout<<arr[i]<<' ';
    }
    
    cout << '\n';
}

template <typename dataType>
bool Queue<dataType>::isEmpty()
{
    return queueSize == 0;
}

template <typename dataType>
dataType Queue<dataType>::first()
{
    if (isEmpty())
    {
        cerr << "Queue is Empty\n";
        // return dataType;
    }
    return arr[front];
}

template <typename dataType>
void Queue<dataType>::enqueue(dataType element)
{
    if (queueSize == MAX_SIZE)
    {
        cerr << "Queue Overflow\n";
        return;
    }
    rear = (rear + 1) % MAX_SIZE;
    arr[rear] = element;
    queueSize++;
}

template <typename dataType>
void Queue<dataType>::dequeue()
{
    if (isEmpty())
    {
        cerr << "Queue Underflow\n";
        return;
    }
    front = (front + 1) % MAX_SIZE;
    queueSize--;
}

int main()
{
    Queue<int> q;
    q.enqueue(1);
    q.enqueue(2);
    q.enqueue(3);

    cout << "First element: " << q.first() << endl;

    q.dequeue();
    cout << "First element after dequeue: " << q.first() << endl;
    q.first();
    q.print();
    q.dequeue();
    q.print();
    q.dequeue();
    q.print();
    q.dequeue();
    q.print();
    q.dequeue();
    q.dequeue();
    return 0;
}
