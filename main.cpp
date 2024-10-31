#include <iostream>
#include <stdexcept>
using namespace std;

template <typename T>
class Queue {
private:
    struct Node {
        T data;
        Node* prev;
        Node* next;

        Node(const T& value) : data(value), prev(nullptr), next(nullptr) {}
    };

    Node* front;
    Node* back;
    size_t size;

public:
    Queue() : front(nullptr), back(nullptr), size(0) {}

    ~Queue() {
        while (!isEmpty()) {
            dequeue();
        }
    }

    void enqueue(const T& value) {
        Node* newNode = new Node(value);
        if (isEmpty()) {
            front = back = newNode;
        }
        else {
            back->next = newNode;
            newNode->prev = back;
            back = newNode;
        }
        ++size;
    }

    void dequeue() {
        if (isEmpty()) {
            throw std::out_of_range("Queue is empty");
        }
        Node* temp = front;
        front = front->next;
        if (front) {
            front->prev = nullptr;
        }
        else {
            back = nullptr;
        }
        delete temp;
        --size;
    }

    T& peek() const {
        if (isEmpty()) {
            throw std::out_of_range("Queue is empty");
        }
        return front->data;
    }

    bool isEmpty() const {
        return size == 0;
    }

    size_t getSize() const {
        return size;
    }
};

int main() {
    Queue<int> q;
    q.enqueue(1);
    q.enqueue(2);
    q.enqueue(3);

    cout << "Front element: " << q.peek() << endl;
    q.dequeue();
    cout << "Front element after dequeue: " << q.peek() << endl;

    while (!q.isEmpty()) {
        cout << "Dequeue: " << q.peek() << endl;
        q.dequeue();
    }

    return 0;
}
