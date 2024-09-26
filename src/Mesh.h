#ifndef MESH_H
#define MESH_H

#include "Vertex.h"
#include "HalfEdge.h"
#include "Facet.h"
#include <fstream>
#include <string> 
#include <cstdlib>  // Para random
#include <ctime>    // Para inicializar random

class HalfEdgeMesh {
private:
    std::vector<std::shared_ptr<Vertex>> vertices;
    std::vector<std::shared_ptr<HalfEdge>> halfedges;
    std::vector<std::shared_ptr<Facet>> facets;

public:

    HalfEdgeMesh(double SIZE, int POINTS) {
        // Inicializar los vértices base del contenedor
        vertices.reserve(POINTS+4);
        // Agregar los 4 vértices iniciales
        vertices.push_back(std::make_shared<Vertex>(SIZE, SIZE, 0));
        vertices.push_back(std::make_shared<Vertex>(-SIZE, SIZE, 1));
        vertices.push_back(std::make_shared<Vertex>(-SIZE, -SIZE, 2));
        vertices.push_back(std::make_shared<Vertex>(SIZE, -SIZE, 3));

        // Crear los halfedges
        std::shared_ptr<HalfEdge> halfedge_0 = std::make_shared<HalfEdge>(0, vertices[0]);
        std::shared_ptr<HalfEdge> halfedge_1 = std::make_shared<HalfEdge>(1, vertices[1]);
        std::shared_ptr<HalfEdge> halfedge_2 = std::make_shared<HalfEdge>(2, vertices[1]);
        std::shared_ptr<HalfEdge> halfedge_3 = std::make_shared<HalfEdge>(3, vertices[2]);
        std::shared_ptr<HalfEdge> halfedge_4 = std::make_shared<HalfEdge>(4, vertices[3]);
        std::shared_ptr<HalfEdge> halfedge_5 = std::make_shared<HalfEdge>(5, vertices[3]);

        // Establecer las relaciones next
        halfedge_0->next = halfedge_1;
        halfedge_1->next = halfedge_4;
        halfedge_4->next = halfedge_0;
        halfedge_2->next = halfedge_3;
        halfedge_3->next = halfedge_5;
        halfedge_5->next = halfedge_2;

        // Establecer las relaciones prev
        halfedge_0->prev = halfedge_4;
        halfedge_1->prev = halfedge_0;
        halfedge_4->prev = halfedge_1;
        halfedge_2->prev = halfedge_5;
        halfedge_3->prev = halfedge_2;
        halfedge_5->prev = halfedge_3;

        // Establecer las relaciones opuestas
        halfedge_1->opposite = halfedge_5;
        halfedge_5->opposite = halfedge_1;

        // Establecer facetas en los halfedges
        halfedge_0->facet = std::make_shared<Facet>(vertices[0], vertices[1], vertices[3], 0);
        halfedge_1->facet = halfedge_0->facet;
        halfedge_4->facet = halfedge_0->facet;

        halfedge_2->facet = std::make_shared<Facet>(vertices[1], vertices[2], vertices[3], 1);
        halfedge_3->facet = halfedge_2->facet;
        halfedge_5->facet = halfedge_2->facet;

        // Agregar los halfedges al vector
        halfedges.push_back(halfedge_0);
        halfedges.push_back(halfedge_1);
        halfedges.push_back(halfedge_2);
        halfedges.push_back(halfedge_3);
        halfedges.push_back(halfedge_4);
        halfedges.push_back(halfedge_5);

        // Agregar las facetas al vector
        facets.push_back(halfedge_0->facet);
        facets.push_back(halfedge_2->facet);

    }

    int faces_count() const {
        int count = 0;
        for (const std::shared_ptr<Facet>& face : facets) {
            if (!face->deleted) {
                count++;
            }
        }
        return count;
    }

    int half_edges_count() const {
        int count = 0;
        for (const std::shared_ptr<HalfEdge>& he : halfedges) {
            if (!he->deleted) {
                count++;
            }
        }
        return count;
    }

    int vertices_count() const {
        int count = 0;
        for (const std::shared_ptr<Vertex>& vertex : vertices) {
            if (!vertex->deleted) {
                count++;
            }
        }
        return count;
    }

    void add_vertex(double x, double y) {
        // Crear y agregar un nuevo vértice
        auto new_vertex = std::make_shared<Vertex>(x, y, vertices.size());
        // Verificar si ya existe un vértice con las mismas coordenadas
        // for (const auto& v : vertices) {
        //     double dif_x = new_vertex->x - v->x;
        //     double dif_y = new_vertex->y - v->y;
        //     double dist = dif_x*dif_x+ dif_y*dif_y;
        //     if (dist < 1e-10) {
        //         return; // Vértice ya existe, no hacer nada
        //     }
        // }

        std::shared_ptr<HalfEdge> halfedge_a = locate_triangle(new_vertex);
        if (!halfedge_a) {
            throw std::runtime_error("The vertex lies outside of the mesh.");
        }

        // Get the other halfedges of the triangle
        auto halfedge_b = halfedge_a->next;
        auto halfedge_c = halfedge_b->next;

        // Step 3: Check the orientation of the vertex with respect to halfedge_a
        CGAL::Orientation orientation = point_orientation(new_vertex, halfedge_a);

        // Step 4: Create new faces based on the orientation
        if (orientation == CGAL::COLLINEAR) {
            create_four_new_faces(halfedge_a, halfedge_b, halfedge_c, new_vertex);
        } else {
            create_three_new_faces(halfedge_a, halfedge_b, halfedge_c, new_vertex);
        }
    }

    void create_three_new_faces(std::shared_ptr<HalfEdge>& halfedge_a, 
                                          std::shared_ptr<HalfEdge>& halfedge_b, 
                                          std::shared_ptr<HalfEdge>& halfedge_c, 
                                          std::shared_ptr<Vertex>& new_vertex) {
        // Set the index for the new vertex
        new_vertex->index = vertices.size();
        vertices.push_back(new_vertex);

        // Step 2: Create new halfedges connecting the new vertex with the triangle's vertices
        std::shared_ptr<HalfEdge> new_halfedge_a = std::make_shared<HalfEdge>(halfedges.size(), halfedge_b->vertex);
        std::shared_ptr<HalfEdge> new_halfedge_at = std::make_shared<HalfEdge>(halfedges.size() + 1, new_vertex);
        std::shared_ptr<HalfEdge> new_halfedge_b = std::make_shared<HalfEdge>(halfedges.size() + 2, halfedge_c->vertex);
        std::shared_ptr<HalfEdge> new_halfedge_bt = std::make_shared<HalfEdge>(halfedges.size() + 3, new_vertex);
        std::shared_ptr<HalfEdge> new_halfedge_c = std::make_shared<HalfEdge>(halfedges.size() + 4, halfedge_a->vertex);
        std::shared_ptr<HalfEdge> new_halfedge_ct = std::make_shared<HalfEdge>(halfedges.size() + 5, new_vertex);

        // Update the current halfedges to point to the new halfedges
        halfedge_a->next = new_halfedge_a;
        new_halfedge_a->next = new_halfedge_ct;
        new_halfedge_ct->next = halfedge_a;

        halfedge_b->next = new_halfedge_b;
        new_halfedge_b->next = new_halfedge_at;
        new_halfedge_at->next = halfedge_b;

        halfedge_c->next = new_halfedge_c;
        new_halfedge_c->next = new_halfedge_bt;
        new_halfedge_bt->next = halfedge_c;

        // Update previous halfedges
        halfedge_a->prev = new_halfedge_ct;
        new_halfedge_a->prev = halfedge_a;
        new_halfedge_ct->prev = new_halfedge_a;

        halfedge_b->prev = new_halfedge_at;
        new_halfedge_b->prev = halfedge_b;
        new_halfedge_at->prev = new_halfedge_b;

        halfedge_c->prev = new_halfedge_bt;
        new_halfedge_c->prev = halfedge_c;
        new_halfedge_bt->prev = new_halfedge_c;

        // Set opposites for new halfedges
        new_halfedge_a->opposite = new_halfedge_at;
        new_halfedge_at->opposite = new_halfedge_a;
        new_halfedge_b->opposite = new_halfedge_bt;
        new_halfedge_bt->opposite = new_halfedge_b;
        new_halfedge_c->opposite = new_halfedge_ct;
        new_halfedge_ct->opposite = new_halfedge_c;

        // Step 3: Create new facets
        std::shared_ptr<Facet> new_facet_1 = std::make_shared<Facet>(halfedge_a->vertex, halfedge_b->vertex, new_vertex, facets.size());
        std::shared_ptr<Facet> new_facet_2 = std::make_shared<Facet>(halfedge_b->vertex, halfedge_c->vertex, new_vertex, facets.size()+1);
        std::shared_ptr<Facet> new_facet_3 = std::make_shared<Facet>(halfedge_c->vertex, halfedge_a->vertex, new_vertex, facets.size()+2);

        halfedge_a->facet->deleted = true;
        // Set the halfedges for the new facets
        halfedge_a->facet = new_facet_1;
        new_halfedge_a->facet = new_facet_1;
        new_halfedge_ct->facet = new_facet_1;

        halfedge_b->facet = new_facet_2;
        new_halfedge_b->facet = new_facet_2;
        new_halfedge_at->facet = new_facet_2;

        halfedge_c->facet = new_facet_3;
        new_halfedge_c->facet = new_facet_3;
        new_halfedge_bt->facet = new_facet_3;

        // Set halfedges in the facets
        new_facet_1->halfedge = halfedge_a;
        new_facet_2->halfedge = halfedge_b;
        new_facet_3->halfedge = halfedge_c;

        // Step 4: Add the new halfedges and facets to the mesh
        halfedges.push_back(new_halfedge_a);
        halfedges.push_back(new_halfedge_at);
        halfedges.push_back(new_halfedge_b);
        halfedges.push_back(new_halfedge_bt);
        halfedges.push_back(new_halfedge_c);
        halfedges.push_back(new_halfedge_ct);

        facets.push_back(new_facet_1);
        facets.push_back(new_facet_2);
        facets.push_back(new_facet_3);

        // Step 5: Ensure the Delaunay condition holds
        flip_edges_if_needed(halfedge_a);
        flip_edges_if_needed(halfedge_b);
        flip_edges_if_needed(halfedge_c);
    }

    void create_four_new_faces(std::shared_ptr<HalfEdge>& halfedge_a, 
                                         std::shared_ptr<HalfEdge>& halfedge_b, 
                                         std::shared_ptr<HalfEdge>& halfedge_c, 
                                         std::shared_ptr<Vertex>& new_vertex) {
        // Set the index for the new vertex
        new_vertex->index = vertices.size();
        vertices.push_back(new_vertex);

        // Step 2: Subdivide the triangle into four new triangles
        // Get the halfedges of the containing triangle
        std::shared_ptr<HalfEdge> halfedge_d = halfedge_a->opposite;
        std::shared_ptr<HalfEdge> halfedge_e = halfedge_d->next;
        std::shared_ptr<HalfEdge> halfedge_f = halfedge_e->next;

        // Create new halfedges connecting the new vertex with the vertices of the triangle
        std::shared_ptr<HalfEdge> new_halfedge_a = std::make_shared<HalfEdge>(halfedges.size(), halfedge_a->vertex);
        std::shared_ptr<HalfEdge> new_halfedge_at = std::make_shared<HalfEdge>(halfedges.size() + 1, new_vertex);
        std::shared_ptr<HalfEdge> new_halfedge_b = std::make_shared<HalfEdge>(halfedges.size() + 2, new_vertex);
        std::shared_ptr<HalfEdge> new_halfedge_bt = std::make_shared<HalfEdge>(halfedges.size() + 3, halfedge_d->vertex);
        std::shared_ptr<HalfEdge> new_halfedge_c = std::make_shared<HalfEdge>(halfedges.size() + 4, halfedge_c->vertex);
        std::shared_ptr<HalfEdge> new_halfedge_ct = std::make_shared<HalfEdge>(halfedges.size() + 5, new_vertex);
        std::shared_ptr<HalfEdge> new_halfedge_d = std::make_shared<HalfEdge>(halfedges.size() + 6, halfedge_f->vertex);
        std::shared_ptr<HalfEdge> new_halfedge_dt = std::make_shared<HalfEdge>(halfedges.size() + 7, new_vertex);

        // Update the current halfedges to point to the new halfedges
        new_halfedge_a->next = new_halfedge_ct;
        new_halfedge_ct->next = halfedge_c;
        halfedge_c->next = new_halfedge_a;

        new_halfedge_b->next = halfedge_b;
        halfedge_b->next = new_halfedge_c;
        new_halfedge_c->next = new_halfedge_b;

        new_halfedge_at->next = halfedge_e;
        halfedge_e->next = new_halfedge_d;
        new_halfedge_d->next = new_halfedge_at;

        new_halfedge_bt->next = new_halfedge_dt;
        new_halfedge_dt->next = halfedge_f;
        halfedge_f->next = new_halfedge_bt;

        // Update the previous halfedges
        new_halfedge_a->prev = halfedge_c;
        new_halfedge_ct->prev = new_halfedge_a;
        halfedge_c->prev = new_halfedge_ct;

        new_halfedge_b->prev = new_halfedge_c;
        new_halfedge_c->prev = halfedge_b;
        halfedge_b->prev = new_halfedge_b;

        new_halfedge_at->prev = new_halfedge_d;
        new_halfedge_d->prev = halfedge_e;
        halfedge_e->prev = new_halfedge_at;

        new_halfedge_bt->prev = halfedge_f;
        halfedge_f->prev = new_halfedge_dt;
        new_halfedge_dt->prev = new_halfedge_bt;

        // Set opposites for new halfedges
        new_halfedge_a->opposite = new_halfedge_at;
        new_halfedge_at->opposite = new_halfedge_a;
        new_halfedge_b->opposite = new_halfedge_bt;
        new_halfedge_bt->opposite = new_halfedge_b;
        new_halfedge_c->opposite = new_halfedge_ct;
        new_halfedge_ct->opposite = new_halfedge_c;
        new_halfedge_d->opposite = new_halfedge_dt;
        new_halfedge_dt->opposite = new_halfedge_d;

        // Step 3: Create new facets
        std::shared_ptr<Facet> new_facet_1 = std::make_shared<Facet>(halfedge_b->vertex, halfedge_c->vertex, new_vertex, facets.size());
        std::shared_ptr<Facet> new_facet_2 = std::make_shared<Facet>(halfedge_c->vertex, halfedge_a->vertex, new_vertex, facets.size()+1);
        std::shared_ptr<Facet> new_facet_3 = std::make_shared<Facet>(halfedge_e->vertex, halfedge_f->vertex, new_vertex, facets.size()+2);
        std::shared_ptr<Facet> new_facet_4 = std::make_shared<Facet>(halfedge_f->vertex, halfedge_d->vertex, new_vertex, facets.size()+3);

        // Set the halfedges for the new facets
        halfedge_a->facet->deleted = true;
        halfedge_d->facet->deleted = true;
        halfedge_a->deleted = true;
        halfedge_d->deleted = true;

        new_halfedge_b->facet = new_facet_1;
        halfedge_b->facet = new_facet_1;
        new_halfedge_c->facet = new_facet_1;

        halfedge_c->facet = new_facet_2;
        new_halfedge_a->facet = new_facet_2;
        new_halfedge_ct->facet = new_facet_2;

        halfedge_e->facet = new_facet_3;
        new_halfedge_d->facet = new_facet_3;
        new_halfedge_at->facet = new_facet_3;

        halfedge_f->facet = new_facet_4;
        new_halfedge_dt->facet = new_facet_4;
        new_halfedge_bt->facet = new_facet_4;

        // Set halfedges in the facets
        new_facet_1->halfedge = halfedge_b;
        new_facet_2->halfedge = halfedge_c;
        new_facet_3->halfedge = halfedge_e;
        new_facet_4->halfedge = halfedge_f;

        // Step 4: Add the new halfedges and facets to the mesh
        halfedges.push_back(new_halfedge_a);
        halfedges.push_back(new_halfedge_at);
        halfedges.push_back(new_halfedge_b);
        halfedges.push_back(new_halfedge_bt);
        halfedges.push_back(new_halfedge_c);
        halfedges.push_back(new_halfedge_ct);
        halfedges.push_back(new_halfedge_d);
        halfedges.push_back(new_halfedge_dt);

        facets.push_back(new_facet_1);
        facets.push_back(new_facet_2);
        facets.push_back(new_facet_3);
        facets.push_back(new_facet_4);

        // Step 5: Ensure the Delaunay condition holds
        flip_edges_if_needed(halfedge_b);
        flip_edges_if_needed(halfedge_c);
        flip_edges_if_needed(halfedge_e);
        flip_edges_if_needed(halfedge_f);
    }

    void flip_edge(std::shared_ptr<HalfEdge>& halfedge) {
        // Obtener el halfedge opuesto
        std::shared_ptr<HalfEdge> he_opposite = halfedge->opposite;

        // Obtener los halfedges alrededor de los triángulos involucrados
        std::shared_ptr<HalfEdge> next_1 = halfedge->next;
        std::shared_ptr<HalfEdge> prev_1 = halfedge->prev;

        std::shared_ptr<HalfEdge> next_2 = he_opposite->next;
        std::shared_ptr<HalfEdge> prev_2 = he_opposite->prev;

        // Actualizar los vértices asociados a los halfedges después del flip
        halfedge->vertex = prev_2->vertex;
        he_opposite->vertex = prev_1->vertex;

        // Actualizar los enlaces next en los halfedges
        halfedge->next = prev_1;
        he_opposite->next = prev_2;
        prev_1->next = next_2;
        next_2->next = halfedge;
        prev_2->next = next_1;
        next_1->next = he_opposite;

        // Actualizar los enlaces prev en los halfedges
        halfedge->prev = next_2;
        he_opposite->prev = next_1;
        prev_1->prev = halfedge;
        next_2->prev = prev_1;
        prev_2->prev = he_opposite;
        next_1->prev = prev_2;

        // Obtener las facetas involucradas en el flip
        std::shared_ptr<Facet> facet_1 = halfedge->facet;
        std::shared_ptr<Facet> facet_2 = he_opposite->facet;

        // Actualizar las facetas con los nuevos vértices y halfedges
        prev_1->facet = facet_1;
        next_2->facet = facet_1;
        prev_2->facet = facet_2;
        next_1->facet = facet_2;

        facet_1->a = halfedge->vertex;
        facet_1->b = prev_1->vertex;
        facet_1->c = next_2->vertex;
        facet_1->halfedge = halfedge;

        facet_2->a = he_opposite->vertex;
        facet_2->b = prev_2->vertex;
        facet_2->c = next_1->vertex;
        facet_2->halfedge = he_opposite;

        // Después del flip, verificar si necesitamos flipar más aristas
        flip_edges_if_needed(prev_2);
        flip_edges_if_needed(next_2);
    }

    
    void flip_edges_if_needed(std::shared_ptr<HalfEdge> halfedge) {
    // Verificar si ambos halfedges tienen facetas asociadas y si existe un halfedge opuesto
    if (halfedge->facet == nullptr || halfedge->opposite == nullptr) {
        return;  // No hay triángulo que revisar, no se puede hacer flip
    }

    // Obtener el halfedge opuesto y los triángulos involucrados
    std::shared_ptr<HalfEdge> he_opposite = halfedge->opposite;

    // Vértices del triángulo de 'halfedge'
    std::shared_ptr<Vertex> v1 = halfedge->vertex;
    std::shared_ptr<Vertex> v2 = halfedge->next->vertex;
    std::shared_ptr<Vertex> v3 = halfedge->prev->vertex;

    // Vértice opuesto del triángulo vecino
    std::shared_ptr<Vertex> v_opposite = he_opposite->prev->vertex;

    // Revisar si el vértice opuesto está dentro del circuncírculo del triángulo de 'halfedge'
    if (is_point_in_circumcircle(v_opposite, v1, v2, v3)) {
        // No se cumple la condición de Delaunay, entonces hacemos flip
        flip_edge(halfedge);
    }
}

    bool is_point_in_circumcircle(const std::shared_ptr<Vertex>& v_opposite, 
                                const std::shared_ptr<Vertex>& v1, 
                                const std::shared_ptr<Vertex>& v2, 
                                const std::shared_ptr<Vertex>& v3) {
        // Convertir los vértices a puntos CGAL
        Point p1 = v1->to_cgal_point();
        Point p2 = v2->to_cgal_point();
        Point p3 = v3->to_cgal_point();
        Point p_opposite = v_opposite->to_cgal_point();

        // Usar el predicado de CGAL para determinar si el punto está dentro del circuncírculo
        CGAL::Oriented_side side = CGAL::side_of_oriented_circle(p1, p2, p3, p_opposite);

        // Si el punto está dentro del circuncírculo, devolver true
        return (side == CGAL::ON_POSITIVE_SIDE);
    }

    CGAL::Orientation point_orientation(const std::shared_ptr<Vertex>& vertex, const std::shared_ptr<HalfEdge>& halfedge) {
        // Obtener los puntos CGAL para los dos vértices de la halfedge
        Point p1 = halfedge->vertex->to_cgal_point();
        Point p2 = halfedge->next->vertex->to_cgal_point();
        Point p = vertex->to_cgal_point();

        // Usar CGAL para determinar la orientación
        CGAL::Orientation orientation = CGAL::orientation(p1, p2, p);

        return orientation;
    }

    bool is_point_in_triangle(const std::shared_ptr<Vertex>& vertex, const std::shared_ptr<Facet>& facet) {
        // Obtener los puntos CGAL para los tres vértices del triángulo
        Point p1 = facet->a->to_cgal_point();
        Point p2 = facet->b->to_cgal_point();
        Point p3 = facet->c->to_cgal_point();
        Point p = vertex->to_cgal_point();

        // Verificar que el punto esté a la izquierda de los tres lados del triángulo
        return (CGAL::orientation(p1, p2, p) == CGAL::LEFT_TURN &&
                CGAL::orientation(p2, p3, p) == CGAL::LEFT_TURN &&
                CGAL::orientation(p3, p1, p) == CGAL::LEFT_TURN);
    }


    bool on_half_edge(const std::shared_ptr<Vertex>& v, const std::shared_ptr<HalfEdge>& halfedge) {
        // Obtener el halfedge opuesto
        std::shared_ptr<HalfEdge> he_opposite = halfedge->opposite;

        // Obtener los vértices de la halfedge y su opuesto
        std::shared_ptr<Vertex> v0 = halfedge->vertex;
        std::shared_ptr<Vertex> v1 = he_opposite->vertex;

        // Verificar las condiciones para la coordenada x
        bool inx_1;
        if (v0->x < v1->x) {
            inx_1 = (v0->x < v->x && v->x < v1->x);
        } else if (v0->x > v1->x) {
            inx_1 = (v1->x < v->x && v->x < v0->x);
        } else {
            inx_1 = (v1->x == v->x);
        }

        // Verificar las condiciones para la coordenada y
        bool iny_1;
        if (v0->y < v1->y) {
            iny_1 = (v0->y < v->y && v->y < v1->y);
        } else if (v0->y > v1->y) {
            iny_1 = (v1->y < v->y && v->y < v0->y);
        } else {
            iny_1 = (v1->y == v->y);
        }

        // El punto está en la halfedge si está dentro de ambos rangos
        return inx_1 && iny_1;
    }

    std::shared_ptr<HalfEdge> locate_triangle(const std::shared_ptr<Vertex>& vertex) {
        // Step 1: Empezar con una halfedge aleatoria
        int random_index = std::rand() % halfedges.size();  // Elegir un índice aleatorio
        std::shared_ptr<HalfEdge> current_halfedge = halfedges[random_index];

        while (true) {
            // Obtener el triángulo (facet) asociado a este halfedge
            std::shared_ptr<Facet> facet = current_halfedge->facet;

            // Verificar si el punto está dentro del triángulo actual
            // if (is_point_in_triangle(vertex, facet)) {
            //     return current_halfedge;
            // }

            // Verificar la orientación con respecto a la halfedge actual
            CGAL::Orientation orientation = point_orientation(vertex, current_halfedge);

            if (orientation == CGAL::COLLINEAR && on_half_edge(vertex, current_halfedge)) {
                // El punto está exactamente en esta halfedge, devolver la halfedge actual
                return current_halfedge;
            } else if (orientation == CGAL::RIGHT_TURN) {
                // Moverse a la halfedge opuesta y repetir
                current_halfedge = current_halfedge->opposite;
            } else {
                // Verificar la siguiente halfedge en el triángulo actual
                std::shared_ptr<HalfEdge> next_halfedge = current_halfedge->next;
                CGAL::Orientation next_orientation = point_orientation(vertex, next_halfedge);

                if (next_orientation == CGAL::COLLINEAR && on_half_edge(vertex, next_halfedge)) {
                    return next_halfedge;
                } else if (next_orientation == CGAL::RIGHT_TURN) {
                    current_halfedge = next_halfedge->opposite;
                } else {
                    // Si no está en ninguna, moverse a la siguiente de la siguiente halfedge
                    current_halfedge = next_halfedge->next;
                    next_orientation = point_orientation(vertex, current_halfedge);
                    if (next_orientation == CGAL::COLLINEAR) {
                        return current_halfedge;
                    } else if (next_orientation == CGAL::RIGHT_TURN) {
                        current_halfedge = current_halfedge->opposite;
                    } else return current_halfedge;
                }
            }
        }
    }

    void write_to_off(const std::string& filename) {
        std::ofstream file(filename);

        if (!file.is_open()) {
            throw std::runtime_error("Cannot open the file for writing");
        }

        // Escribir el encabezado OFF
        file << "OFF\n";

        // Número de vértices, caras y aristas
        int num_vertices = vertices_count();  // asume que tienes esta función
        int num_faces = faces_count();        // asume que tienes esta función
        int num_edges = half_edges_count() / 2;  // Cada arista tiene dos halfedges
        file << num_vertices << " " << num_faces << " " << num_edges << "\n";

        // Escribir los vértices
        for (const auto& v : vertices) {
            if (!v->deleted) {
                file << v->x << " " << v->y << " 0.0\n";  // 2D triangulación, z = 0
            }
        }

        // Escribir las caras (facetas)
        for (const auto& facet : facets) {
            if (!facet->deleted) {
                // Cada faceta es un triángulo, así que tiene 3 vértices
                file << "3 " 
                    << facet->a->index << " "
                    << facet->b->index << " "
                    << facet->c->index << "\n";
            }
        }

        file.close();
    }

};

#endif // MESH_H