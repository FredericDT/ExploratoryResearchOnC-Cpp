#include <iostream>
#include <string>

using namespace std;

template<typename T>
class LinkedList {
public:
    LinkedList() : tail(new LinkedListNode(NULL)), head(new LinkedListNode(NULL, NULL)), current(this->head) {
        this->head->next = this->tail;
        //this->tail->next = NULL;
    }

    LinkedList *insert(T value) {
        LinkedListNode *node = new LinkedListNode(value, this->current->next);
        if (this->isTail()) {
            this->current->next = node;
        } else {
            this->current->next->next = node;
        }
        this->current = this->current->next;
        ++this->size;
        return this;
    }

    T getCurrentValue() {
        return this->current->next != NULL ? this->current->next->value : NULL;
    }

    LinkedList *toHead() {
        this->current = this->head;
        return this;
    }

    bool isTail() {
        return this->current->next == this->tail;
    }

    unsigned int getSize() {
        return this->size;
    }

    LinkedList *deleteCurrent() {
        if (this->isTail()) {
            return this;
        }
        LinkedListNode *current = this->current->next;
        this->current->next = current->next;
        delete current;
        --this->size;
        return this;
    }

    LinkedList *next() {
        if (this->isTail()) {
            return this;
        }
        this->current = this->current->next;
        return this;
    }

    LinkedList *modifyCurrent(T value) {
        if (this->isTail()) {
            return this;
        }
        this->current->next->value = value;
        return this;
    }

private:
    class LinkedListNode {
    public:
        T value;
        LinkedListNode *next;

        LinkedListNode() : value(NULL), next(NULL) {}

        LinkedListNode(T value, LinkedListNode *next) : value(value), next(next) {}

        explicit LinkedListNode(T value) : value(value), next(NULL) {}

        inline T operator()() {
            return this->value;
        }

        inline T operator()(T value) {
            this->value = value;
            return this->value;
        }
    };

    LinkedListNode *head;
    LinkedListNode *tail;
    LinkedListNode *current;

    unsigned int size = 0;
};

bool stringEquals(const string a, const string b) {
    return a == b;
}

void println(const string i) {
    std::cout << i << std::endl;
}

int main() {
    LinkedList<int> *list = new LinkedList<int>();
    string command;
    while (true) {
        println("input: [q, insert, next, delete, current, size, istail, tohead]");
        std::cin >> command;
        //mmp!
        if (stringEquals(command, "q")) {
            break;
        } else if (stringEquals(command, "insert")) {
            println("input a value");
            int value;
            std::cin >> value;
            list->insert(value);
            std::cout << "inserted " << value << std::endl;
        } else if (stringEquals(command, "next")) {
            list->next();
            println("moved");
        } else if (stringEquals(command, "delete")) {
            list->deleteCurrent();
            println("deleted");
        } else if (stringEquals(command, "current")) {
            std::cout << "current value: " << list->getCurrentValue() << std::endl;
        } else if (stringEquals(command, "size")) {
            std::cout << "size: " << list->getSize() << std::endl;
        } else if (stringEquals(command, "istail")) {
            std::cout << "istail: " << list->isTail() << std::endl;
        } else if (stringEquals(command, "tohead")) {
            list->toHead();
            println("moved");
        }
    }
    println("exit");
    return 0;
}
