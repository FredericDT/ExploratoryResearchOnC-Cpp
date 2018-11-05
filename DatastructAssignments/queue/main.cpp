#include <iostream>

template<typename T>
class Queue {
private:
    unsigned length = 0;
    T *datas;
    unsigned rear = 0;
    //unsigned front = 0;
public:
    const unsigned size;

    static const unsigned DEFAULT_SIZE = 20;

    unsigned front() {
        int f = this->rear - this->length;
        if (f < 0) {
            f += this->size;
        }
        return (unsigned)f;
    }

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
        return this->datas[this->front()];
    }

    T pull() {
        if (this->isEmpty()) {
            return 0;
        }
        unsigned t = this->front();
        --this->length;
//        ++this->front;
//        if (this->front >= this->size) {
//            this->front = 0;
//        }
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

int main() {
    auto *q = new Queue<int>();
    std::cout << "size=" << q->size << std::endl;
    for (int i = 0; i < q->size; ++i) {
        q->push(i);
        std::cout << "pushed " << i << std::endl;
        std::cout << "top " << q->top() << std::endl;
        if (1) {
            int t = q->pull();
            std::cout << "pulled " << t << std::endl;
        }
    }
    delete q;
}