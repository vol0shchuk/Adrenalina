#include <iostream>
using namespace std;

template <typename T>
class PriorityQueue {
private:
    struct Node {
        T data;
        int priority;
        Node* next;
    };

    Node* front;
    Node* rear;
    int count;

public:
    PriorityQueue() : front(nullptr), rear(nullptr), count(0) {}

    ~PriorityQueue() {
        clear();
    }

    PriorityQueue(const PriorityQueue& other) {
        front = nullptr;
        rear = nullptr;
        count = 0;
        Node* temp = other.front;
        while (temp != nullptr) {
            enqueue(temp->data, temp->priority);
            temp = temp->next;
        }
    }

    void enqueue(const T& value, int priority) {
        Node* newNode = new Node{ value, priority, nullptr };
        if (isEmpty()) {
            front = newNode;
            rear = newNode;
        }
        else if (priority > front->priority) {
            newNode->next = front;
            front = newNode;
        }
        else {
            Node* current = front;
            while (current->next != nullptr && current->next->priority >= priority) {
                current = current->next;
            }
            newNode->next = current->next;
            current->next = newNode;
            if (newNode->next == nullptr) {
                rear = newNode;
            }
        }
        count++;
    }

    void dequeue() {
        if (isEmpty()) {
            cout << "Queue is empty. Cannot dequeue.\n";
            return;
        }
        Node* temp = front;
        front = front->next;
        delete temp;
        count--;
    }

    const T& frontElement() const {
        if (isEmpty()) {
            throw runtime_error("Queue is empty.");
        }
        return front->data;
    }

    const T& rearElement() const {
        if (isEmpty()) {
            throw runtime_error("Queue is empty.");
        }
        return rear->data;
    }

    bool isEmpty() const {
        return count == 0;
    }

    int size() const {
        return count;
    }

    void clear() {
        while (!isEmpty()) {
            dequeue();
        }
    }

    bool operator<(const PriorityQueue& other) const {
        return frontElement() < other.frontElement();
    }

    bool operator>(const PriorityQueue& other) const {
        return frontElement() > other.frontElement();
    }

    bool operator==(const PriorityQueue& other) const {
        return frontElement() == other.frontElement();
    }

    PriorityQueue& operator=(const PriorityQueue& other) {
        if (this != &other) {
            clear();
            Node* temp = other.front;
            while (temp != nullptr) {
                enqueue(temp->data, temp->priority);
                temp = temp->next;
            }
        }
        return *this;
    }
};

int main() {
    PriorityQueue<int> pq;
    pq.enqueue(5, 2);
    pq.enqueue(10, 1);
    pq.enqueue(3, 3);
    pq.enqueue(7, 2);

    cout << "Size of pq: " << pq.size() << endl;
    cout << "Front element of pq: " << pq.frontElement() << endl;
    cout << "Rear element of pq: " << pq.rearElement() << endl;

    pq.dequeue();
    cout << "After dequeue, Front element of pq: " << pq.frontElement() << endl;

    PriorityQueue<int> pq2 = pq;
    cout << "pq2 front element: " << pq2.frontElement() << endl;
}
