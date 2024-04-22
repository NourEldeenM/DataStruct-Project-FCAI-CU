#include "bits/stdc++.h"

using namespace std;

template<typename T>
struct Node {
    T data{};
    Node *next{};
    Node *prev{};     // Previous node!

    Node(T data) : data(data) {}

    void set(Node *next, Node *prev) {
        this->next = next;
        this->prev = prev;
    }

    ~Node() {
        cout << "Destroy value: " << data << " at address " << this << "\n";
    }
};

template<typename T>
class LinkedList {
private:
    Node<T> *head{};
    Node<T> *tail{};
    int length = 0; // counter to count how many nodes

public:
//    // Below 2 deletes prevent copy and assign to avoid this mistake
//    LinkedList() {
//    }
//
//    LinkedList(const LinkedList &) = delete;
//
//    LinkedList &operator=(const LinkedList &another) = delete;




    void insertAtHead(T element);

    void insertAtTail(T element);

    void insertAt(T element, int index);

    void removeAtHead();

    void removeAtTail();

    void removeAt(int index);

    T retrieveAt(int index);

    void replaceAt(T newElement, int index);   //check if void or not
    bool isExist(T element);

    bool isItemAtEqual(T element, int index);

    void swap(int firstItemIdx, int secondItemIdx);    // swap two nodes without swapping data.
    bool isEmpty();

    int linkedListSize();

    void clear();

    void print();

    void link(Node<T> *first, Node<T> *second) {
        if (first)
            first->next = second;
        if (second)
            second->prev = first;
    }

    void embed_after(Node<T> *node_before, T value) {
        // Add a node with value between node and its next
        Node<T> *middle = new Node(value);
        ++length;
        Node<T> *node_after = node_before->next;
        link(node_before, middle);
        link(middle, node_after);
    }

    void delete_node(Node<T> *node) {
        delete node;
        length--;
    }
};

template<typename T>
void LinkedList<T>::insertAtHead(T element) {
    Node<T> *newNode = new Node(element);
    if (!head)
        head = tail = newNode;
    else {
        link(newNode, head);
        head = newNode;
    }
    length++;
}

template<typename T>
void LinkedList<T>::insertAtTail(T element) {
    Node<T> *newNode = new Node(element);
    if (!head)
        head = tail = newNode;
    else {
        link(tail, newNode);
        tail = newNode;
    }
    length++;
}

template<typename T>
void LinkedList<T>::insertAt(T element, int index) {
    Node<T> *newNode = new Node(element);
    if (index == 0 || !head) {
        insertAtHead(newNode);
        return;
    }
    Node<T> *pre = head;
    //Loop to find the node before the index
    for (int i = 0; i < index - 1 and pre != nullptr; i++)
        pre = pre->next;
    if (!pre) {
        delete newNode;
        return;
    }
    link(newNode, pre->next);
    link(pre, newNode);
    length++;
}

template<typename T>
void LinkedList<T>::removeAtHead() {
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

template<typename T>
void LinkedList<T>::removeAtTail() {
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

template<typename T>
void LinkedList<T>::removeAt(int index) {
    if (!head || index < 0 || index >= length) {
        return;
    }
    if (!index) {
        removeAtHead();
        return;
    }
    Node<T> *prevcur = nullptr, *cur = head;
    for (int i = 0; i < index and cur != nullptr; i++) {        //Loop to find the node
        prevcur = cur;
        cur = cur->next;
    }
    if (!cur) {
        return;
    }
    if (cur->next == nullptr)
        removeAtTail();
    prevcur->next = cur->next;
    cur->next->prev = prevcur;          //no need to check if null since checked in previous condition
    delete_node(cur);
}

template<typename T>
T LinkedList<T>::retrieveAt(int index) {
    Node<T> *cur = head;
    for (int i = 0; i < length and cur; ++i, cur = cur->next) {
        if (i == index)
            return cur->data;
    }
}

template<typename T>
void LinkedList<T>::replaceAt(T newElement, int index) {        //check if void or not
    Node<T> *cur = head;
    for (int i = 0; i < length and cur; ++i, cur = cur->next) {
        if (i == index) {
            cur->data = newElement;
            return;
        }
    }
}

template<typename T>
bool LinkedList<T>::isExist(T element) {
    for (Node<T> *cur = head; cur; cur = cur->next) {
        if (element == cur->data)
            return true;
    }
    return false;
}

template<typename T>
bool LinkedList<T>::isItemAtEqual(T element, int index) {
    Node<T> *cur = head;
    for (int i = 0; i < length and cur; ++i, cur = cur->next) {
        if (i == index)
            return element == cur->data;
    }
}

template<typename T>
void LinkedList<T>::swap(int firstItemIdx, int secondItemIdx) {         // swap two nodes without swapping data.
    if (firstItemIdx == secondItemIdx || (!firstItemIdx and !secondItemIdx) ||
        (firstItemIdx > length - 1 and secondItemIdx > length - 1) || !head || head->next == nullptr)
        return;
    Node<T> *first = nullptr, *second = nullptr;
    Node<T> *cur = head;
    int itr = 0;
    while (*cur) {
        if (itr++ == firstItemIdx)
            first = cur;
        if (itr++ == secondItemIdx)
            second = cur;
        cur = cur->next;
    }
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

template<typename T>
bool LinkedList<T>::isEmpty() {
    return !length || (head == nullptr and tail == nullptr);
}

template<typename T>
int LinkedList<T>::linkedListSize() {
    return length;
}

template<typename T>
void LinkedList<T>::clear() {
    Node<T> *cur = head;
    while (cur) {
        Node<T> *temp = cur;
        cur = cur->next;
        delete_node(temp);
    }
    head = tail = nullptr;
}

template<typename T>
void LinkedList<T>::print() {
    for (Node<T> *cur = head; cur; cur = cur->next)
        cout << cur->data << " ";
    cout << "\n";
}


int main() {
    // must see it, otherwise RTE
    cout << "\n\nNO RTE\n";

    return 0;
}

