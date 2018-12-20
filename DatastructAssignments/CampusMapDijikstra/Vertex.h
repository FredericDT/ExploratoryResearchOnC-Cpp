#ifndef CAMPUSMAPDIJIKSTRA_VERTEX_H
#define CAMPUSMAPDIJIKSTRA_VERTEX_H

#include <string>
#include <vector>

#include "Edge.h"

namespace fdt {
    class Edge;

    class Vertex {
    public:
        unsigned id;
        std::string name;
        std::vector<Edge> connectedEdges;

        Vertex(): id(0), name(""), connectedEdges{} {}

        Vertex(unsigned id, std::string const &name) : id(id), name(name), connectedEdges{} {}

        ~Vertex() = default;
    };
}


#endif //CAMPUSMAPDIJIKSTRA_VERTEX_H
