#include "TVertex.h"

void Vertex::set_handle(unsigned int _i) {
    vertex_handle = _i;
}

unsigned int Vertex::handle() {
    if (this == nullptr) {
        return std::numeric_limits<unsigned int>::max();
    }
    return vertex_handle;
}

void Vertex::set_x(double _x) {
    x = _x;
}

void Vertex::set_y(double _y) {
    y = _y;
}

// void Vertex::set_z(double _z) {
//     z = _z;
// }

double Vertex::get_x() {
    return x;
}

double Vertex::get_y() {
    return y;
}

// double Vertex::get_z() {
//     return z;
// }

void Vertex::add_incoming_half_edge(unsigned int _i) {
    incoming_half_edges.insert(_i);
}

void Vertex::add_outgoing_half_edge(unsigned int _i) {
    outgoing_half_edges.insert(_i);
}

std::unordered_set<unsigned int> Vertex::get_incoming_half_edges() {
    return incoming_half_edges;
}

std::unordered_set<unsigned int> Vertex::get_outgoing_half_edges() {
    return outgoing_half_edges;
}