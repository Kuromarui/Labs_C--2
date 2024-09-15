#include <iostream>
#include <fstream>
#include <exception>

using namespace std;

// Базовый класс
class Queue {
public:
    Queue() { cout << "Конструктор Queue без параметров" << endl; }
    Queue(const Queue& other) { cout << "Конструктор Queue копирования" << endl; }
    virtual ~Queue() { cout << "Деструктор Queue" << endl; }

    virtual void print() const = 0;
    virtual void set(int value) = 0;
    virtual int get() const = 0;
    virtual int push_forward(int value) = 0;
    virtual int push_back(int value) = 0;
    virtual int pop_forward()  = 0;
    virtual int pop_back()  = 0;
};

// Класс Очередь
class ListQueue : public Queue {
public:
    ListQueue() { 
        head = nullptr;
        tail =nullptr ;
    }

    ListQueue(const ListQueue& other) : Queue(other) {
        cout << "Конструктор ListQueue копирования" << endl;
        if (other.head) {
            head = new Node(other.head->value);
            Node* current = head;
            for (Node* otherNode = other.head->next; otherNode; otherNode = otherNode->next) {
                current->next = new Node(otherNode->value);
                current = current->next;
            }
            tail = current;
        }
    }

    ~ListQueue() {
        cout << "Деструктор ListQueue" << endl;
        while (head) {
            Node* next = head->next;
            delete head;
            head = next;
        }
    }

    void print() const override {
        for (Node* current = head; current; current = current->next) {
            cout << current->value << " ";
        }
        cout << endl;
    }

    void set(int value) override {
        if (head) {
            head->value = value;
        }
    }

    int get() const override {
        if (head) {
            return head->value;
        }
        return -1;
    }

    int push_forward(int value) override {
        Node* newNode = new Node(value);
        if (!head) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
        return 0;
    }

    int pop_forward() override {
        if (head) {
            int value = head->value;
            Node* next = head->next;
            delete head;
            head = next;
            if (!head) {
                tail = nullptr;
            }
            return value;
        }
        return -1;
    }



private:
    struct Node {
        int value;
        Node* next;

        Node(int value) : value(value), next(nullptr) {}
    };

    Node* head;
    Node* tail;
};

class StackQueue : public Queue {
public:
    StackQueue() : top(nullptr) { cout << "Конструктор StackQueue без параметров" << endl; }
    StackQueue(const StackQueue& other) : Queue(other) {
        cout << "Конструктор StackQueue копирования" << endl;
        if (other.top) {
            top = new Node(other.top->value);
            Node* current = top;
            for (Node* otherNode = other.top->next; otherNode; otherNode = otherNode->next) {
                current->next = new Node(otherNode->value);
                current = current->next;
            }
        }
    }
    ~StackQueue() {
        cout << "Деструктор StackQueue" << endl;
        while (top) {
            Node* next = top->next;
            delete top;
            top = next;
        }
    }

    void print() const override {
        for (Node* current = top; current; current = current->next) {
            cout << current->value << " ";
        }
        cout << endl;
    }

    void set(int value) override {
        if (top) {
            top->value = value;
        }
    }

    int get() const override {
        if (top) {
            return top->value;
        }
        return -1;
    }

    int push_forward(int value) override {
        Node* newNode = new Node(value);
        newNode->next = top;
        top = newNode;
        return 0;
    }

    int pop_forward() override {
        if (top) {
            int value = top->value;
            Node* next = top->next;
            delete top;
            top = next;
            return value;
        }
        return -1;
    }

private:
    struct Node {
        int value;
        Node* next;

        Node(int value) : value(value), next(nullptr) {}
    };

    Node* top;
};


// Класс Дека
class DequeQueue : public Queue {
public:
    DequeQueue() : head(nullptr), tail(nullptr) { cout << "Конструктор DequeQueue без параметров" << endl; }
    DequeQueue(const DequeQueue& other) : Queue(other) {
        cout << "Конструктор DequeQueue копирования" << endl;
        if (other.head) {
            head = new Node(other.head->value);
            Node* current = head;
            for (Node* otherNode = other.head->next; otherNode; otherNode = otherNode->next) {
                current->next = new Node(otherNode->value);
                current = current->next;
            }
            tail = current;
        }
    }
    ~DequeQueue() {
        cout << "Деструктор DequeQueue" << endl;
        while (head) {
            Node* next = head->next;
            delete head;
            head = next;
        }
    }

    void print() const override {
        for (Node* current = head; current; current = current->next) {
            cout << current->value << " ";
        }
        cout << endl;
    }

    void set(int value) override {
        if (head) {
            head->value = value;
        }
    }

    int get() const override {
        if (head) {
            return head->value;
        }
        return -1;
    }

    int push_forward(int value) override {
        Node* newNode = new Node(value);
        if (!head) {
            head = newNode;
            tail = newNode;
        } else {
            newNode->next = head;
            head = newNode;
        }
        return 0;
    }

    int push_back(int value) override {
        Node* newNode = new Node(value);
        if (!head) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
        return 0;
    }

    int pop_forward() override {
        if (head) {
            int value = head->value;
            Node* next = head->next;
            delete head;
            head = next;
            if (!head) {
                tail = nullptr;
            }
            return value;
        }
        return -1;
    }

    int pop_back() override {
        if (tail) {
            int value = tail->value;
            Node* current = head;
            while (current->next != tail) {
                current = current->next;
            }
            delete tail;
            tail = current;
            if (!head) {
                tail = nullptr;
            }
            return value;
        }
        return -1;
    }

private:
    struct Node {
        int value;
        Node* next;

        Node(int value) : value(value), next(nullptr) {}
    };

    Node* head;
    Node* tail;
};

class Keeper {
public:
    Keeper() { cout << "Конструктор Keeper без параметров" << endl; }
    Keeper(const Keeper& other) { cout << "Конструктор Keeper копирования" << endl; }
    ~Keeper() { cout << "Деструктор Keeper" << endl; }

    void add(Queue* queue) {
        queues[num_queues++] = queue;
    }

    void remove(Queue* queue) {
        for (int i = 0; i < num_queues; ++i) {
            if (queues[i] == queue) {
                for (int j = i; j < num_queues - 1; ++j) {
                    queues[j] = queues[j + 1];
                }
                num_queues--;
                return;
            }
        }
    }

    void save(const string& filename) {
        ofstream out(filename);
        if (!out.is_open()) {
            throw runtime_error("Не удалось открыть файл для записи");
        }
        for (int i = 0; i < num_queues; ++i) {
            out << queues[i]->get() << " ";
        }
        out << endl;
    }

    void load(const string& filename) {
        ifstream in(filename);
        if (!in.is_open()) {
            throw runtime_error("Не удалось открыть файл для чтения");
        }
        int value;
        while (in >> value) {
            Queue* queue = new Queue();
            queue->set(value);
            queues[num_queues++] = queue;
        }
    }

private:
    Queue* queues[100];
    int num_queues = 0;
};


int main() {
    Keeper keeper;

    ListQueue* listQueue = new ListQueue();
    listQueue->push_forward(1);
    listQueue->push_forward(2);
    listQueue->push_forward(3);
    keeper.add(listQueue);

    StackQueue* stackQueue = new StackQueue();
    stackQueue->push_forward(4);
    stackQueue->push_forward(5);
    stackQueue->push_forward(6);
    keeper.add(stackQueue);

    DequeQueue* dequeQueue = new DequeQueue();
    dequeQueue->push_forward(7);
    dequeQueue->push_forward(8);
    dequeQueue->push_forward(9);
    keeper.add(dequeQueue);

    keeper.save("queues.txt");

    keeper.remove(listQueue);
    delete listQueue;

    keeper.load("queues.txt");

    for (auto queue : keeper.queues) {
        queue->print();
    }

    return 0;
}