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
    virtual int push(int value) = 0;
    virtual int pop() const = 0;
};

// Класс Очередь
class ListQueue : public Queue {
public:
    ListQueue() : head(nullptr), tail(nullptr) { cout << "Конструктор ListQueue без параметров" << endl; }
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

    int push(int value) override {
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

    int pop() const override {
        if (head) {
            int value = head->value;
            Node* next = head->next;
            delete head;
            head = next;
            if (!head) {
                tail = nullptr;
            } else {
                tail = head;
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

    int push(int value) override {
        Node* newNode = new Node(value);
        newNode->next = top;
        top = newNode;
        return 0;
    }

    int pop() const override {
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

    int push_front(int value) override {
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

    int pop_front() const override {
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

    int pop_back() const override {
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

// Класс Хранитель
class Keeper {
public:
    Keeper() { cout << "Конструктор Keeper без параметров" << endl; }
    Keeper(const Keeper& other) { cout << "Конструктор Keeper копирования" << endl; }
    ~Keeper() { cout << "Деструктор Keeper" << endl; }

    void add(Queue* obj) {
        if (size >= 100) throw runtime_error("Превышен максимальный размер хранилища");
        objects[size++] = obj;
    }

    void remove(int index) {
        if (index < 0 || index >= size) throw out_of_range("Индекс выходит за пределы хранилища");
        delete objects[index];
        for (int i = index; i < size - 1; i++) objects[i] = objects[i + 1];
        size--;
    }

    void save(const string& filename) {
        ofstream out(filename);
        if (!out.is_open()) throw runtime_error("Не удалось открыть файл для записи");
        out << size << endl;
        for (int i = 0; i < size; i++) {
            out << objects[i]->get() << endl;
        }
        out.close();
    }

    void load(const string& filename) {
        ifstream in(filename);
        if (!in.is_open()) throw runtime_error("Не удалось открыть файл для чтения");
        int n;
        in >> n;
        for (int i = 0; i < n; i++) {
            int value;
            in >> value;
            add(new List(value));
        }
        in.close();
    }

private:
    Queue* objects[100];
    int size = 0;
};

int main() {
    Keeper keeper;

    while (true) {
        cout << "Меню:" << endl;
        cout << "1. Добавить объект" << endl;
        cout << "2. Удалить объект" << endl;
        cout << "3. Вывести объекты на экран" << endl;
        cout << "4. Сохранить объекты в файл" << endl;
        cout << "5. Загрузить объекты из файла" << endl;
        cout << "0. Выход" << endl;

        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Введите тип объекта (1 - очередь, 2 - стек, 3 - дека): ";
                int type;
                cin >> type;
                cout << "Введите значение: ";
                int value;
                cin >> value;
                try {
                    switch (type) {
                        case 1:
                            keeper.add(new List(value));
                            break;
                        case 2:
                            keeper.add(new Stack(value));
                            break;
                        case 3:
                            keeper.add(new Deque(value));
                            break;
                        default:
                            throw invalid_argument("Неверный тип объекта");
                    }
                } catch (exception& e) {
                    cout << "Ошибка: " << e.what() << endl;
                }
                break;
            case 2:
                cout << "Введите индекс объекта: ";
                int index;
                cin >> index;
                try {
                    keeper.remove(index);
                } catch (exception& e) {
                    cout << "Ошибка: " << e.what() << endl;
                }
                break;
            case 3:
                for (int i = 0; i < keeper.size; i++) {
                    keeper.objects[i]->print();
                }
                break;
            case 4:
                cout << "Введите имя файла для сохранения: ";
                string filename;
                cin >> filename;
                try {
                    keeper.save(filename);
                } catch (exception& e) {
                    cout << "Ошибка: " << e.what() << endl;
                }
                break;
            case 5:
                cout << "Введите имя файла для загрузки: ";
                cin >> filename;
                try {
                    keeper.load(filename);
                } catch (exception& e) {
                    cout << "Ошибка: " << e.what() << endl;
                }
                break;
            case 0:
                return 0;
            default:
                cout << "Неверный выбор" << endl;
        }
    }

    return 0;
}
