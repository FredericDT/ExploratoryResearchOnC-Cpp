//
// Created by FredericDT on 11/11/2018.
//

/**
 * 迷宫问题
 *
 * 从开始位置（start）找出到出口（end）的通路，并从start到end输出；输出路径的长度。
 * 采用下图迷宫
 * 可以将节点进行编号，从1开始编号，编号次序从上到下，从左到右；保存每条边，根据两个节点之间是否有边，来决定是否能够走通；
 * 将边保存在文件中，用俩个端点来表示一条边；
 * 每个节点的分支数不一样，要求根据分支数决定遍历的方向数，不能用恒定的遍历方向数。
 * 需要提交设计报告和源代码，要求和《实验一》一样
 * 补充：找到从start到end的一条最短的路径；当迷宫有多个出口应该如何找到最近的出口；
 *
 */

#include <iostream>
#include <fstream>
#include <cassert>
#include <vector>
#include <map>
#include <set>
#include <queue>

namespace fdt {
    class Maze {
    public:
        class Node {
        public:
            unsigned id;

            bool isEnd = false;

            std::set<class Node> to;

            explicit Node(unsigned id) : id(id), to() {}

            Node(unsigned id, bool isEnd) : id(id), isEnd(isEnd), to() {}

            explicit operator bool() {
                return this->id > 0;
            }

            friend std::ostream &operator<<(std::ostream &os, const Node &node) {
                os << "id: " << node.id << " to: ";
                for (auto i : node.to) {
                    os << i.id << " ";
                }
                os << std::endl;
                return os;
            }

            bool operator==(const Node &rhs) const {
                return id == rhs.id;
            }

            bool operator!=(const Node &rhs) const {
                return !(rhs == *this);
            }

            bool operator<(const Node &c) const {
                return this->id < c.id;
            }

            Node() : id(0) {}
        };

        std::map<unsigned, class Maze::Node> nodes;
        std::set<std::set<unsigned>> paths;
        unsigned start = 0;

        explicit Maze() : nodes(), paths() {}

        static int load(class Maze &maze, std::string &pathOfNodes, std::string &pathOfPaths) {
            std::ifstream file;
            file.open(pathOfNodes);
            if (file.is_open()) {
                while(!file.eof() && file.good()) {
                    unsigned id = 0;
                    bool start = false;
                    bool end = false;
                    file >> id >> start >> end;
                    if (id <= 0) break;
                    maze.nodes.insert(std::pair<unsigned, class Node>(id, Maze::Node(id, end)));
                    if (start) {
                        maze.start = id;
                    }
                }
                file.close();
            }
            file.open(pathOfPaths);
            if (file.is_open()) {
                while (!file.eof()) {
                    unsigned p1 = 0, p2 = 0;
                    file >> p1 >> p2;
                    if (!(p1 > 0 && p2 > 0)) break;
                    maze.paths.insert(std::set<unsigned>({p1, p2}));
                    class Node &np1 = maze.nodes[p1];
                    class Node &np2 = maze.nodes[p2];
                    assert(np1 && np2);
                    np1.to.insert(np2);
                    np2.to.insert(np1);
                }
                file.close();
            }
            return 0;
        }

        static int serialize(class Maze &maze, std::string &pathOfNodes, std::string &pathOfPaths) {
            std::ofstream file;
            file.open(pathOfNodes);

            if (file.is_open()) {
                for (auto &i : maze.nodes) {
                    file << i.first << " " << (i.first == maze.start) << " " << i.second.isEnd << std::endl;
                }
                file.close();
            } else {
                throw "Cant open " + pathOfNodes;
            }
            std::set<std::set<unsigned>> pool;
            file.open(pathOfPaths);
            for (auto &p : maze.nodes) {
                for (auto &t : p.second.to) {
                    pool.insert(std::set<unsigned>({p.first, t.id}));
                }
            }
            if (file.is_open()) {
                for (auto &b : pool) {
                    for (auto &p : b) {
                        file << p << " ";
                    }
                    file << std::endl;
                }
                file.close();
            } else {
                throw "Cant open " + pathOfPaths;
            }
            return 0;
        }

        static bool bfs(Maze &m, std::vector<unsigned> &result) {
            std::queue<std::vector<unsigned>> q = std::queue<std::vector<unsigned>>();
            std::set<unsigned> visited = std::set<unsigned>();
            q.push(std::vector<unsigned>({m.start}));
            visited.insert(m.start);
            while(!q.empty()) {
                std::vector<unsigned> l = q.front();
                for (auto &i : m.nodes[l.back()].to) {
                    if (visited.find(i.id) == visited.end()) {
                        visited.insert(i.id);
                        std::vector<unsigned> n = l;
                        n.push_back(i.id);
                        if (i.isEnd) {
                            result = n;
                            return true;
                        }
                        q.push(n);
                    }
                }
                q.pop();
            }
            return false;
        }

        static bool searchForShortestPath(Maze &m, std::vector<unsigned> &result) {
            return bfs(m, result);
        }
    };
}

int main() {
    fdt::Maze m;
    std::string nodes("nodes");
    std::string paths("paths");
    fdt::Maze::load(m, nodes, paths);
    std::cout << "loaded" << std::endl;
    std::vector<unsigned> result;
    fdt::Maze::searchForShortestPath(m, result);
    std::cout << "length: " << result.size() << std::endl;
    std::cout << "path: ";
    for (unsigned &i : result) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    std::string sn("sn");
    std::string sp("sp");
    fdt::Maze::serialize(m, sn, sp);
    std::cout << "serialized" << std::endl;
    return 0;
}