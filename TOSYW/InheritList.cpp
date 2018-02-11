#include <iostream>
#include <string>

using namespace std;


template<class T>
class LinkedListNode {
public:
    T value;
    LinkedListNode *next;

    explicit LinkedListNode(T value) : value(value), next(nullptr) {}

    LinkedListNode(T value, LinkedListNode *next) : value(value), next(next) {}

    LinkedListNode() : value(0), next(nullptr) {}
};

template<class T>
class List {
public:
    explicit List(unsigned int size) : size(size) {}

    unsigned getSize() const {
        return this->size;
    }

    virtual T get(unsigned int index) {}

    virtual bool replace(unsigned int index, T value) {}

    inline T operator[](unsigned int i) {
        return get(i);
    }
    
    virtual ~List() = default;;

private:
    unsigned int size = 0;

};

template<class T>
class LinkedList : public List<T> {
public:
    explicit LinkedList(unsigned int size) : List<T>(size) {
        this->head = new LinkedListNode<T>();
        LinkedListNode<T> *current = this->head;
        int it = this->getSize() - 1;
        for (int i = 0; i < it; ++i) {
            current->next = new LinkedListNode<T>();
            current = current->next;
        }
    }

    T get(unsigned int index) override {
        if (index >= this->getSize()) {
            return NULL;
        }
        LinkedListNode<T> *current = this->head;
        for (int i = 0; i < index; ++i) {
            current = current->next;
        }
        return current->value;
    }

    bool replace(unsigned int index, T value) override {
        if (index >= this->getSize()) {
            return false;
        }
        LinkedListNode<T> *current = this->head;
        for (int i = 0; i < index; ++i) {
            current = current->next;
        }
        current->value = value;
        return true;
    }

    ~LinkedList() override {
        LinkedListNode<T> *current = this->head;
        while (current != nullptr) {
            LinkedListNode<T> *temp = current->next;
            delete current;
            current = temp;
        }
    }

private:
    LinkedListNode<T> *head;
};

template<class T>
class ArrayList : public List<T> {
public:
    explicit ArrayList(unsigned int size) : List<T>(size) {
        this->nodes = new T[size];
    }

    T get(unsigned int index) override {
        if (index >= this->getSize()) {
            return NULL;
        }
        return this->nodes[index];
    }

    bool replace(unsigned int index, T value) override {
        if (index >= this->getSize()) {
            return false;
        }
        this->nodes[index] = value;
        return true;
    }

    ~ArrayList() override {
        delete this->nodes;
    }

private:
    T *nodes;
};

// fuck cpp!

int main() {
    const unsigned int size = 10;
    List<int> *linked = new LinkedList<int>(size);
    List<int> *array = new ArrayList<int>(size);
    for (int i = 0; i < 10; ++i) {
        linked->replace(i, i + 10);
        array->replace(i, i + 20);
    }
    for (int i = 0; i < 10; ++i) {
        int linkedValue = (*linked)[i];//linked->get(i);
        int arrayValue = (*array)[i];//array->get(i);
        std::cout << "[" << i << "] linked: " << linkedValue << " array: " << arrayValue << std::endl;
    }
    delete linked;
    delete array;
    return 0;
}

