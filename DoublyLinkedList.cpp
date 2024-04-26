#include "bits/stdc++.h"

using namespace std;

template <typename T>
struct Node
{
    T data{};
    Node *next{};
    Node *prev{};

    Node(T data) : data(data) {}

    void set(Node *next, Node *prev)
    {
        this->next = next;
        this->prev = prev;
    }

    ~Node()
    {
        cout << "Destroying value: " << data << " at address " << this << "\n";
    }
};

template <typename T>
class LinkedList
{
private:
    Node<T> *head{};
    Node<T> *tail{};
    int length = 0; // counter to count how many nodes

public:
    void insertAtHead(T element);

    void insertAtTail(T element);

    void insertAt(T element, int index);

    void removeAtHead();

    void removeAtTail();

    void removeAt(int index);

    T retrieveAt(int index);

    void replaceAt(T newElement, int index);

    bool isExist(T element);

    bool isItemAtEqual(T element, int index);

    void swap(int firstItemIdx, int secondItemIdx); // swap two nodes without swapping data.
    bool isEmpty();

    int linkedListSize();

    void clear();

    void print();

    // link 2 nodes in a DLL by making the second the next of the first and the first the previous of the second
    void link(Node<T> *first, Node<T> *second)
    {
        if (first)
            first->next = second;
        if (second)
            second->prev = first;
    }

    void delete_node(Node<T> *node)
    {
        delete node;
        length--;
    }
};

template <typename T>
void LinkedList<T>::insertAtHead(T element)
{
    Node<T> *newNode = new Node(element);
    if (!head)
        head = tail = newNode;
    else
    {
        link(newNode, head);
        head = newNode;
    }
    length++;
}

template <typename T>
void LinkedList<T>::insertAtTail(T element)
{
    Node<T> *newNode = new Node(element);
    if (!head)
        head = tail = newNode;
    else
    {
        link(tail, newNode);
        tail = newNode;
    }
    length++;
}

template <typename T>
void LinkedList<T>::insertAt(T element, int index)
{
    if (index == length + 1)
    {
        insertAtTail(element);
        return;
    }
    if (index == 1)
    {
        insertAtHead(element);
        return;
    }
    if (index > length)
        return;
    Node<T> *newNode = new Node(element);
    int counter = 0;
    for (Node<T> *curr = head, *pre = nullptr; curr; pre = curr, curr = curr->next)
    {
        counter++;
        if (counter == index)
        {
            link(newNode, curr);
            link(pre, newNode);
            length++;
            return;
        }
    }
}

template <typename T>
void LinkedList<T>::removeAtHead()
{
    if (!head)
        return;
    Node<T> *cur = head->next;
    delete_node(head);
    head = cur;
    if (head)
        head->prev = nullptr;
    else if (!length)
        tail = nullptr;
}

template <typename T>
void LinkedList<T>::removeAtTail()
{
    if (!head)
        return;
    Node<T> *cur = tail->prev;
    delete_node(tail);
    tail = cur;
    if (tail)
        tail->next = nullptr;
    else if (!length)
        head = nullptr;
}

template <typename T>
void LinkedList<T>::removeAt(int index)
{
    index--;
    if (!head || index < 0 || index >= length)
    {
        return;
    }
    if (!index)
    {
        removeAtHead();
        return;
    }
    Node<T> *prevcur = nullptr, *cur = head;
    for (int i = 0; i < index and cur != nullptr; i++)
    { // Loop to find the node
        prevcur = cur;
        cur = cur->next;
    }
    if (!cur)
    {
        return;
    }
    if (cur->next == nullptr)
    {
        removeAtTail();
        return;
    }
    prevcur->next = cur->next;
    if (cur->next)
        cur->next->prev = prevcur;
    delete_node(cur);
}

template <typename T>
T LinkedList<T>::retrieveAt(int index)
{
    index--;
    Node<T> *cur = head;
    for (int i = 0; i < length and cur; ++i, cur = cur->next)
    {
        if (i == index)
            return cur->data;
    }
}

template <typename T>
void LinkedList<T>::replaceAt(T newElement, int index)
{
    index--;
    Node<T> *cur = head;
    for (int i = 0; i < length and cur; ++i, cur = cur->next)
    {
        if (i == index)
        {
            cur->data = newElement;
            return;
        }
    }
}

template <typename T>
bool LinkedList<T>::isExist(T element)
{
    for (Node<T> *cur = head; cur; cur = cur->next)
    {
        if (element == cur->data)
            return true;
    }
    return false;
}

template <typename T>
bool LinkedList<T>::isItemAtEqual(T element, int index)
{
    index--;
    Node<T> *cur = head;
    for (int i = 0; i < length and cur; ++i, cur = cur->next)
    {
        if (i == index)
            return element == cur->data;
    }
}

template <typename T>
void LinkedList<T>::swap(int firstItemIdx, int secondItemIdx)
{
    if (head == nullptr || head->next == nullptr || firstItemIdx == secondItemIdx)
        return;
    int cnt = 0;
    firstItemIdx--;
    secondItemIdx--;
    Node<T> *cur = head;
    Node<T> *first = nullptr;
    Node<T> *second = nullptr;
    while (cur)
    {
        if (cnt++ == firstItemIdx)
            first = cur;
        cur = cur->next;
    }
    cnt = 0;
    cur = head;
    while (cur)
    {
        if (cnt++ == secondItemIdx)
            second = cur;
        cur = cur->next;
    }
    if (!first || !second)
        return;
    if (first == head)
        head = second;
    else if (second == head)
        head = first;
    if (first == tail)
        tail = second;
    else if (second == tail)
        tail = first;
    Node<T> *temp;
    temp = first->next;
    first->next = second->next;
    second->next = temp;
    if (first->next)
        first->next->prev = first;
    if (second->next)
        second->next->prev = second;
    temp = first->prev;
    first->prev = second->prev;
    second->prev = temp;
    if (first->prev)
        first->prev->next = first;
    if (second->prev)
        second->prev->next = second;
}

template <typename T>
bool LinkedList<T>::isEmpty()
{
    return !length || (head == nullptr and tail == nullptr);
}

template <typename T>
int LinkedList<T>::linkedListSize()
{
    return length;
}

template <typename T>
void LinkedList<T>::clear()
{
    while (head)
    {
        Node<T> *temp = head->next;
        delete_node(head);
        head = temp;
    }
    head = tail = nullptr;
}

template <typename T>
void LinkedList<T>::print()
{
    for (Node<T> *cur = head; cur; cur = cur->next)
        cout << cur->data << " ";
    cout << "\n";
}

int main()
{
    LinkedList<int> DLL;
    DLL.insertAtTail(2);
    DLL.insertAtTail(3);
    DLL.insertAtTail(4);
    DLL.insertAtTail(5);
    DLL.print();
    DLL.insertAtHead(1);
    DLL.print();
    cout << "Inserting element 6 at index 3 (1-based)\n";
    DLL.insertAt(6, 3);
    DLL.print();
    DLL.removeAtTail();
    DLL.removeAtHead();
    DLL.print();
    cout << "Removing element at index 2 (1-based)\n";
    DLL.removeAt(2);
    DLL.print();
    cout << DLL.isEmpty() << " " << DLL.isExist(6) << " " << DLL.linkedListSize() << "\n";
    cout << DLL.isItemAtEqual(4, 2) << "\n";
    cout << "Element at index 1 (1-based) is: " << DLL.retrieveAt(1) << "\n";
    cout << "Replacing element at index 1 (1-based) with 70:\n";
    DLL.replaceAt(70, 1);
    DLL.print();
    DLL.swap(1, 2);
    DLL.print();
    DLL.clear();
    DLL.print(); // List is empty, nothing is printed
    // must see this line, otherwise we have RTE
    cout << "\n\nNO RTE\n";
    return 0;
}