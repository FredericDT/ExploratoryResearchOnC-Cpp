/**
 * @assignment
 *
 * 从键盘输入人数N（N<50）及N个人的编号（整型）、姓名、性别和年龄，正向建立带头节点的循环链表；
 * 输出循环链表各结点的值；
 * 输入开始报数的人的编号S、间隔的个数M和剩余人数X；
 * 在循环链表中查找到编号为S的结点；
 * 从1开始向后报数，将报M的人（结点）从循环链表中删除，并输出该人的编号；
 * 从刚才被删除人的下一个人开始重复步骤5，直至最后只剩下 X 个人为止；
 * 输出最后剩余的人的编号、姓名、性别和年龄。
 */

#include <iostream>
#include <cctype>
#include <string>
#include <sstream>
#include <cassert>

namespace fdt {
    /**
     * @author FredericDT
     * @date 2018/10/28
     */

    namespace josephus {

        /**
         * @param MAX_LIST_SIZE
         *
         * max list size defined in the slide file
         */
        const int MAX_LIST_SIZE = 50;

        /**
         * class printAbleObject
         *
         * fdt's base class for a print-able object
         * contains a function to_string() which convert this object to string
         */
        class printAbleObject {
        public:
            /**
             * return std::string
             *
             * a base function for convert the printAbleObject to std::string
             */
            virtual std::string to_string() = 0;
        };

        class Person : printAbleObject {
        public:
            int id;
            std::string name;
            enum Gender {
                MALE, FEMALE
            } gender;
            int age;

            /**
             * @constructor
             * default constructor with value
             *
             * id = 0
             * name = ""
             * gender = MALE
             * age = 0
             */
            Person() : id(0), name(""), gender(MALE), age(0) {};

            /**
             * @constructor
             * @param id
             *   id of the Person
             * @param name
             *   name of the Person
             * @param g
             *   gender of the Person
             * @param age
             *   age of the Person
             *
             * full field constructor
             */
            Person(int id, std::string &name, enum Gender g, int age) {
                this->id = id;
                this->name = name;
                this->gender = g;
                this->age = age;
            }

            /**
             * @return Person *
             * static method constructor
             *
             * build a Person instance from stdin
             */
            static Person *buildPFromStdin() {
                std::cout << "Please input p id: " << std::endl;
                int id;
                std::cin >> id;
                std::cout << "Please input p name: " << std::endl;
                std::string name;
                std::cin >> name;
                std::cout << "Please input p gender: (male, female)" << std::endl;
                std::string g;
                std::cin >> g;
                Person::Gender gender = Person::Gender::MALE;
                for (char &i : g) {
                    i = (char) tolower(i);
                    if (i == 'f') {
                        gender = FEMALE;
                        break;
                    }
                }
                std::cout << "Please input p age: " << std::endl;
                int age;
                std::cin >> age;
                Person *p = new class Person(id, name, gender, age);
                return p;
            }

            /**
             * @return std::string
             * @override printAbleObject::to_string()
             *
             * convert object's fields into a std::string
             */
            std::string to_string() override {
                std::ostringstream r;
                r << " id: " << std::to_string(this->id);
                r << " name: " << this->name;
                r << " gender: " << (this->gender == MALE ? "MALE" : "FEMALE");
                r << " age: " << std::to_string(this->age);
                return r.str();
            }

            ~Person() {
            }

            /**
             * @deprecated
             * @return std::ostream
             *
             * deprecated function for << append output
             * @see std::string to_string()
             */
            [[deprecated]] friend std::ostream &operator<<(std::ostream &os, const Person &p) {
                os << " id: " << p.id << " name: " << p.name << " gender: "
                   << (p.gender == MALE ? "MALE" : "FEMALE") << " age: " << p.age;
                return os;
            };

        };

        /**
         * @return bool
         *
         * a function to perform equality analyze
         * return 1 for left.id == right.id
         */
        inline bool operator==(const Person &l, const Person &r) {
            return l.id == r.id;
        }

        /**
         * @return bool
         * @see inline bool operator==(const Person &l, const Person &r)
         *
         * return the opposite value of function
         * inline bool operator==(const Person &l, const Person &r)
         */
        inline bool operator!=(const Person &l, const Person &r) {
            return !(l == r);
        }

        /**
         * @tparam T
         * Generic typed RemoveOnlyLoopList
         */
        template<typename T>
        class RemoveOnlyLoopList : printAbleObject {
        public:
            /**
             * @class Node
             *
             * implement of data node
             */
            class Node : printAbleObject {
            public:
                Node() {
                }

                Node(T *v) : value(v) {}

                ~Node() {}

                Node *next;

                T *value;

                /**
                 * @return std::string
                 * @override printAbleObject::to_string()
                 *
                 * convert object's fields into a std::string
                 */
                std::string to_string() override {
                    return this->value->to_string();
                }

                /**
                 * @return bool
                 *
                 * a function to perform equality analyze
                 * return 1 for left.value == right.value
                 */
                bool operator==(const Node &rhs) const {
                    return this->value == rhs.value;
                }

                /**
                 * @return bool
                 * @see bool operator==(const Node &rhs) const
                 *
                 * return the opposite value of function
                 * bool operator==(const Node &rhs) const
                 */
                bool operator!=(const Node &rhs) const {
                    return !(rhs == *this);
                }

            };

        private:
            /**
             * @constructor
             *
             * this constructor should not be accessd from outside of this class
             */
            RemoveOnlyLoopList() {
                throw "DEFAULT CONSTRUCTOR INVOKED ERROR";
            }

            int size;

            class Node *head;

            class Node *c;

            class Node *p;

        public:

            /**
             * @return std::string
             * @override printAbleObject::to_string
             *
             * convert object's data into a std::string
             */
            std::string to_string() override {
                std::ostringstream r;
                Node *n = this->head;
                while (n->next != head) {
                    r << n->to_string() << std::endl;
                    n = n->next;
                }
                r << n->to_string() << std::endl;
                return r.str();
            }

            /**
             * @enum FunctionStatus
             *
             * return fucntion status of this class
             */
            enum FunctionStatus {
                SUCCESS, FAILED
            };

            /**
             * @constructor
             * @param size
             *   list size
             * @param d
             *   An array containing the values you wish to initiate the list
             *
             * constructor for build a RemoveOnlyLoopList from T array
             */
            RemoveOnlyLoopList(int size, T *d[]) : size(size) {
                this->head = new Node(d[0]);
                this->head->next = this->head;
                this->c = this->head;
                Node *n = this->head;
                for (int i = 1; i < size; ++i) {
                    n->next = new Node(d[i]);
                    n->next->next = this->head;
                    n = n->next;
                    this->p = n;
                }
            }

            /**
             * @return int
             *
             * return the length of this lsit
             */
            int length() {
                return this->size;
            }

            /**
             * @return T *
             *
             * return a pointer which pointing to the current node
             */
            T *current() {
                return this->c->value;
            }

            /**
             * @return T *
             *
             * move the current pos marker to the next node, then
             * return a pointer which pointing to the current node
             */
            T *next() {
                this->c = this->c->next;
                this->p = this->p->next;
                return current();
            }

            /**
             * @return T *
             *
             * return a pointer to the node which has been rmoved from this list
             * @notice You MUST free the returned node manually, otherwise it causes memory leak
             */
            T *remove() {
                T *t = this->c->value;
                Node *pr = this->c;
                --this->size;
                this->p->next = this->c->next;
                this->c = this->c->next;
                delete pr;
                return t;
            }

            /**
             * @return FunctonStatus
             * @param t
             *   target T object
             *
             * move the pos marker to the node which equals to target
             */
            FunctionStatus moveTo(T &t) {
                while (t != *this->current()) {
                    this->next();
                }
                return t == *this->current() ? FunctionStatus::SUCCESS : FunctionStatus::FAILED;
            }

            /**
             * @finalize
             */
            ~RemoveOnlyLoopList() {
                if (this->size > 1) {
                    Node *n = this->head->next;
                    while (n != this->head) {
                        Node *t = n;
                        n = n->next;
                        delete t->value;
                        delete t;
                    }
                }
                delete this->head;
            }
        };

        /**
         * @return RemvoeOnlyLoopList<Person> *
         *
         * build a list for Person from stdin
         * intended for the assignment
         */
        RemoveOnlyLoopList<Person> *buildPListForJosephus() {
            int size;
            std::cout << "Please input list size: " << std::endl;
            std::cin >> size;
            assert(size > 0 && size < MAX_LIST_SIZE);
            Person **ps = new Person *[size];
            for (int i = 0; i < size; ++i) {
                ps[i] = Person::buildPFromStdin();
            }
            RemoveOnlyLoopList<Person> *lp = new RemoveOnlyLoopList<Person>(size, ps);
            return lp;
        }


        /**
         * @enum JosephusFunctionStatus
         *
         * function runtime status for JosephusFunctionStatus namespace
         */
        enum JosephusFunctionStatus {
            SUCCESS, FAIL
        };

        /**
         * @return JosephusFunctionStatus
         *
         * main body of the josephus assignment
         */
        JosephusFunctionStatus josephus() {
            RemoveOnlyLoopList<Person> *l = buildPListForJosephus();
            std::cout << "List values: " << std::endl << l->to_string();
            int startId;
            std::cout << "Please input S: " << std::endl;
            std::cin >> startId;
            int m;
            std::cout << "Please input M: " << std::endl;
            std::cin >> m;
            int remain;
            --m;
            std::cout << "Please input X: " << std::endl;
            std::cin >> remain;

            Person p;
            p.id = startId;

            if (RemoveOnlyLoopList<Person>::FunctionStatus::FAILED == l->moveTo(p)) {
                delete l;
                return FAIL;
            }

            if (l->length() < remain) {
                delete l;
                return FAIL;
            }

            std::cout << "Removed Objects's id: " << std::endl;
            while (l->length() > remain) {
                for (int i = 0; i < m; ++i) {
                    l->next();
                }
                Person *t = l->remove();
                std::cout << " id: " << t->id << std::endl;
                delete t;
            }
            std::cout << "Remain members: " << std::endl << l->to_string();
            delete l;
            return SUCCESS;
        }

    }
}

int main() {
    assert(fdt::josephus::josephus() == fdt::josephus::JosephusFunctionStatus::SUCCESS);
}