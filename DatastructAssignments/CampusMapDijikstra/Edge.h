#ifndef CAMPUSMAPDIJIKSTRA_EDGE_H
#define CAMPUSMAPDIJIKSTRA_EDGE_H


namespace fdt {
    class Vertex;

    class Edge {
    public:
        Vertex *connectedVertex;
        unsigned distance;

        Edge(Vertex *connectedVertex, unsigned distance) : connectedVertex(connectedVertex), distance(distance) {}
    };
}


#endif //CAMPUSMAPDIJIKSTRA_EDGE_H
