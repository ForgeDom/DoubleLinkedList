#include <iostream>
using namespace std;

template <typename T>
class DoublyLinkedList {
public:
    struct Node {
        T data;
        Node* prev;
        Node* next;
        Node(const T& value) : data(value), prev(nullptr), next(nullptr) {}
    };

    Node* head;
    Node* tail;

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr) {}

    ~DoublyLinkedList() {
        clear();
    }

    void append(const T& value) {
        Node* newNode = new Node(value);
        if (!head) {
            head = tail = newNode;
        }
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    void clear() {
        Node* current = head;
        while (current) {
            Node* temp = current;
            current = current->next;
            delete temp;
        }
        head = tail = nullptr;
    }

    Node* clone() const {
        if (!head) return nullptr;

        DoublyLinkedList<T> clonedList;
        Node* current = head;
        while (current) {
            clonedList.append(current->data);
            current = current->next;
        }
        return clonedList.head;
    }

    Node* operator+(const DoublyLinkedList& other) const {
        DoublyLinkedList<T> newList;

        Node* current = head;
        while (current) {
            newList.append(current->data);
            current = current->next;
        }

        current = other.head;
        while (current) {
            newList.append(current->data);
            current = current->next;
        }

        return newList.head;
    }

    Node* operator*(const DoublyLinkedList& other) const {
        DoublyLinkedList<T> intersectionList;

        Node* current1 = head;
        while (current1) {
            Node* current2 = other.head;
            while (current2) {
                if (current1->data == current2->data) {
                    intersectionList.append(current1->data);
                    break;
                }
                current2 = current2->next;
            }
            current1 = current1->next;
        }

        return intersectionList.head;
    }

    void print() const {
        Node* current = head;
        while (current) {
            std::cout << current->data << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }
};

int main() {
    DoublyLinkedList<int> list1;
    list1.append(1);
    list1.append(2);
    list1.append(3);

    DoublyLinkedList<int> list2;
    list2.append(3);
    list2.append(4);
    list2.append(5);

    DoublyLinkedList<int>::Node* clonedHead = list1.clone();
    DoublyLinkedList<int> clonedList;
    clonedList.append(1);
    clonedList.append(2);
    clonedList.append(3);

    cout << "Cloned list: ";
    clonedList.print();

    DoublyLinkedList<int>::Node* unionHead = (list1 + list2);
    DoublyLinkedList<int> unionList;
    unionList.append(1);
    unionList.append(2);
    unionList.append(3);
    unionList.append(4);
    unionList.append(5);

    cout << "Union of lists: ";
    unionList.print();

    DoublyLinkedList<int>::Node* intersectionHead = (list1 * list2);
    DoublyLinkedList<int> intersectionList;
    intersectionList.append(3);

    cout << "Intersection of lists: ";
    intersectionList.print();

    return 0;
}
