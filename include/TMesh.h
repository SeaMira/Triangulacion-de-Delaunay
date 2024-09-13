#include <memory>
#include <fstream>
#include "TVertex.h"
#include "THalfEdge.h"
#include "TFace.h"
#include "utils.h"
#include "predicates.h"

class Mesh {
    public:
        Mesh(std::vector<Vertex> points);

        void addVertex(Vertex& new_v);
        Face* addFace(Vertex*v1, Vertex*v2, Vertex*v3);
        HalfEdge* addHalfEdge(Vertex*v1, Vertex*v2);
        void addingVertexInT(Vertex& new_v, Face* current_face);

        HalfEdge* next(HalfEdge* current);

        void removeVertex(unsigned int index);

        bool isInsideTriangle(Vertex& v, Face* face);
        bool isOnSegment(HalfEdge* edge, Vertex* vertex);

        bool hasVertex(Vertex v);

        double distance(Vertex* v1, Vertex* v2);

    private:
        std::vector<Face> all_faces;
        std::vector<HalfEdge> all_half_edges;
        std::vector<Vertex> all_vertices;
};