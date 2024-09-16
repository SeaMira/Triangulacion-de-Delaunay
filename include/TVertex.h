#ifndef _VERTEX_
#define _VERTEX_

#include "TCommon.h"

class Vertex {
    public:
        Vertex(double _x, double _y) : x(_x), y(_y) {};
        ~Vertex() {};

        void set_x(double _x);
        void set_y(double _y);
        // void set_z(double _z);

        double get_x();
        double get_y();
        // double get_z();

        void add_incoming_half_edge(unsigned int _i);
        void add_outgoing_half_edge(unsigned int _i);

        std::unordered_set<unsigned int> get_incoming_half_edges();
        std::unordered_set<unsigned int> get_outgoing_half_edges();

        void set_handle(unsigned int _i);
        unsigned int handle();
    private:
        double x, y;
        unsigned int vertex_handle;
        std::unordered_set<unsigned int> incoming_half_edges;
        std::unordered_set<unsigned int> outgoing_half_edges;
        bool deleted = false;
};

#endif