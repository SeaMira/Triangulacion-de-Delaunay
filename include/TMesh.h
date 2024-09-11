#include <memory>
#include <fstream>
#include "TVertex.h"
#include "THalfEdge.h"
#include "TFace.h"

class Mesh {
    public:
        Mesh(std::vector<Vertex> points);
        void addVertex(Vertex& new_v);
        void removeVertex(unsigned int index);

        bool isInsideTriangle(Vertex& v, Face* face);

        bool hasVertex(Vertex v);

        double distance(Vertex* v1, Vertex* v2);

    private:
        std::vector<Face> all_faces;
        std::vector<HalfEdge> all_half_edges;
        std::vector<Vertex> all_vertices;
};