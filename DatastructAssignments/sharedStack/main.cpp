#include <iostream>

template<typename T>
class SharedStack {
private:
    unsigned size;
    T *datas;
    unsigned f = 0;
    unsigned e;
public:
    enum TargetStack {
        FIRST, SECOND
    };

    explicit SharedStack(unsigned size) : size(size), e(size - 1) {
        this->datas = new T[size];
    }

    bool isFull() {
        return this->f > this->e;
    }

    bool push(T d, TargetStack targetStack = FIRST) {
        if (this->isFull()) {
            return false;
        }
        this->datas[targetStack == FIRST ? f++ : e--] = d;
        return true;
    }

    bool isEmpty(TargetStack targetStack = FIRST) {
        return targetStack == FIRST ? e == 0 : e + 1 == size;
    }

    T top(TargetStack targetStack = FIRST) {
        if (targetStack == FIRST) {
            if (!this->isEmpty(FIRST)) {
                return this->datas[f];
            }
        } else {
            if (!this->isEmpty(SECOND)) {
                return this->datas[e];
            }
        }
        return 0;
    }

    T pop(TargetStack targetStack = FIRST) {
        if (targetStack == FIRST) {
            if (!this->isEmpty(FIRST)) {
                return this->datas[f--];
            }
        } else {
            if (!this->isEmpty(SECOND)) {
                return this->datas[e++];
            }
        }
        return 0;
    }

    ~SharedStack() {
        delete this->datas;
    }
};