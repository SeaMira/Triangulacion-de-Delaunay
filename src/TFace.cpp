#include "TFace.h"

void Face::set_handle(unsigned int _i) {
    face_handle = _i;
}

unsigned int Face::handle() {
    if (this == nullptr) {
        return std::numeric_limits<unsigned int>::max();
    }
    return face_handle;
}

bool Face::is_valid() {
    if (handle() == std::numeric_limits<unsigned int>::max()) {
        return false;
    } else {
        return true;
    }
}

void Face::set_one_half_edge(HalfEdge *half_edge) {
    one_half_edge = half_edge;
}

HalfEdge *Face::get_one_half_edge() {
    return one_half_edge;
}

void Face::swap_vertex(Vertex *_v1 = nullptr, Vertex *_v2 = nullptr, Vertex *_v3 = nullptr) {
    if (_v1 != nullptr) {
        v1 = _v1;
    }
    if (_v2 != nullptr) {
        v2 = _v2;
    }
    if (_v3 != nullptr) {
        v3 = _v3;
    }
}

Vertex *Face::get_vertex_one() {
    return v1;
}

Vertex *Face::get_vertex_two() {
    return v2;
}

Vertex *Face::get_vertex_three() {
    return v3;
}

std::tuple<Vertex *, Vertex *, Vertex *> Face::get_vertices() {
    return std::make_tuple(v1, v2, v3);
}

std::tuple<double, double, double> Face::get_normal() {
    double x = 0.0;
    double y = 0.0;
    double z = 0.0;
    return std::make_tuple(x, y, z);
}

bool Face::is_deleted() {
    return deleted;
}

void Face::markDeleted() {
    deleted = true;
}