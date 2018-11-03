#include <iostream>

template<typename T>
class Queue {
private:
    unsigned length = 0;
    unsigned size;
    T *datas;
    unsigned rear = 0;
    unsigned front = 0;
public:
    static const unsigned DEFAULT_SIZE = 20;

    Queue() : size(DEFAULT_SIZE) {
        this->datas = new T[size];
    }

    explicit Queue(unsigned size) : size(size) {
        this->datas = new T[size];
    }

    ~Queue() {
        delete this->datas;
    }

    bool isFull() {
        return this->length == this->size;
    }

    bool isEmpty() {
        return this->length == 0;
    }

    T top() {
        if (this->isEmpty()) {
            return 0;
        }
        return this->datas[this->front];
    }

    T pull() {
        if (this->isEmpty()) {
            return 0;
        }
        --this->length;
        unsigned t = this->front;
        ++this->front;
        if (this->front >= this->size) {
            this->front = 0;
        }
        return this->datas[t];
    }

    bool push(T d) {
        if (this->isFull()) {
            return false;
        }
        ++this->length;
        unsigned t = this->rear;
        ++this->rear;
        if (this->rear >= this->size) {
            this->rear = 0;
        }
        this->datas[t] = d;
        return true;
    }

    unsigned getLength() {
        return this->length;
    }
};