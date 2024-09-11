#include "TMesh.h"

Mesh::Mesh(std::vector<Vertex> points) {
    double min_x = points[0].get_x(), min_y = points[0].get_y(), max_x = points[0].get_x(), max_y = points[0].get_y();
    for (int i = 1; i < points.size(); i++) {
        double x = points[i].get_x();
        double y = points[i].get_y();
        if (x < min_x) min_x = x;
        if (x > max_x) max_x = x;
        if (y < min_y) min_y = y;
        if (y > max_y) max_y = y;
    }

    // create containing rectangle
    //top right
    all_vertices.push_back(Vertex(max_x+1.0, max_y+1.0));
    all_vertices[0].set_handle(0);
    //top left
    all_vertices.push_back(Vertex(min_x-1.0, max_y+1.0));
    all_vertices[1].set_handle(1);
    //down left
    all_vertices.push_back(Vertex(min_x-1.0, min_y-1.0));
    all_vertices[2].set_handle(2);
    //down right
    all_vertices.push_back(Vertex(max_x+1.0, min_y-1.0));
    all_vertices[3].set_handle(3);

    // create first faces
    all_faces.push_back(Face(&all_vertices[0], &all_vertices[1], &all_vertices[3]));
    all_faces[0].set_handle(0);

    all_faces.push_back(Face(&all_vertices[1], &all_vertices[2], &all_vertices[3]));
    all_faces[1].set_handle(1);

    // top edge
    all_half_edges.push_back(HalfEdge(&all_vertices[0], &all_vertices[1]));
    all_half_edges[0].set_handle(0);
    all_half_edges.push_back(HalfEdge(&all_vertices[1], &all_vertices[0]));
    all_half_edges[1].set_handle(1);

    // medium edge
    all_half_edges.push_back(HalfEdge(&all_vertices[1], &all_vertices[3]));
    all_half_edges[2].set_handle(2);
    all_half_edges.push_back(HalfEdge(&all_vertices[3], &all_vertices[1]));
    all_half_edges[3].set_handle(3);
    
    // right edge
    all_half_edges.push_back(HalfEdge(&all_vertices[3], &all_vertices[0]));
    all_half_edges[4].set_handle(4);
    all_half_edges.push_back(HalfEdge(&all_vertices[0], &all_vertices[3]));
    all_half_edges[5].set_handle(5);

    // left edge
    all_half_edges.push_back(HalfEdge(&all_vertices[1], &all_vertices[2]));
    all_half_edges[6].set_handle(6);
    all_half_edges.push_back(HalfEdge(&all_vertices[2], &all_vertices[1]));
    all_half_edges[7].set_handle(7);

    // down edge
    all_half_edges.push_back(HalfEdge(&all_vertices[2], &all_vertices[3]));
    all_half_edges[8].set_handle(8);
    all_half_edges.push_back(HalfEdge(&all_vertices[3], &all_vertices[2]));
    all_half_edges[9].set_handle(9);

    // preparing initial vertex
    all_vertices[0].add_incoming_half_edge(1);
    all_vertices[0].add_incoming_half_edge(4);
    all_vertices[0].add_outgoing_half_edge(0);
    all_vertices[0].add_outgoing_half_edge(5);
    
    all_vertices[1].add_incoming_half_edge(0);
    all_vertices[1].add_incoming_half_edge(3);
    all_vertices[1].add_incoming_half_edge(7);
    all_vertices[1].add_outgoing_half_edge(1);
    all_vertices[1].add_outgoing_half_edge(2);
    all_vertices[1].add_outgoing_half_edge(6);
    
    all_vertices[2].add_incoming_half_edge(6);
    all_vertices[2].add_incoming_half_edge(9);
    all_vertices[2].add_outgoing_half_edge(7);
    all_vertices[2].add_outgoing_half_edge(8);

    all_vertices[3].add_incoming_half_edge(2);
    all_vertices[3].add_incoming_half_edge(5);
    all_vertices[3].add_incoming_half_edge(8);
    all_vertices[3].add_outgoing_half_edge(3);
    all_vertices[3].add_outgoing_half_edge(4);
    all_vertices[3].add_outgoing_half_edge(9);

    // preparing initial half edges
    all_half_edges[0].set_parent_face(0);
    all_half_edges[0].set_next_handle(2);
    all_half_edges[0].set_boundary(true);
    all_half_edges[0].set_opposing_half_edge(1);

    all_half_edges[1].set_parent_face(std::numeric_limits<unsigned int>::max());
    all_half_edges[1].set_next_handle(std::numeric_limits<unsigned int>::max());
    all_half_edges[1].set_boundary(true);
    all_half_edges[1].set_opposing_half_edge(0);
    
    all_half_edges[2].set_parent_face(0);
    all_half_edges[2].set_next_handle(4);
    all_half_edges[2].set_boundary(false);
    all_half_edges[2].set_opposing_half_edge(3);
    
    all_half_edges[3].set_parent_face(1);
    all_half_edges[3].set_next_handle(6);
    all_half_edges[3].set_boundary(false);
    all_half_edges[3].set_opposing_half_edge(2);
    
    all_half_edges[4].set_parent_face(0);
    all_half_edges[4].set_next_handle(0);
    all_half_edges[4].set_boundary(true);
    all_half_edges[4].set_opposing_half_edge(5);
    
    all_half_edges[5].set_parent_face(std::numeric_limits<unsigned int>::max());
    all_half_edges[5].set_next_handle(std::numeric_limits<unsigned int>::max());
    all_half_edges[5].set_boundary(true);
    all_half_edges[5].set_opposing_half_edge(4);
    
    all_half_edges[6].set_parent_face(1);
    all_half_edges[6].set_next_handle(8);
    all_half_edges[6].set_boundary(true);
    all_half_edges[6].set_opposing_half_edge(7);
    
    all_half_edges[7].set_parent_face(std::numeric_limits<unsigned int>::max());
    all_half_edges[7].set_next_handle(std::numeric_limits<unsigned int>::max());
    all_half_edges[7].set_boundary(true);
    all_half_edges[7].set_opposing_half_edge(6);
    
    all_half_edges[8].set_parent_face(1);
    all_half_edges[8].set_next_handle(3);
    all_half_edges[8].set_boundary(true);
    all_half_edges[8].set_opposing_half_edge(9);
    
    all_half_edges[9].set_parent_face(std::numeric_limits<unsigned int>::max());
    all_half_edges[9].set_next_handle(std::numeric_limits<unsigned int>::max());
    all_half_edges[9].set_boundary(true);
    all_half_edges[9].set_opposing_half_edge(8);

    // preparing initial faces
    all_faces[0].set_one_half_edge(&all_half_edges[0]);
    all_faces[1].set_one_half_edge(&all_half_edges[8]);

    for (int i = 0; i < points.size(); i++) {
        if (!hasVertex(points[i])) addVertex(points[i]);
    }

    removeVertex(0);
    removeVertex(1);
    removeVertex(2);
    removeVertex(3);

}

bool Mesh::hasVertex(Vertex v) {
    for (int i = 0; i < all_vertices.size(); i++) {
        double diff_x = all_vertices[i].get_x()- v.get_x();
        double diff_y = all_vertices[i].get_y()- v.get_y();
        double dist = diff_x*diff_x+diff_y*diff_y;
        if (dist < 0.0001*0.0001) {
            return true;
        }
    }
    return false;
}

void Mesh::addVertex(Vertex& new_v) {
    // Step 1: Check if the vertex is already in the mesh
    if (hasVertex(new_v)) {
        return;
    }

    // Step 2: Randomly select a half-edge and start the search
    unsigned int init_edge_handle = getRandomFromRange(0, all_half_edges.size() - 1);
    HalfEdge* current_edge = &all_half_edges[init_edge_handle];
    Face* current_face = &all_faces[current_edge->get_parent_face()];

    // Step 3: Search for the containing triangle
    while (!isInsideTriangle(new_v, current_face)) {
        // Find the closest vertex to the new vertex
        Vertex* v1 = current_face->get_vertex_one();
        Vertex* v2 = current_face->get_vertex_two();
        Vertex* v3 = current_face->get_vertex_three();

        // Calculate distances from the new vertex to each of the triangle vertices
        double d1 = distance(v1, &new_v);
        double d2 = distance(v2, &new_v);
        double d3 = distance(v3, &new_v);

        // Choose the closest vertex
        Vertex* closest_vertex;
        if (d1 <= d2 && d1 <= d3) {
            closest_vertex = v1;
        } else if (d2 <= d1 && d2 <= d3) {
            closest_vertex = v2;
        } else {
            closest_vertex = v3;
        }

        // Step to the next face using the half-edge that connects to the closest vertex
        HalfEdge* next_edge = current_edge; // Starting edge
        for (HalfEdge& he : all_half_edges) {
            if (he.get_vertex_one() == closest_vertex && he.get_opposing_half_edge() != std::numeric_limits<unsigned int>::max()) {
                next_edge = &all_half_edges[he.get_opposing_half_edge()];
                break;
            }
        }
        current_edge = next_edge;
        current_face = &all_faces[current_edge->get_parent_face()];
    }

    // Step 4: Add the new vertex to the vertex list
    new_v.set_handle(all_vertices.size());
    all_vertices.push_back(new_v);

    // Step 5: Split the triangle into three new triangles
    Vertex* v1 = current_face->get_vertex_one();
    Vertex* v2 = current_face->get_vertex_two();
    Vertex* v3 = current_face->get_vertex_three();

    // Remove the old face
    // all_faces.erase(std::remove(all_faces.begin(), all_faces.end(), *current_face), all_faces.end());

    // Create three new faces
    Face new_face1(&new_v, v1, v2);
    new_face1.set_handle(all_faces.size());
    all_faces.push_back(new_face1);

    Face new_face2(&new_v, v2, v3);
    new_face2.set_handle(all_faces.size());
    all_faces.push_back(new_face2);

    Face new_face3(&new_v, v3, v1);
    new_face3.set_handle(all_faces.size());
    all_faces.push_back(new_face3);

    // Step 6: Create new half-edges and update connectivity
    HalfEdge he1(&new_v, v1);
    he1.set_handle(all_half_edges.size());
    all_half_edges.push_back(he1);

    HalfEdge he2(&new_v, v2);
    he2.set_handle(all_half_edges.size());
    all_half_edges.push_back(he2);

    HalfEdge he3(&new_v, v3);
    he3.set_handle(all_half_edges.size());
    all_half_edges.push_back(he3);

    // Update the triangle connectivity and complete mesh construction
}


bool Mesh::isInsideTriangle(Vertex& v, Face* face) {
    // Use geometric predicates or cross product-based method to check
    Vertex* v1 = face->get_vertex_one();
    Vertex* v2 = face->get_vertex_two();
    Vertex* v3 = face->get_vertex_three();

    // Implement a method to check if the point `v` is inside the triangle formed by `v1`, `v2`, and `v3`
    double pa[2] = {v1->get_x(), v1->get_y()};
    double pb[2] = {v2->get_x(), v2->get_y()};
    double pc[2] = {v3->get_x(), v3->get_y()};
    double pd[2] = {v.get_x(), v.get_y()};

    // Use an orientation test or other geometric checks
    return (orient2d(pa, pb, pd) > 0 &&
            orient2d(pb, pc, pd) > 0 &&
            orient2d(pc, pa, pd) > 0);
}

double Mesh::distance(Vertex* v1, Vertex* v2) {
    double dx = v1->get_x() - v2->get_x();
    double dy = v1->get_y() - v2->get_y();
    return sqrt(dx * dx + dy * dy);
}