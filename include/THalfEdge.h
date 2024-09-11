#ifndef _HALF_EDGE_
#define _HALF_EDGE_

#include "TVertex.h"
#include "TFace.h"
#include "TCommon.h"


class HalfEdge {
    public:
        HalfEdge(Vertex *_v1, Vertex *_v2) : v1(_v1), v2(_v2) {};
        ~HalfEdge() {};

        void set_vertex_one(Vertex *_v1);
        void set_vertex_two(Vertex *_v2);

        Vertex* get_vertex_one();
        Vertex* get_vertex_two();

        void set_handle(unsigned int _i);
        unsigned int handle();
        
        void set_next_handle(unsigned int _i);
        unsigned int next_handle();

        void set_parent_face(unsigned int _i);
        unsigned int get_parent_face();

        void set_boundary(bool _boundariness);
        bool is_boundary() ;

        void set_opposing_half_edge(unsigned int _i);
        unsigned int get_opposing_half_edge();

    private:
        Vertex *v1, *v2;
        unsigned int half_edge_handle;
        unsigned int next_half_edge_handle;
        unsigned int parent_face_handle;
        unsigned int opposing_half_edge = std::numeric_limits<unsigned int>::max();
        bool boundary_half_edge;
        bool deleted;
};


#endif