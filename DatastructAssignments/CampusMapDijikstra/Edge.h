#ifndef CAMPUSMAPDIJIKSTRA_EDGE_H
#define CAMPUSMAPDIJIKSTRA_EDGE_H

/**
 * @author FredericDT <frederic.dt.twh@gmail.com> DA8F097136E9AD8A
 * @date 20/12/2018
 *
 */
namespace fdt {
    /**
     * @class Vertex
     *
     * Entity of a vertex
     *
     */
    class Vertex;

    /**
     * @class Edge
     *
     * Entity of an edge
     *
     */
    class Edge {
    public:
        /**
         * @field Vertex *connectedVertex
         *
         * represent the destination of this edge
         * the source vertex is omitted
         *
         */
        Vertex *connectedVertex;

        /**
         * @field unsigned distance
         *
         * represent the distance between the source vertex and the destination vertex
         *
         */
        unsigned distance;

        /**
         * @constructor
         *
         * @param Vertex *connectedVertex
         *   a pointer to the destination vertex
         * @param unsigned distance
         *   distance between two vertexs
         *
         */
        Edge(Vertex *connectedVertex, unsigned distance) : connectedVertex(connectedVertex), distance(distance) {}

        /**
         * @finalizer
         *
         * defualt
         */
        ~Edge() = default;
    };
}


#endif //CAMPUSMAPDIJIKSTRA_EDGE_H
