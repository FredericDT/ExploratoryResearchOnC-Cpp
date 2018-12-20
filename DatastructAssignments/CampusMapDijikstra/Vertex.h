#ifndef CAMPUSMAPDIJIKSTRA_VERTEX_H
#define CAMPUSMAPDIJIKSTRA_VERTEX_H

#include <string>
#include <vector>

#include "Edge.h"

/**
 * @author FredericDT <frederic.dt.twh@gmail.com> DA8F097136E9AD8A
 * @date 20/12/2018
 *
 */
namespace fdt {
    /**
     * @class Edge
     *
     * Entity of an edge
     *
     */
    class Edge;

    /**
     * @class Vertex
     *
     * Entity of a vertex
     *
     */
    class Vertex {
    public:
        /**
         * @field unsigned id
         *
         * vertex's id
         *
         */
        unsigned id;
        /**
         * @field std::string name
         *
         * vertex's name
         *
         */
        std::string name;
        /**
         * @field std::vector<Edge> connectedEdges
         *
         * all edge attached to this vertex
         *
         */
        std::vector<Edge> connectedEdges;

        /**
         * @constructor
         *
         * default constructor
         * should not be called
         *
         */
        Vertex() : id(0), name(""), connectedEdges{} {}

        /**
         * @constructor
         *
         * @param unsigned id
         *   vertex's id
         * @param std::string name
         *   vertex's name
         *
         * main constructor
         * construct a vertex from its id and name
         *
         */
        Vertex(unsigned id, std::string const &name) : id(id), name(name), connectedEdges{} {}

        /**
         * @finalizer
         *
         * default
         */
        ~Vertex() = default;
    };
}


#endif //CAMPUSMAPDIJIKSTRA_VERTEX_H
