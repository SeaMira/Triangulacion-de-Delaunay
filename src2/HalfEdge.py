import sys
import math
from . import config
from .alg import norm, normalize,allclose,dot,cross_product

class Halfedge:

    def __init__(self, next=None, opposite=None, prev=None, vertex=None,
                 facet=None, index=None):
        """Create a halfedge with given index.
        """
        self.opposite = opposite
        self.next = next
        self.prev = prev
        self.vertex = vertex
        self.facet = facet
        self.index = index
        self.deleted = False

    def __eq__(self, other):
        # TODO Test more
        return (self.vertex == other.vertex) and \
               (self.prev.vertex == other.prev.vertex) and \
               (self.index == other.index)

    def __hash__(self):
        return hash(self.opposite) ^ hash(self.next) ^ hash(self.prev) ^ \
                hash(self.vertex) ^ hash(self.facet) ^ hash(self.index) ^ \
                hash((self.opposite, self.next, self.prev, self.vertex,
                    self.facet, self.index))

    def get_angle_normal(self):
        """Calculate the angle between the normals that neighbor the edge.

        Return an angle in radians
        """
        a = self.facet.get_normal()
        b = self.opposite.facet.get_normal()

        dir = [self.vertex.x - self.prev.vertex.x,
               self.vertex.y - self.prev.vertex.y]
        dir = normalize(dir)

        ab = dot(a, b)

        args = ab / (norm(a) * norm(b))

        if allclose(args, 1):
            args = 1
        elif allclose(args, -1):
            args = -1

        assert (args <= 1.0 and args >= -1.0)

        angle = math.acos(args)

        if not (angle % math.pi == 0):
            e = cross_product(a, b)
            e = normalize(e)

            vec = dir
            vec = normalize(vec)

            if (allclose(vec, e)):
                return angle
            else:
                return -angle
        else:
            return 0