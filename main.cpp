#include <iostream>
#include "TMesh.h"
// #include "TVertex.h"

int main() {
    // Create a vector of points (vertices) to initialize the mesh
    std::vector<Vertex> points;
    points.push_back(Vertex(0.0, 0.0));
    points.push_back(Vertex(1.0, 0.0));
    points.push_back(Vertex(0.5, 1.0));

    // Initialize the mesh with the given points
    Mesh mesh(points);
    std::cout << "Mesh initialized" << std::endl;
    // Add another vertex to test the addVertex functionality
    Vertex new_v(0.5, 0.5);
    mesh.addVertex(new_v);

    // Display the vertices and faces of the mesh
    std::cout << "Vertices in the mesh: \n";
    for (int i = 0; i < mesh.getAllVertices().size(); ++i) {
        Vertex v = mesh.getAllVertices()[i];
        std::cout << "Vertex " << i << ": (" << v.get_x() << ", " << v.get_y() << ")\n";
    }

    std::cout << "\nFaces in the mesh: \n";
    for (int i = 0; i < mesh.getAllFaces().size(); ++i) {
        Face f = mesh.getAllFaces()[i];
        if (!f.is_deleted()) {
            auto vertices = f.get_vertices();
            std::cout << "Face " << i << ": "
                      << "(" << std::get<0>(vertices)->get_x() << ", " << std::get<0>(vertices)->get_y() << "), "
                      << "(" << std::get<1>(vertices)->get_x() << ", " << std::get<1>(vertices)->get_y() << "), "
                      << "(" << std::get<2>(vertices)->get_x() << ", " << std::get<2>(vertices)->get_y() << ")\n";
        }
    }

    return 0;
}