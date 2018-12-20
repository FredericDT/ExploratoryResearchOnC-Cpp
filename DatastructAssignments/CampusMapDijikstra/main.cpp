#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <limits>
#include <set>
#include <algorithm>
#include <functional>

#include "Edge.h"
#include "Vertex.h"

#define min(a, b) (a) > (b) ? (b) : (a)

//#define DEBUG

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
        std::map<unsigned, Vertex> vertexs;
        std::map<std::pair<unsigned, unsigned>, unsigned> computedDistances;

        Map() : vertexs{}, computedDistances{} {}

        static Map load(std::string const &pathOfVertexs, std::string const &pathOfEdges) {
            Map m = Map();
            std::ifstream vertexsFile;
            vertexsFile.open(pathOfVertexs);
            while (!vertexsFile.eof()) {
                unsigned id;
                std::string name;
                vertexsFile >> id >> name;
                Vertex v = Vertex(id, name);
                m.vertexs[id] = v;
            }
            vertexsFile.close();
            std::ifstream edgesFile;
            edgesFile.open(pathOfEdges);
            while (!edgesFile.eof()) {
                unsigned id1, id2, distance;
                edgesFile >> id1 >> id2 >> distance;
                m.vertexs[id1].connectedEdges.emplace_back(Edge(&m.vertexs[id2], distance));
                m.vertexs[id2].connectedEdges.emplace_back(Edge(&m.vertexs[id1], distance));
            }
            edgesFile.close();
            return m;
        }

        static bool idDistanceCompare(const std::pair<unsigned, unsigned> &a, const std::pair<unsigned, unsigned> &b) {
            return a.second < b.second;
        }

        void computeAllMinimunDistances() {
            if (this->computedDistances.size() == this->vertexs.size() * this->vertexs.size()) {
                return;
            }
            for (auto i = this->vertexs.begin(); i != this->vertexs.end(); ++i) {
                this->minimumDistance(i->first, i->first);
            }
        }

        unsigned minimumDistance(unsigned id1, unsigned id2) {
            if (computedDistances.find(std::make_pair(id1, id2)) != computedDistances.end()) {
                return computedDistances[std::make_pair(id1, id2)];
            }
            std::set<unsigned> setOfIdOfUnvisitedVertexs{};
            for (auto i = this->vertexs.begin(); i != this->vertexs.end(); ++i) {
                setOfIdOfUnvisitedVertexs.insert(i->first);
            }
            std::map<unsigned, unsigned> distances{};
            for (auto j = setOfIdOfUnvisitedVertexs.begin(); j != setOfIdOfUnvisitedVertexs.end(); ++j) {
                distances[*j] = UINT32_MAX;
            }
            distances[id1] = 0;
            while (!setOfIdOfUnvisitedVertexs.empty()) {
                std::vector<std::pair<unsigned, unsigned>> iDistances{};
                for (auto i = distances.begin(); i != distances.end(); ++i) {
                    iDistances.emplace_back(std::make_pair(i->first, i->second));
                }
                std::sort(iDistances.begin(), iDistances.end(), idDistanceCompare);
                for (auto i = iDistances.begin(); i != iDistances.end(); ++i) {
                    if (setOfIdOfUnvisitedVertexs.find(i->first) == setOfIdOfUnvisitedVertexs.end()) {
                        continue;
                    }
                    std::vector<Edge> &connectedEdges = this->vertexs[i->first].connectedEdges;
                    for (auto j = connectedEdges.begin(); j != connectedEdges.end(); ++j) {
                        distances[j->connectedVertex->id] = min(i->second + j->distance,
                                                                distances[j->connectedVertex->id]);
                    }
                    setOfIdOfUnvisitedVertexs.erase(i->first);
                    break;
                }
            }
            for (auto i = distances.begin(); i != distances.end(); ++i) {
                computedDistances.insert(std::make_pair(std::make_pair(id1, i->first), distances[i->first]));
                if (i->first != id1) {
                    computedDistances.insert(std::make_pair(std::make_pair(i->first, id1), distances[i->first]));
                }
            }
            return computedDistances[std::make_pair(id1, id2)];
        }
    };
}

int main(int argc, char **argv) {
#ifndef DEBUG
    if (argc != 3) {
        std::cout << "Usage: CampusMapDijkstra <path_to_vertexs_file> <path_to_edges_file>";
    }
    fdt::Map m = fdt::Map::load(argv[1], argv[2]);
#else
    fdt::Map m = fdt::Map::load("Vertexs", "Edges");
#endif
    m.computeAllMinimunDistances();
    for (auto i = m.vertexs.begin(); i != m.vertexs.end(); ++i) {
        for (auto j = m.vertexs.begin(); j != m.vertexs.end(); ++j) {
            std::cout << i->second.name << " -> " << j->second.name << " " << m.minimumDistance(i->first, j->first)
                      << std::endl;
        }
    }
    return 0;
}