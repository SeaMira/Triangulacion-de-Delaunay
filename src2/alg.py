from . import config
import math
from functools import reduce

def allclose(v1, v2):
    """Compare if v1 and v2 are close

    v1, v2 - any numerical type or list/tuple of numerical types

    Return bool if vectors are close, up to some epsilon specified in config.py
    """

    v1 = make_iterable(v1)
    v2 = make_iterable(v2)

    elementwise_compare = map(
        (lambda x, y: abs(x - y) < config.EPSILON), v1, v2)
    return reduce((lambda x, y: x and y), elementwise_compare)


def make_iterable(obj):
    """Check if obj is iterable, if not return an iterable with obj inside it.
    Otherwise just return obj.

    obj - any type

    Return an iterable
    """
    try:
        iter(obj)
    except:
        return [obj]
    else:
        return obj


def dot(v1, v2):
    """Dot product(inner product) of v1 and v2

    v1, v2 - python list

    Return v1 dot v2
    """
    elementwise_multiply = map((lambda x, y: x * y), v1, v2)
    return reduce((lambda x, y: x + y), elementwise_multiply)


def norm(vec):
    """ Return the Euclidean norm of a 3d vector.

    vec - a 3d vector expressed as a list of 3 floats.
    """
    return math.sqrt(reduce((lambda x, y: x + y * y), vec, 0.0))


def normalize(vec):
    """Normalize a vector

    vec - python list

    Return normalized vector
    """
    if norm(vec) < 1e-6:
        return [0 for i in xrange(len(vec))]
    return map(lambda x: x / norm(vec), vec)


def cross_product(v1, v2):
    """ Return the cross product of v1, v2.

    v1, v2 - 3d vector expressed as a list of 3 floats.
    """
    x3 = v1[1] * v2[2] - v2[1] * v1[2]
    y3 = -(v1[0] * v2[2] - v2[0] * v1[2])
    z3 = v1[0] * v2[1] - v2[0] * v1[1]
    return [x3, y3, z3]

def create_vector(p1, p2):
    """Contruct a vector going from p1 to p2.

    p1, p2 - python list wth coordinates [x,y,z].

    Return a list [x,y,z] for the coordinates of vector
    """
    return map((lambda x,y: x-y), p2, p1)

def is_point_in_circumcircle(p, a, b, c):
    """
    Verifica si el punto `p` está dentro del circuncírculo formado por los puntos `a`, `b` y `c`.
    """
    # Convertir las coordenadas de los puntos a una matriz
    mat = [
        [a.x - p.x, a.y - p.y, (a.x - p.x)**2 + (a.y - p.y)**2],
        [b.x - p.x, b.y - p.y, (b.x - p.x)**2 + (b.y - p.y)**2],
        [c.x - p.x, c.y - p.y, (c.x - p.x)**2 + (c.y - p.y)**2]
    ]
    
    # Calcular el determinante de la matriz 3x3
    det = (mat[0][0] * (mat[1][1] * mat[2][2] - mat[2][1] * mat[1][2]) -
           mat[0][1] * (mat[1][0] * mat[2][2] - mat[2][0] * mat[1][2]) +
           mat[0][2] * (mat[1][0] * mat[2][1] - mat[2][0] * mat[1][1]))
    
    return det > 0  # Si el determinante es positivo, el punto está dentro del circuncírculo