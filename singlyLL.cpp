#include <bits/stdc++.h>

using namespace std;

struct Node
{
    /* data */
    int data;
    Node *next = nullptr;
    Node(int data) : data(data) {}
};

class singlyLinkedList
{
private:
    Node *head{}, *tail{};
    int length;

public:
    /**
     * Prints the elements of linked list, even if empty
     * @param {void}
     * @returns {void}
     */
    void print()
    {
        for (Node *curr = head; curr; curr = curr->next)
            cout << curr->data << ' ';
        cout << '\n';
    }
    /**
     * Inserts an element to the front of the SLL.
     * @param {value} int : the element to be inserted
     * @returns {void}
     */
    void insertAtHead(int value)
    {
        Node *item = new Node(value);
        item->next = head;
        head = item;
        length++;
    }
    /**
     * Inserts an element to the end of the SLL.
     * @param {value} int : the element to be inserted
     * @returns {void}
     */
    void insertAtTail(int value)
    {
        Node *item = new Node(value);
        if (head == nullptr)
            head = tail = item;
        else
        {
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
    void insertAt(int value, int index)
    {
        if (index > length)
            return;

        int cntr = 0;
        for (Node *curr = head, *prev = nullptr; curr; prev = curr, curr = curr->next)
        {
            cntr++;
            if (cntr == index)
            {
                Node *item = new Node(value);
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
    void removeAtHead()
    {
        Node *dummy = head;
        head = head->next;
        delete dummy;
        length--;
    }
    /**
     * Removes last element
     * @param {void}
     * @returns {void}
     */
    void removeAtTail()
    {
        Node *prev = retrieveAt(length - 1);
        Node *dummy = tail;
        tail = prev;
        delete dummy;
        tail->next = nullptr;
    }
    /**
     * Removes element found at certain index
     * @param {index} int : index of element to be removed (1 based)
     * @returns {void}
     */
    void removeAt(int index)
    {
        if (index == 1)
            removeAtHead();
        else if (index == length)
            removeAtTail();
        else
        {
            Node *prev = retrieveAt(index - 1);
            Node *after = prev->next->next;
            Node *dummy = prev->next;
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
    Node *retrieveAt(int index)
    {
        if (index > length)
            return nullptr;
        int counter = 0;
        for (Node *current = head; current != nullptr; current = current->next)
        {
            if (++counter == index)
                return current;
        }
    }
    /**
     * Get the Node found at certain index
     * @param {value} int : new value to be replaced instead of old one
     * @param {index} int : position of node to replace its old value
     * @returns {void}
     */
    void replaceAt(int value, int index)
    {
        if (index > length)
            return;
        int cntr = 0;
        for (Node *curr = head; curr; curr = curr->next)
        {
            if (++cntr == index)
            {
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
    bool isExist(int value)
    {
        for (Node *curr = head; curr; curr = curr->next)
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
    bool isItemAtEqual(int element, int index)
    {
        if (index > length)
            return false;
        int cntr = 0;
        for (Node *curr = head; curr; curr = curr->next)
        {
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
    // Not yet
    void swap(int firstItemIdx, int secondItemIdx)
    {
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
    void clear()
    {
        // Iterate while head is not null
        while (head)
        {
            // Store the next node before deleting current
            Node *temp = head->next;
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
//     singlyLinkedList s;
//     s.insertAtTail(1);
//     s.insertAtTail(2);
//     s.insertAtTail(3);

//     s.insertAt(5, 2);
//     s.print();
//     s.removeAtHead();
//     s.print();
//     s.clear();
//     s.print();
// }