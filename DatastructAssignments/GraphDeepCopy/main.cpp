/**
 * @author FredericDT<frederic.dt.twh@gmail.com> DA8F097136E9AD8A
 * @date 11/14/2018
 */

#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>

template<typename T>
class Node {
public:
    enum Type {
        DATA, GRAPH
    };
    unsigned size = 0;

    class Data {
    public:
        Type type;
        union {
            T value;
            Node *node;
        } data;

        ~Data() = default;
    };

    Data *datas = nullptr;

private:
    std::unordered_map<Node *, Node *> m;

    void deepCopy(Node &node) {
        Node *p = &node;
        if (m.find(p) != m.end()) {
            return;
        }
        m.insert(std::make_pair(&node, this));
        this->size = node.size;
        this->datas = new Data[node.size];
        for (int i = 0; i < node.size; ++i) {
            if (node.datas[i].type == GRAPH) {
                this->datas[i].type = GRAPH;
                if (m.find(node.datas[i].data.node) != m.end()) {
                    this->datas[i].data.node = m[&node];
                } else {
                    this->datas[i].data.node = new Node();
                    this->datas[i].data.node->deepCopy(*node.datas[i].data.node);
                }
            } else {
                this->datas[i].type = node.datas[i].type;
                this->datas[i].data.value = node.datas[i].data.value;
            }
        }
    }

    static void finalize(Node &node, std::unordered_set<Node *> &s) {
        if (s.find(&node) != s.end()) {
            return;
        }
        s.insert(&node);
        for (int i = 0; i < node.size; ++i) {
            if (node.datas[i].type == GRAPH) {
                finalize(*node.datas[i].data.node, s);
            }
        }
        delete[] node.datas;
    }

public:
    Node(Node &node) {
        m = std::unordered_map<Node *, Node *>{};
        this->deepCopy(node);
    }

    Node() {}

    ~Node() {
        std::unordered_set<Node *> s = std::unordered_set<Node *>();
        finalize(*this, s);
    }

    bool operator<(Node const &n) {
        return this < &n;
    }


};

int main() {
    Node<int> n{};
    n.size = 2;
    n.datas = new Node<int>::Data[2];
    n.datas[0].type = Node<int>::GRAPH;
    n.datas[0].data.node = &n;
    n.datas[1].type = Node<int>::DATA;
    n.datas[1].data.value = 1001;

    Node<int> n1{n};
    std::cout << "hi" << std::endl;
    return 0;
}
