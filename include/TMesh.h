#include <memory>
#include <fstream>
// #include "TVertex.h"
// #include "THalfEdge.h"
#include "TFace.h"
#include "utils.h"
#include "predicates2.h"

class Mesh {
    public:
        Mesh(std::vector<Vertex> points);

        void addVertex(Vertex& new_v);
        Face* addFace(Vertex*v1, Vertex*v2, Vertex*v3);
        HalfEdge* addHalfEdge(Vertex*v1, Vertex*v2);
        void addingVertexInT(Vertex& new_v, Face* current_face);
        void splitEdgeWithVertex(Vertex& new_v, HalfEdge* original_he);

        HalfEdge* next(HalfEdge* current);

        void removeVertex(unsigned int index);

        bool isInsideTriangle(Vertex& v, Face* face);
        bool isOnSegment(HalfEdge* edge, Vertex* vertex);

        bool hasVertex(Vertex v);

        double distance(Vertex* v1, Vertex* v2);

        std::vector<Vertex>& getAllVertices();  // Devolver una referencia al vector de vértices
        std::vector<Face>& getAllFaces();

    private:
        std::vector<Face> all_faces;
        std::vector<HalfEdge> all_half_edges;
        std::vector<Vertex> all_vertices;
};