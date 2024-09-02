#include <random>
#include <cmath>
#include "mesh.h"

unsigned int getRandomFromRange(int min, int max) {
    // Initialize a random number generator
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(min, max);

    // Generate random number in the range [min, max]
    return distrib(gen);
}

namespace HalfMesh {

class DelaunayTriangulationMesh : public Mesh {
    
    public:

        Vertex* addVertex(Vertex* new_v ) {
            double x = new_v ->x, y = new_v ->y, z = new_v ->z;
            unsigned int init_edge_handle =  getRandomFromRange(0, edge_handle_to_edge_map.size());
            HalfEdge* edge = get_half_edge(init_edge_handle);


        }


        HalfEdge* getContainingTriangle(HalfEdge* starting_edge) {
            Face* starting_face = get_face(starting_edge->get_parent_face());
            Face* iter_face = starting_face;
            do {
                Vertex* v1 = iter_face->get_vertex_one(), v2 = iter_face->get_vertex_two(), v3 = iter_face->get_vertex_three();
                

            } while ()
        }

}

}
