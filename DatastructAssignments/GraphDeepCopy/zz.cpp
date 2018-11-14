/**
 * @author FredericDT<frederic.dt.twh@gmail.com> DA8F097136E9AD8A
 * @date 11/14/2018
 */

#include <iostream>

namespace fdt {
    enum GrandListNodeType {
        ATOM, LIST
    };

    template<typename AtomType>
    struct GrandListNode {
        GrandListNodeType type;
        union {
            AtomType atom;
            struct {
                struct GrandListNode *headPointer;
                struct GrandListNode *tailPointer;
            } pointers;
        };
    };

    template<typename T>
    void copy(struct GrandListNode<T> &target, struct GrandListNode<T> const &source) {
        if (source.type == ATOM) {
            target.atom = source.atom;
            target.type = ATOM;
            return;
        }
        target.type = LIST;
        target.pointers.headPointer = new GrandListNode<T>();
        copy(*target.pointers.headPointer, *source.pointers.headPointer);
        if (source.pointers.tailPointer) {
            target.pointers.tailPointer = new GrandListNode<T>();
            copy(*target.pointers.tailPointer, *source.pointers.tailPointer);
        } else {
            target.pointers.tailPointer = nullptr;
        }
    }

    template<typename T>
    void finalize(struct GrandListNode<T> &node) {
        if (node.type == ATOM) {
            delete &node;
            return;
        }
        finalize(*node.pointers.headPointer);
        if (node.pointers.tailPointer) {
            finalize(*node.pointers.tailPointer);
        }
    }
}

//template<typename T>
//void operator delete(struct fdt::GrandListNode<T> &n) {
//    fdt::finalize(n);
//}

int main() {
    fdt::GrandListNode<int> n{};
    n.type = fdt::LIST;
    n.pointers.tailPointer = nullptr;
    n.pointers.headPointer = new fdt::GrandListNode<int>();
    n.pointers.headPointer->type = fdt::ATOM;
    n.pointers.headPointer->pointers.tailPointer = nullptr;
    n.pointers.headPointer->atom = 10001;
    fdt::GrandListNode<int> m{};
    fdt::copy(m, n);
    std::cout << "h1" << std::endl;
    return 0;
}

