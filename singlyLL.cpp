#include <bits/stdc++.h>

using namespace std;

template<typename T>
struct Node {
    /* data */
    T data;
    Node *next = nullptr;

    Node(T data) : data(data) {}
};

template<typename T>
class singlyLinkedList {
private:
    Node<T> *head{}, *tail{};
    int length = 0;

public:
    /**
     * Prints the elements of linked list, even if empty
     * @param {void}
     * @returns {void}
     */
    void print() {
        cout << "Length: " << length << endl;
        for (Node<T> *curr = head; curr; curr = curr->next)
            cout << curr->data << ' ';
        cout << '\n';
    }

    /**
     * Inserts an element to the front of the SLL.
     * @param {value} int : the element to be inserted
     * @returns {void}
     */
    void insertAtHead(T value) {
        Node<T> *item = new Node(value);
        item->next = head;
        head = item;
        length++;
    }

    /**
     * Inserts an element to the end of the SLL.
     * @param {value} int : the element to be inserted
     * @returns {void}
     */
    void insertAtTail(T value) {
        Node<T> *item = new Node(value);
        if (head == nullptr)
            head = tail = item;
        else {
            tail->next = item;
            tail = item;
        }
        length++;
    }

    /**
     * Inserts an element in the index
     * @param {value} int : the element to be inserted
     * @param {index} int : the position of the element to be inserted (1 based)
     * @returns {void}
     */
    void insertAt(T value, int index) {
        if (index == length + 1) {
            insertAtTail(value);
            return;
        }
        if (index == 1) {
            insertAtHead(value);
            return;
        }
        if (index > length)
            return;

        int cntr = 0;
        for (Node<T> *curr = head, *prev = nullptr; curr; prev = curr, curr = curr->next) {
            cntr++;
            if (cntr == index) {
                Node<T> *item = new Node(value);
                prev->next = item, item->next = curr;
                length++;
                return;
            }
        }
    }

    /**
     * Removes first element
     * @param {void}
     * @returns {void}
     */
    void removeAtHead() {
        Node<T> *dummy = head;
        head = head->next;
        delete dummy;
        length--;
    }

    /**
     * Removes last element
     * @param {void}
     * @returns {void}
     */
    void removeAtTail() {
        Node<T> *prev = retrieveAt(length - 1);
        Node<T> *dummy = tail;
        tail = prev;
        delete dummy;
        tail->next = nullptr;
        length--;
    }

    /**
     * Removes element found at certain index
     * @param {index} int : index of element to be removed (1 based)
     * @returns {void}
     */
    void removeAt(int index) {
        if (index == 1)
            removeAtHead();
        else if (index == length)
            removeAtTail();
        else {
            Node<T> *prev = retrieveAt(index - 1);
            Node<T> *after = prev->next->next;
            Node<T> *dummy = prev->next;
            prev->next = after;
            delete dummy;
        }
    }

    /**
     * Get the Node found at certain index
     * @param {index} int : position of node to be returned
     * @returns {*Node} the node found at position index
     * @returns {nullptr} if index > length
     */
    Node<T> *retrieveAt(int index) {
        if (index > length)
            return nullptr;
        int counter = 0;
        for (Node<T> *current = head; current != nullptr; current = current->next) {
            if (++counter == index)
                return current;
        }
        return nullptr;
    }

    /**
     * Get the Node found at certain index
     * @param {value} int : new value to be replaced instead of old one
     * @param {index} int : position of node to replace its old value
     * @returns {void}
     */
    void replaceAt(T value, int index) {
        if (index > length)
            return;
        int cntr = 0;
        for (Node<T> *curr = head; curr; curr = curr->next) {
            if (++cntr == index) {
                curr->data = value;
                return;
            }
        }
    }

    /**
     * Checks if a value is found inside the list or not
     * @param {value} int : value to search for
     * @returns {bool} true if element found, false otherwise
     */
    bool isExist(T value) {
        for (Node<T> *curr = head; curr; curr = curr->next)
            if (curr->data == value)
                return true;
        return false;
    }

    /**
     * Checks if node found at certain index has a certain value or not
     * @param {element} int : value to search for
     * @param {index} int : index of node to look at
     * @returns {bool} true if element found, false otherwise
     */
    bool isItemAtEqual(T element, int index) {
        if (index > length)
            return false;
        int cntr = 0;
        for (Node<T> *curr = head; curr; curr = curr->next) {
            if (++cntr == index)
                if (curr->data == element)
                    return true;
        }
        return false;
    }

    /**
     * Swaps two nodes without swapping data
     * @param {firstItemIdx} int : index of first node (1 based)
     * @param {secondItemIdx} int : index of second node (1 based)
     * @returns {void}
     */
    void swap(int firstItemIdx, int secondItemIdx) {
        if (head == nullptr || head->next == nullptr || firstItemIdx == secondItemIdx ||
            firstItemIdx > length || secondItemIdx > length || firstItemIdx < 0 || secondItemIdx < 0)
            return;
        int cnt = 0;
        Node<T> *cur = head;
        Node<T> *prevFirst = nullptr, *prevSecond = nullptr;
        Node<T> *first = nullptr;
        Node<T> *second = nullptr;
        while (cur) {
            if (++cnt == firstItemIdx)
                first = cur;
            prevFirst = first, cur = cur->next;
        }
        cnt = 0;
        cur = head;
        while (cur) {
            if (++cnt == secondItemIdx)
                second = cur;
            prevSecond = second, cur = cur->next;
        }
        if (!first || !second)
            return;
        // If first node to be swapped is not the head
        if (prevFirst)
            prevFirst->next = second;
        else         //if it is the head
            head = second;
        // If second node to be swapped is not the head
        if (prevSecond)
            prevSecond->next = first;
        else         //if it is the head
            head = first;
        Node<T> *temp = second->next;
        second->next = first->next;
        first->next = temp;
    }

    /**
     * Checks if linked list is empty
     * @param {void}
     * @returns {bool} true if empty, false otherwise
     */
    bool isEmpty() { return (length == 0) ? true : false; }

    /**
     * returns size of linked list
     * @param {void}
     * @returns {int} size
     */
    int linkedListSize() { return length; }

    /**
     * removes all elements
     * @param {void}
     * @returns {void}
     */
    void clear() {
        // Iterate while head is not null
        while (head) {
            // Store the next node before deleting current
            Node<T> *temp = head->next;
            // Delete the current node
            delete head;
            // Move head to the next node
            head = temp;
        }
        // Set head to null to indicate an empty list
        head = nullptr;
    }
};

// int main()
// {
//     singlyLinkedList<int> s;
//     s.insertAtTail(2);
//     s.insertAtTail(3);
//     s.insertAtTail(4);
//     s.insertAtHead(1);
//     s.insertAt(5, 5);
//     s.print();

//     s.removeAtHead();
//     s.removeAtTail();
//     s.print();

//     s.removeAt(1);
//     s.print();

//     cout << "Element at index 1 is: " << s.retrieveAt(1)->data << endl;

//     s.replaceAt(6, 1);
//     s.print();

//     cout << s.isExist(4) << " " << s.isExist(56) << endl;

//     cout << s.isItemAtEqual(6, 1) << endl;

//     cout << s.isEmpty() << endl;

// }
