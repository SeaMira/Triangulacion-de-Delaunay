#include "THalfEdge.h"

 void HalfEdge::set_vertex_one(Vertex *_v1) {
    v1 = _v1;
}

void HalfEdge::set_vertex_two(Vertex *_v2) {
    v2 = _v2;
}

Vertex* HalfEdge::get_vertex_one() {
    return v1;
}

Vertex* HalfEdge::get_vertex_two() {
    return v2;
}

void HalfEdge::set_handle(unsigned int _i) {
    half_edge_handle = _i;
}

unsigned int HalfEdge::handle() {
    if (this == nullptr) {
        return std::numeric_limits<unsigned int>::max();
    }
    return half_edge_handle;
}

void HalfEdge::set_next_handle(unsigned int _i) {
    next_half_edge_handle = _i;
}
unsigned int HalfEdge::next_handle() {
    if (this == nullptr) {
        return std::numeric_limits<unsigned int>::max();
    }
    return next_half_edge_handle;
}

void HalfEdge::set_parent_face(unsigned int _i) {
    parent_face_handle = _i;
}

unsigned int HalfEdge::get_parent_face() {
    return parent_face_handle;
}

void HalfEdge::set_boundary(bool _boundariness) {
    boundary_half_edge = _boundariness;
}

bool HalfEdge::is_boundary() {
    return boundary_half_edge;
}

void HalfEdge::set_opposing_half_edge(unsigned int _i) {
    opposing_half_edge = _i;
}

unsigned int HalfEdge::get_opposing_half_edge() {
    return opposing_half_edge;
}

void HalfEdge::set_deleted() {
    deleted = true;
}

bool HalfEdge::get_deleted() {
    return deleted;
}