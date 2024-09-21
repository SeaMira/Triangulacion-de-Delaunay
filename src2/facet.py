from .alg import normalize, cross_product
from .HalfEdge import Halfedge

class Facet:

    def __init__(self, a=-1, b=-1, c=-1, index=None, halfedge=None):
        """Create a facet with the given index with three vertices.

        a, b, c - indices for the vertices in the facet, counter clockwise.
        index - index of facet in the mesh
        halfedge - a Halfedge that belongs to the facet
        """
        self.a = a
        self.b = b
        self.c = c
        self.index = index
        # halfedge going ccw around this facet.
        self.halfedge = halfedge
        self.deleted = False

    def __eq__(self, other):
        return self.a == other.a and self.b == other.b and self.c == other.c \
            and self.index == other.index and self.halfedge == other.halfedge

    def __hash__(self):
        return hash(self.halfedge) ^ hash(self.a) ^ hash(self.b) ^ \
            hash(self.c) ^ hash(self.index) ^ \
            hash((self.halfedges, self.a, self.b, self.c, self.index))

    def get_normal(self):
        """Calculate the normal of facet

        Return a python list that contains the normal
        """
        vertex_a = [self.halfedge.vertex.x, self.halfedge.vertex.y]

        vertex_b = [self.halfedge.next.vertex.x, self.halfedge.next.vertex.y]

        vertex_c = [self.halfedge.prev.vertex.x, self.halfedge.prev.vertex.y]

        # create edge 1 with vector difference
        edge1 = [u - v for u, v in zip(vertex_b, vertex_a)]
        edge1 = normalize(edge1)
        # create edge 2 ...
        edge2 = [u - v for u, v in zip(vertex_c, vertex_b)]
        edge2 = normalize(edge2)

        # cross product
        normal = cross_product(edge1, edge2)

        normal = normalize(normal)

        return normal