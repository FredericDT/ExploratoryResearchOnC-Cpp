#include <iostream>
#include <vector>
#include <string>

/**
 * @Assignment
 *
 * 绘制学校地图；
 * 将学校的所有建筑物当作节点，两个建筑物间如果直接有路相连则这两个节点间有一条边，路径的长度或者步行所化时间作为边的权值；
 * 用户输入任意两个建筑物，可以计算出它们之间的最短距离，并给出最短路径
 * 需要提交设计报告和源代码，要求和《实验一》一样
 * 补充：给出建筑物内各个位置之间的最短路径；
 *
 */

namespace fdt {
    class Map {
    public:
        static class Vertex {
            unsigned id;
            std::string name;
            std::vector<Edge> connectedEdges;

            Vertex(unsigned id, std::string const &name) : id(id), name(name), connectedEdges{} {}

            ~Vertex() = default;
        };
        static class Edge {
            std::pair<Vertex *, Vertex *> connectedVertexs;
            unsigned distance;
        };
        std::vector<Vertex> vertexs;
    };
}

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}