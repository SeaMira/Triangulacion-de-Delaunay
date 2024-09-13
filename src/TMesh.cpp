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
    unsigned int init_edge_handle = getRandomInt(0, all_half_edges.size() - 1);
    HalfEdge* current_edge = &all_half_edges[init_edge_handle];
    Face* current_face = &all_faces[current_edge->get_parent_face()];

    bool he1_on = isOnSegment(current_edge, &new_v);
    bool he2_on = isOnSegment(next(current_edge), &new_v);
    bool he3_on = isOnSegment(next(next(current_edge)), &new_v);
    // Step 3: Search for the containing triangle
    while (!isInsideTriangle(new_v, current_face) && !he1_on && !he2_on && !he3_on) {
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
        he1_on = isOnSegment(current_edge, &new_v);
        he2_on = isOnSegment(next(current_edge), &new_v);
        he3_on = isOnSegment(next(next(current_edge)), &new_v);
    }

    if (he1_on) {

    } else if (he2_on) {

    } else if (he3_on) {

    } else addingVertexInT(new_v, current_face);
}

HalfEdge* Mesh::next(HalfEdge* current) {
    return &all_half_edges[current->next_handle()];
}

// Create new half edge
HalfEdge* Mesh::addHalfEdge(Vertex*v1, Vertex*v2) {
    HalfEdge he1(v1, v2);
    he1.set_handle(all_half_edges.size());
    all_half_edges.push_back(he1);
    return &all_half_edges[all_half_edges.size()-1];
}

// Create new face
Face* Mesh::addFace(Vertex*v1, Vertex*v2, Vertex*v3) {
    Face new_face1(v1, v2, v3);
    new_face1.set_handle(all_faces.size());
    all_faces.push_back(new_face1);
    return &all_faces[all_faces.size() - 1];
}


void Mesh::addingVertexInT(Vertex& new_v, Face* current_face) {
    // Step 4: Add the new vertex to the vertex list
    new_v.set_handle(all_vertices.size());
    all_vertices.push_back(new_v);

    // Step 5: Split the triangle into three new triangles
    Vertex* nv = &all_vertices[all_vertices.size()-1];
    Vertex* v1 = current_face->get_vertex_one();
    Vertex* v2 = current_face->get_vertex_two();
    Vertex* v3 = current_face->get_vertex_three();

    // Obtain the original half-edges of the current face
    HalfEdge* original_he1 = current_face->get_one_half_edge();
    HalfEdge* original_he2 = &all_half_edges[original_he1->next_handle()];
    HalfEdge* original_he3 = &all_half_edges[original_he2->next_handle()];

    if (original_he1->get_vertex_one() == v2) {
        HalfEdge* temp = original_he1;
        original_he1 = original_he3;
        original_he3 = original_he2;
        original_he2 = temp;
    } else if (original_he1->get_vertex_one() == v3) {
        HalfEdge* temp = original_he1;
        original_he1 = original_he2;
        original_he2 = original_he3;
        original_he3 = temp;
    }

    // Remove the old face
    // You can either mark it as removed or actually erase it from the list
    // all_faces.erase(std::remove(all_faces.begin(), all_faces.end(), *current_face), all_faces.end());
    
    // Alternatively, mark it as invalid if needed
    current_face->markDeleted();

    // Create three new faces
    Face* new_face1 = addFace(&new_v, v1, v2);
    Face* new_face2 = addFace(&new_v, v2, v3);
    Face* new_face3 = addFace(&new_v, v3, v1);

    // Step 6: Create new half-edges and update connectivity
    HalfEdge* he1 = addHalfEdge(&new_v, v1);
    HalfEdge* he1t = addHalfEdge(v1, &new_v);
    HalfEdge* he2 = addHalfEdge(&new_v, v2);
    HalfEdge* he2t = addHalfEdge(v2, &new_v);
    HalfEdge* he3 = addHalfEdge(&new_v, v3);
    HalfEdge* he3t = addHalfEdge(v3, &new_v);


    // Update the connectivity between half-edges and faces if necessary
    // For each new face, update the half-edge handles and set the parent faces
    he1->set_parent_face(new_face1->handle());
    he1t->set_parent_face(new_face3->handle());
    he2->set_parent_face(new_face2->handle());
    he2t->set_parent_face(new_face1->handle());
    he3->set_parent_face(new_face3->handle());
    he3t->set_parent_face(new_face2->handle());
    original_he1->set_parent_face(new_face1->handle());
    original_he2->set_parent_face(new_face2->handle());
    original_he3->set_parent_face(new_face3->handle());
    
    he1->set_opposing_half_edge(he1t->handle());
    he1t->set_opposing_half_edge(he1->handle());
    he2->set_opposing_half_edge(he2t->handle());
    he2t->set_opposing_half_edge(he2->handle());
    he3->set_opposing_half_edge(he3t->handle());
    he3t->set_opposing_half_edge(he3->handle());
    
    he1->set_next_handle(original_he1->handle());
    he1t->set_next_handle(he3->handle());
    he2->set_next_handle(original_he2->handle());
    he2t->set_next_handle(he1->handle());
    he3->set_next_handle(original_he3->handle());
    he3t->set_next_handle(he2->handle());
    original_he1->set_next_handle(he2t->handle());
    original_he2->set_next_handle(he3t->handle());
    original_he3->set_next_handle(he1t->handle());

    // updating vertices
    nv->add_incoming_half_edge(he1t->handle());
    nv->add_incoming_half_edge(he2t->handle());
    nv->add_incoming_half_edge(he3t->handle());
    nv->add_outgoing_half_edge(he1->handle());
    nv->add_outgoing_half_edge(he2->handle());
    nv->add_outgoing_half_edge(he3->handle());

    v1->add_incoming_half_edge(he1->handle());
    v1->add_outgoing_half_edge(he1t->handle());
    v2->add_incoming_half_edge(he2->handle());
    v2->add_outgoing_half_edge(he2t->handle());
    v3->add_incoming_half_edge(he3->handle());
    v3->add_outgoing_half_edge(he3t->handle());

    // Optionally, you can set the next and previous half-edges to complete the cycle in each face
    new_face1->set_one_half_edge(he1);
    new_face2->set_one_half_edge(he2);
    new_face3->set_one_half_edge(he3);
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

bool Mesh::isOnSegment(HalfEdge* edge, Vertex* vertex) {
    // Get the vertices of the half-edge
    Vertex* v1 = edge->get_vertex_one();  // Start of the edge
    Vertex* v2 = edge->get_vertex_two();  // End of the edge
    
    // Coordinates of the segment's endpoints and the point to test
    double pa[2] = {v1->get_x(), v1->get_y()};
    double pb[2] = {v2->get_x(), v2->get_y()};
    double pd[2] = {vertex->get_x(), vertex->get_y()};
    
    // Check if the points are collinear using orient2d
    double orientation = orient2d(pa, pb, pd);
    
    // If orientation is not zero, the point is not on the line
    if (orientation != 0) {
        return false;
    }

    // Check if the point is within the bounds of the segment
    double min_x = std::min(pa[0], pb[0]);
    double max_x = std::max(pa[0], pb[0]);
    double min_y = std::min(pa[1], pb[1]);
    double max_y = std::max(pa[1], pb[1]);

    // Return true if the point lies within the bounding box of the segment
    return (pd[0] >= min_x && pd[0] <= max_x && pd[1] >= min_y && pd[1] <= max_y);
}
