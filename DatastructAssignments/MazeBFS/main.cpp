/**
 * @assignment
 *
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

/**
 * @author FredericDT <frederic.dt.twh@gmail.com> DA8F097136E9AD8A
 * @date 11/11/2018
 *
 */
namespace fdt {
    /**
     * @class Maze
     *
     * represent a read-only maze
     * cannot be changed by re-associate the nodes
     *
     * @field std::map<unsigned, class Maze::Node> nodes
     * @field
     *
     */
    class Maze {
    public:
        /**
         * @class Node
         *
         * represent a node of the maze
         *
         */
        class Node {
        public:
            /**
             * @field unsigned id
             *
             * id of the node
             */
            unsigned id;

            /**
             * @field bool isEnd
             * @default false
             *
             * representing this node is or isnot the end of the maze
             */
            bool isEnd = false;

            /**
             * @field std::set<class Node *> associatedNodesSet
             *
             * containing the pointer to the connected nodes
             */
            std::set<class Node *> associatedNodesSet;

            /**
             * @constructor explicit Node(unsigned id)
             *
             * @param unsigned id
             *
             * initialize the node with parameter id and an empty associatedNodesSet
             */
            explicit Node(unsigned id) : id(id), associatedNodesSet() {}

            /**
             * @constructor Node(unsigned id, bool isEnd)
             *
             * @param unsigned id
             * @param bool isEnd
             *
             * initialize the node with the given id, isEnd and an empty associatedNodesSet
             */
            Node(unsigned id, bool isEnd) : id(id), isEnd(isEnd), associatedNodesSet() {}

            /**
             * @function explicit operator bool()
             *
             * @return bool
             *
             * helper function to analyze the node is valid
             * return true for valid, the opposite is invalid
             */
            explicit operator bool() {
                return this->id > 0;
            }

            /**
             * @function friend std::ostream &operator<<(std::ostream &os, const Node &node)
             *
             * @return std::ostream &
             *
             * helper function to stream output the data of this node
             */
            friend std::ostream &operator<<(std::ostream &os, const Node &node) {
                os << "id: " << node.id << " isEnd: " << node.isEnd << " associatedNodesSet: ";
                for (auto i : node.associatedNodesSet) {
                    os << i->id << " ";
                }
                os << std::endl;
                return os;
            }

            /**
             * @function bool operator==(const Node &rhs) const
             *
             * @return bool
             *
             * to analyze two nodes are equal
             * return true for equal, the opposite for inequal
             */
            bool operator==(const Node &rhs) const {
                return id == rhs.id;
            }

            /**
             * @function bool operator!=(const Node &rhs) const
             *
             * @return bool
             *
             * @see function bool operator==(const Node &rhs) const
             *
             * return the opposite value of the 'equal' function
             */
            bool operator!=(const Node &rhs) const {
                return !(rhs == *this);
            }

            /**
             * @function bool operator<(const Node &c) const
             *
             * @return bool
             *
             * comparing two nodes, return true the first one's id is smaller than the second one's
             */
            bool operator<(const Node &c) const {
                return this->id < c.id;
            }

            /**
             * @constructor
             *
             * default constructor
             * should not be called
             */
            Node() : id(0) {}
        };

        /**
         * @field std::map<unsigned, class Maze::Node> nodesMap
         *
         * build a one-to-one relationship from the node id to
         * the instance of the node
         */
        std::map<unsigned, class Maze::Node> nodesMap;

        /**
         * @field std::set<std::set<unsigned>> pathsSet
         *
         * container of all the paths
         */
        std::set<std::set<unsigned>> pathsSet;

        /**
         * @field unsigned startNodeId
         * @default 0
         *
         * id of the start node
         */
        unsigned startNodeId = 0;

        /**
         * @function friend std::ostream &operator<<(std::ostream &os, const Maze &maze)
         *
         * @return std::ostream &
         *
         * helper function to stream output the data of this maze
         */
        friend std::ostream &operator<<(std::ostream &os, const Maze &maze) {
            os << "startNodeId: " << maze.startNodeId << std::endl;
            os << "nodesMap: " << std::endl;
            for (auto &i : maze.nodesMap) {
                os << i.second;
            }
            return os;
        }

        /**
         * @constructor
         *
         * initialize an empty maze
         */
        explicit Maze() : nodesMap(), pathsSet() {}

        /**
         * @static
         * @function static int load(class Maze &maze, std::string &pathOfNodes, std::string &pathOfPaths)
         * @return int
         *   0 for good
         *   any other value represent an error
         *
         * @param class Maze &maze
         *   target maze
         * @param std::string &pathOfNodes
         *   file path of the nodes
         * @param std::string &pathOfPaths
         *   file path of the maze paths
         *
         * load a maze from file
         * @protocol
         * @see static int serialize(class Maze &maze, std::string &pathOfNodes, std::string &pathOfPaths)
         */
        static int load(class Maze &maze, std::string &pathOfNodes, std::string &pathOfPaths) {
            std::ifstream file;
            file.open(pathOfNodes);
            if (file.is_open()) {
                while (!file.eof() && file.good()) {
                    unsigned id = 0;
                    bool start = false;
                    bool end = false;
                    file >> id >> start >> end;
                    if (id <= 0) break;
                    maze.nodesMap.insert(std::pair<unsigned, class Node>(id, Maze::Node(id, end)));
                    if (start) {
                        maze.startNodeId = id;
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
                    maze.pathsSet.insert(std::set<unsigned>({p1, p2}));
                    class Node &np1 = maze.nodesMap[p1];
                    class Node &np2 = maze.nodesMap[p2];
                    assert(np1 && np2);
                    np1.associatedNodesSet.insert(&np2);
                    np2.associatedNodesSet.insert(&np1);
                }
                file.close();
            }
            return 0;
        }

        /**
         * @static
         * @function static int serialize(class Maze &maze, std::string &pathOfNodes, std::string &pathOfPaths)
         * @return int
         *   0 for good
         *   any other value represent an error
         *
         * @param class Maze &maze
         *   target maze
         * @param std::string &pathOfNodes
         *   file path of the nodes
         * @param std::string &pathOfPaths
         *   file path of the maze paths
         *
         * serialize a maze to a pair of files
         * @protocol
         * a file containing all the nodes
         * whose format as follows
         * <node_id> <is_start> <is_end>
         *
         * a file containing all the paths
         * whose format as follows
         * <associated_node_id_1> <associated_node_id_2>
         */
        static int serialize(class Maze &maze, std::string &pathOfNodes, std::string &pathOfPaths) {
            std::ofstream file;
            file.open(pathOfNodes);

            if (file.is_open()) {
                for (auto &i : maze.nodesMap) {
                    file << i.first << " " << (i.first == maze.startNodeId) << " " << i.second.isEnd << std::endl;
                }
                file.close();
            } else {
                throw "Cant open " + pathOfNodes;
            }
            std::set<std::set<unsigned>> pool;
            file.open(pathOfPaths);
            for (auto &p : maze.nodesMap) {
                for (auto &t : p.second.associatedNodesSet) {
                    pool.insert(std::set<unsigned>({p.first, t->id}));
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

        /**
         * @static
         * @function static bool bfs(Maze &m, std::vector<unsigned> &result)
         *
         * implements the searchForShortestPath
         */
        static bool bfs(Maze &m, std::vector<unsigned> &result) {
            std::queue<std::vector<unsigned>> q = std::queue<std::vector<unsigned>>();
            std::set<unsigned> visited = std::set<unsigned>();
            q.push(std::vector<unsigned>({m.startNodeId}));
            visited.insert(m.startNodeId);
            while (!q.empty()) {
                std::vector<unsigned> l = q.front();
                for (auto &i : m.nodesMap[l.back()].associatedNodesSet) {
                    if (visited.find(i->id) == visited.end()) {
                        visited.insert(i->id);
                        std::vector<unsigned> n = l;
                        n.push_back(i->id);
                        if (i->isEnd) {
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

        /**
         * @static
         * @function static bool searchForShortestPath(Maze &m, std::vector<unsigned> &result)
         * @return bool
         *   true represent 'the path has been found'
         *   false represent 'no path'
         *
         * @param Maze &m
         *   target maze to parse
         * @param std::vector<unsigned> &result
         *   result path container
         *
         * this function is intended to find the shortest path from the start node of the maze
         * to any end node which takes the shortest path
         * the result vector is the path as it from 0 to its tail
         */
        static bool searchForShortestPath(Maze &m, std::vector<unsigned> &result) {
            return bfs(m, result);
        }
    };
}

int main() {
    fdt::Maze m; // instance of the maze
    std::string nodes("nodes"); // name of the file which containing the nodesMap
    std::string paths("paths"); // name of the file which containing the pathsSet
    fdt::Maze::load(m, nodes, paths); // load the maze from files predefined
    std::cout << "loaded" << std::endl;
    std::cout << m << std::endl;
    std::vector<unsigned> result; // result container
    fdt::Maze::searchForShortestPath(m, result); // search interface implementation : bfs
    std::cout << "length: " << result.size() << std::endl; // output the length
    std::cout << "path: "; // print the path
    for (unsigned &i : result) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    std::string sn("sn"); // serialize data save path for nodesMap
    std::string sp("sp"); // serialize data save path for pathsSet
    fdt::Maze::serialize(m, sn, sp); // serialize interface
    std::cout << "serialized" << std::endl;
    return 0;
}