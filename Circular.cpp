#include <iostream>
            
using namespace std;

template <typename T>
struct Node {
    T data;
    Node<T> *next {};
    Node(T data) : data(data){}
    ~Node(){
        cout<<"Destroy value: "<<data<<" at address "<<this<<endl;
    }
};

template <typename T>
class CircularLinkedList {
private:
    Node<T> *head { };
    Node<T> *tail { };
    int length = 0;

public:

    //Inserts an element to the front of the CLL.
    void insertAtHead(T val) {		// O(1) time - O(1) memory
        Node<T> *newNode = new Node(val);
        if(!head) {                      // Handle empty list case
            head = tail = newNode;
            head->next = tail->next = newNode;
        }
        else {
            newNode->next = head;
            tail->next = newNode;
            head = newNode;
        }
        length++;
    }
    // Inserts an element to the end of the CLL.
    void insertAtTail(T val)
    {
        Node<T> *newNode = new Node(val);
        if(!head) {                      // Handle empty list case
            head = tail = newNode;
            head->next = tail->next = newNode;
        }
        else {
            newNode->next = head;
            tail->next = newNode;
        }
        tail = newNode;
        tail->next = head;
        length++;
    }
    // Insert at specific index
    void insertAt(T val, int idx) {
        if (idx < 1 || idx > length) {
            cout << "Invalid index" << endl;
            return;
        }
        if (idx == 1) {
            insertAtHead(val);
            return;
        }
        if(idx == length + 1){
            insertAtTail(val);
            return;
        }
        Node<T> *newNode = new Node(val);
        Node<T> *cur = head;
        int cnt = 0;
        while(cur->next != head && cnt < idx - 2){
            cur = cur->next;
            cnt++;
        }
        newNode->next = cur->next;
        cur->next = newNode;
        length++;
    }

    // Remove from head
    void removeAtHead() {
        if (!head) {
            cout << "List is empty" << endl;
            return;
        }
        Node<T> *cur = head;
        if (head->next == head) { // Handle single node case
            head = nullptr;
        } else {
            head = head->next;
            tail->next = head;
        }
        delete cur;
        length--;
    }

    // Remove from tail
    void removeAtTail() {
        if (!head) {
            cout << "List is empty" << endl;
            return;
        }
        if (head->next == head) { // Handle single node case
            delete head;
            head = nullptr;
        } else {
            Node<T> *cur = head;
            while (cur->next->next != head) {
                cur = cur->next;
            }
            delete cur->next;
            tail = cur;
            tail->next = head;
        }
        length--;
    }

    // Remove from specific idx
    void removeAt(int idx) {
        if (idx < 1 || idx > length) {
            cout << "Invalid index" << endl;
            return;
        }
        if (idx == 1) {
            removeAtHead();
            return;
        }
        if (idx == length) {
            removeAtTail();
            return;
        }
        Node<T> *cur = head;
        int cnt = 0;
        while (cur->next != head && cnt < idx - 2) {
            cur = cur->next;
            cnt++;
        }
        Node<T> *deleteNode = cur->next;
        cur->next = deleteNode->next;
        delete deleteNode;
        length--;
    }

    // Retrieve element at idx
    int retrieveAt(int idx) {
        if (idx < 1 || idx > length) {
            cout << "Invalid index" << endl;
            return -1;
        }
        Node<T> *cur = head;
        int cnt = 1; // Start counting from 1 as index starts from 1
        while (cnt < idx) {
            cur = cur->next;
            cnt++;
        }
        return cur->data; // Return the data of the node at the given index
    }


    void replaceAt(T val, int idx)
    {
        if (idx < 1 || idx > length) {
            cout << "Invalid index" << endl;
            return;
        }
        int cnt = 1;    // Start counting from 1 as index starts from 1
        for (Node<T> *cur = head; cnt <= idx; cur = cur->next)
        {
            if (cnt++ == idx)
            {
                cur->data = val;
                return;
            }
        }
    }

    bool isExist(T val) {
        if (!head) return false; // If the list is empty, the val doesn't exist

        Node<T> *cur = head;
        do {
            if (cur->data == val)
                return true; // If the current node's data equals the val, return true
            cur = cur->next;
        } while (cur != head);

        return false; // If the loop completes without finding the val, return false
    }


    bool isItemAtEqual(T val, int idx)
    {
        if (idx < 1 || idx > length + 1) {
            cout << "Invalid index" << endl;
            return false;
        }
        int cnt = 1;
        for (Node<T> *cur = head; cnt <= idx; cur = cur->next)
        {
            if (cnt++ == idx)
                if (cur->data == val)
                    return true;
        }
        return false;
    }

    // swap two nodes without swapping data.
    void swap(int firstItemIdx, int secondItemIdx) {
        if (firstItemIdx == secondItemIdx) {
            return; // No need to swap if indices are the same
        }

        if (firstItemIdx < 1 || firstItemIdx > length + 1 || secondItemIdx < 1 || secondItemIdx > length + 1) {
            cout << "Invalid index" << endl;
            return;
        }

        Node<T> *first = nullptr, *second = nullptr; // Nodes to be swapped
        Node<T> *prev1 = nullptr, *prev2 = nullptr; // Previous nodes of the nodes to be swapped

        Node<T> *prev = nullptr, *cur = head;
        int idx = 1;
        while (idx != length + 1 && (!first || !second)) {
            if (idx == firstItemIdx) {
                first = cur;
                prev1 = prev;
            }
            else if (idx == secondItemIdx) {
                second = cur;
                prev2 = prev;
            }
            prev = cur;
            cur = cur->next;
            idx++;
        }

        if (prev1) {
            prev1->next = second;
        } else {
            head = second; // Update head if first is the head
            tail->next = head; // Update tail's next pointer
        }

        if (prev2) {
            prev2->next = first;
        } else {
            head = first; // Update head if second is the head
            tail->next = head; // Update tail's next pointer
        }

        Node<T> *temp = first->next;
        first->next = second->next;
        second->next = temp;

        int val = first->data;
        first->data = second->data;
        second->data = val;
    }


    bool isEmpty(){
        return head == nullptr;
    }

    int linkedListSize(){
        return length;
    }

    void clear() {
        if (!head) return; // If the list is empty, there's nothing to clear

        Node<T> *cur = head;
        do {
            Node<T> *nextNode = cur->next;
            delete cur;
            cur = nextNode;
        } while (cur != head);

        head = nullptr;
        length = 0;
    }

    void print() {
        if (!head) {  // If the list is empty, there's nothing to print
            cout<<"List is empty.\n";
            return;
        }

        Node<T> *cur = head;
//        cout<<"head: "<<head->data<<endl;
        do {
            cout << cur->data << ' ' << cur << ' ';
            cur = cur->next;
        } while (cur != head);

        cout << endl;
//        cout<<"tail: "<<tail->data<<endl;
    }

};
int main()
{
    CircularLinkedList<int> DLL;
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
