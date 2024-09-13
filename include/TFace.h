#ifndef _FACE_
#define _FACE_

#include "TVertex.h"
#include "THalfEdge.h"
#include "TCommon.h"

class Face {
    public:
        Face(Vertex *_v1, Vertex *_v2, Vertex *_v3) : v1(_v1), v2(_v2), v3(_v3) {};

        ~Face() {};

    public:
        void set_handle(unsigned int _i);

        unsigned int handle();

        bool is_valid();
        bool is_deleted();
        void markDeleted();

        void set_one_half_edge(HalfEdge *half_edge);
        HalfEdge *get_one_half_edge();

        void swap_vertex(Vertex *_v1 = nullptr, Vertex *_v2 = nullptr, Vertex *_v3 = nullptr);

        Vertex *get_vertex_one();
        Vertex *get_vertex_two();
        Vertex *get_vertex_three();

        std::tuple<Vertex *, Vertex *, Vertex *> get_vertices();
        std::tuple<double, double, double> get_normal();

    private:
        Vertex *v1, *v2, *v3;
        unsigned int face_handle;
        HalfEdge *one_half_edge = nullptr;
        bool deleted;
};

#endif // _FACE_