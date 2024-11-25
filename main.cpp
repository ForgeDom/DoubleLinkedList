#include <iostream>
#include <stdexcept>

using namespace std;

template <typename T>
class Array {
private:
    struct Node {
        T data;
        Node* next;
        Node* prev;

        Node(const T& data) : data(data), next(nullptr), prev(nullptr) {}
    };

    Node* head;
    Node* tail;
    int size;
    int capacity;
    int grow;

public:
    Array(int initialSize = 0, int grow = 1) : head(nullptr), tail(nullptr), size(0), capacity(initialSize), grow(grow) {
        if (initialSize > 0) {
            for (int i = 0; i < initialSize; ++i) {
                Add(T());
            }
        }
    }

    Array(const Array<T>& other) : head(nullptr), tail(nullptr), size(0), capacity(other.capacity), grow(other.grow) {
        Node* current = other.head;
        while (current) {
            Add(current->data);
            current = current->next;
        }
    }

    Array<T>& operator=(const Array<T>& other) {
        if (this != &other) {
            RemoveAll();
            Node* current = other.head;
            while (current) {
                Add(current->data);
                current = current->next;
            }
            capacity = other.capacity;
            grow = other.grow;
        }
        return *this;
    }

    ~Array() {
        RemoveAll();
    }

    int GetSize() const {
        return size;
    }

    void SetSize(int newSize, int grow = 1) {
        if (newSize > size) {
            this->grow = grow;
            while (size < newSize) {
                Add(T());
            }
        }
        else {
            while (size > newSize) {
                RemoveAt(size - 1);
            }
        }
    }

    int GetUpperBound() const {
        return size - 1;
    }

    bool IsEmpty() const {
        return size == 0;
    }

    void FreeExtra() {
        SetSize(size);
    }

    void RemoveAll() {
        Node* current = head;
        while (current) {
            Node* nextNode = current->next;
            delete current;
            current = nextNode;
        }
        head = tail = nullptr;
        size = 0;
    }

    T GetAt(int index) const {
        if (index < 0 || index >= size) {
            throw out_of_range("Index out of range");
        }

        Node* current = head;
        for (int i = 0; i < index; ++i) {
            current = current->next;
        }
        return current->data;
    }

    void SetAt(int index, const T& value) {
        if (index < 0 || index >= size) {
            throw out_of_range("Index out of range");
        }

        Node* current = head;
        for (int i = 0; i < index; ++i) {
            current = current->next;
        }
        current->data = value;
    }

    T& operator[](int index) {
        if (index < 0 || index >= size) {
            throw out_of_range("Index out of range");
        }

        Node* current = head;
        for (int i = 0; i < index; ++i) {
            current = current->next;
        }
        return current->data;
    }

    void Add(const T& value) {
        Node* newNode = new Node(value);
        if (tail) {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        else {
            head = tail = newNode;
        }
        ++size;
        if (size > capacity) {
            capacity += grow;
        }
    }

    void Append(const Array<T>& other) {
        for (int i = 0; i < other.GetSize(); ++i) {
            Add(other.GetAt(i));
        }
    }

    T* GetData() const {
        T* data = new T[size];
        Node* current = head;
        for (int i = 0; i < size; ++i) {
            data[i] = current->data;
            current = current->next;
        }
        return data;
    }

    void InsertAt(int index, const T& value) {
        if (index < 0 || index > size) {
            throw out_of_range("Index out of range");
        }

        if (index == size) {
            Add(value);
        }
        else {
            Node* current = head;
            for (int i = 0; i < index; ++i) {
                current = current->next;
            }

            Node* newNode = new Node(value);
            newNode->next = current;
            newNode->prev = current->prev;

            if (current->prev) {
                current->prev->next = newNode;
            }
            else {
                head = newNode;
            }
            current->prev = newNode;
            ++size;
        }
    }

    void RemoveAt(int index) {
        if (index < 0 || index >= size) {
            throw out_of_range("Index out of range");
        }

        Node* current = head;
        for (int i = 0; i < index; ++i) {
            current = current->next;
        }

        if (current->prev) {
            current->prev->next = current->next;
        }
        else {
            head = current->next;
        }

        if (current->next) {
            current->next->prev = current->prev;
        }
        else {
            tail = current->prev;
        }

        delete current;
        --size;
    }
};

int main() {
    Array<int> arr;
    arr.Add(10);
    arr.Add(20);
    arr.Add(30);

    cout << "Element at index 1: " << arr.GetAt(1) << endl;

    arr.SetAt(1, 50);
    cout << "Element at index 1 after modification: " << arr[1] << endl;

    cout << "Array size: " << arr.GetSize() << endl;
    cout << "Array upper bound: " << arr.GetUpperBound() << endl;

    arr.RemoveAt(1);
    cout << "Array size after removal: " << arr.GetSize() << endl;

    Array<int> arr2;
    arr2.Add(100);
    arr2.Add(200);

    arr.Append(arr2);
    cout << "Array size after append: " << arr.GetSize() << endl;

    return 0;
}
