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
    virtual void print_in_file() const = 0;
    virtual void set(int value) = 0;
    virtual int get() const = 0;
    virtual int push_forward(int value) = 0;
    virtual int push_back(int value) = 0;
    virtual int pop_forward()  = 0;
    virtual int pop_back()  = 0;

protected: 
    struct Node {
        int value;
        Node* next;

        Node(int value) : value(value), next(nullptr) {}
    };
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

    void print_in_file() const override {
        ofstream out("Lists.txt");
        if (!out.is_open()) {
            throw runtime_error("Не удалось открыть файл для записи");
        }
        for (Node* current = head; current; current = current->next) {
            out << current->value << " ";
        }
        out << "\n";
        out << endl;
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
    int push_back(int value) override{
        return 0;
    }
    int pop_back() override{
        return 0;
    }



private:

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

    void print_in_file() const override {
        ofstream out("stack.txt");
        if (!out.is_open()) {
            throw runtime_error("Не удалось открыть файл для записи");
        }
        for (Node* current = top; current; current = current->next) {
            out << current->value << " ";
        }
        out<<"\n";
        out << endl;
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
    int push_back(int value) override{
        return 0;
    }
    int pop_back() override{
        return 0;
    }

private:

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

    void print_in_file() const override {
        ofstream out("deque.txt");
        if (!out.is_open()) {
            throw runtime_error("Не удалось открыть файл для записи");
        }
        for (Node* current = head; current; current = current->next) {
            out << current->value << " ";
        }
        out << "\n";
        out << endl;
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

    void print(){
        for (int i = 0; i < num_queues; i++){         
            queues[i]->print();
        }
    }

    void save() {
        for (int i = 0; i < num_queues; ++i) {
            queues[i]->print_in_file();
        }
    }

    void read_digits_from_file(ListQueue* listqueue, StackQueue* stackqueue, DequeQueue* dequequeue) {
        std::ifstream file("Lists.txt");
        if (!file.is_open()) {
            throw std::runtime_error("Could not open file");
        }

        int digit;
        while (file >> digit) {
            listqueue->push_forward(digit);
        }
        file.close();

        std::ifstream file1("stack.txt");
        if (!file1.is_open()) {
            throw std::runtime_error("Could not open file");
        }

        while (file1 >> digit) {
            stackqueue->push_forward(digit);
        }
        file1.close();

        std::ifstream file2("deque.txt");
        if (!file2.is_open()) {
            throw std::runtime_error("Could not open file");
        }

        while (file2 >> digit) {
            dequequeue->push_forward(digit);
        }
        file2.close();

    }

private:
    Queue* queues[100];
    int num_queues = 0;
};


int main() {
    Keeper keeper;

    ListQueue* listQueue = new ListQueue();

    StackQueue* stackQueue = new StackQueue();
    
    DequeQueue* dequeQueue = new DequeQueue();

int choice;
    do {
        cout << "Меню:" << endl;
        cout << "1 - Добавление элемента в список" << endl;
        cout << "2 - добавление элемента в стек" << endl;
        cout << "3 - добавление элемента в дек" << endl;
        cout << "4 - достать элемент из списка" << endl;
        cout << "5 - достать элемент из стека" << endl;
        cout << "6 - достать элемент из дека" << endl;
        cout << "7 - вывести список на экран" << endl;
        cout << "8 - вывести стек на экран" << endl;
        cout << "9 - вывести дек на экран" << endl;
        cout << "10 - добавить список в контейнер" << endl;
        cout << "11 - добавить стек в контейнер" << endl;
        cout << "12 - добавить дек в контейнер" << endl;
        cout << "13 - вывести содержимое контейнера" << endl;
        cout << "14 - сохранить содержимое контейнера" << endl;
        cout << "15 - извлечь содержимое контейнера из файла" << endl;
        cout << "16 - Выход из программы" << endl;
        cout << "Введите ваш выбор: ";
        cin >> choice;

        switch (choice) {
            case 1:
                int element;
                cout << "Введите элемент для добавления: ";
                cin >> element;
                listQueue->push_forward(element);
                break;
            case 2:
                int element1;
                cout << "Введите элемент для добавления: ";
                cin >> element1;
                stackQueue->push_forward(element);
                break;
            case 3:
                int element2;
                cout << "Введите элемент для добавления: ";
                cin >> element2;
                listQueue->push_forward(element);
                break;
            case 4: {
                cout << listQueue->pop_forward();
                break;                
            }
            case 5: {
                cout << stackQueue->pop_forward();
                break; 
            }
            case 6: {
                cout << dequeQueue->pop_forward();
                break; 
            }
            case 7: {
                listQueue->print();
                break; 
            }   
            case 8: {
                stackQueue->print();
                break; 
            }   
            case 9: {
                dequeQueue->print();
                break; 
            }    
            case 10: {
                keeper.add(listQueue);
                break; 
            } 
            case 11: {
                keeper.add(stackQueue);
                break; 
            } 
            case 12: {
                keeper.add(dequeQueue);
                break; 
            }          
            case 13: {
                keeper.print();
                break; 
            } 
            case 14: {
                keeper.save();
                break; 
            } 
            case 15: {
                keeper.read_digits_from_file(listQueue, stackQueue, dequeQueue );
                break; 
            }                                    
            case 16:
                cout << "Выход из программы." << endl;
                break;
            default:
                cout << "Неверный выбор!" << endl;
        }
    } while (choice != 16);
    return 0;
}