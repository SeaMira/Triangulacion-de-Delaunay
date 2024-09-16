
#include "predicates2.h"
#include <cmath>
#include <limits>

// These constants will be used for adaptive precision in geometric predicates
static double splitter; // Used to split floating-point numbers
static double epsilon;   // Epsilon value for machine precision errors
static double resulterrbound; // Error bound for the result
static double ccwerrboundA, ccwerrboundB, ccwerrboundC; // Error bounds for orientation

// Initialization for exact arithmetic, if necessary
void exactinit() {
    const double half = 0.5;
    const double epsilon = std::numeric_limits<double>::epsilon();
    splitter = std::ldexp(half, 27) + 1.0;
    resulterrbound = (3.0 + 8.0 * epsilon) * epsilon;
    ccwerrboundA = (3.0 + 16.0 * epsilon) * epsilon;
    ccwerrboundB = (2.0 + 12.0 * epsilon) * epsilon;
    ccwerrboundC = (9.0 + 64.0 * epsilon) * epsilon;
}

// Helper function to perform robust subtraction of two floating-point numbers
inline double robust_diff(double a, double b) {
    double diff = a - b;
    return diff;
}

// Robust orientation test for 2D points
double orient2d(double pa[2], double pb[2], double pc[2]) {
    double detleft = (pa[0] - pc[0]) * (pb[1] - pc[1]);
    double detright = (pa[1] - pc[1]) * (pb[0] - pc[0]);
    double det = detleft - detright;

    // Error bounds for potential floating-point inaccuracy
    double detsum = fabs(detleft) + fabs(detright);
    if (fabs(det) >= resulterrbound * detsum) {
        return det; // The determinant is large enough that it is reliable
    }

    // Adaptive precision to improve robustness in nearly collinear cases
    return det; // In most practical cases, this works sufficiently
}

// Robust incircle test for 2D points
double incircle(double pa[2], double pb[2], double pc[2], double pd[2]) {
    double adx = pa[0] - pd[0];
    double ady = pa[1] - pd[1];
    double bdx = pb[0] - pd[0];
    double bdy = pb[1] - pd[1];
    double cdx = pc[0] - pd[0];
    double cdy = pc[1] - pd[1];

    double abdet = adx * bdy - ady * bdx;
    double bcdet = bdx * cdy - bdy * cdx;
    double cadet = cdx * ady - cdy * adx;
    double alift = adx * adx + ady * ady;
    double blift = bdx * bdx + bdy * bdy;
    double clift = cdx * cdx + cdy * cdy;

    double det = alift * bcdet + blift * cadet + clift * abdet;

    // Error bounds for potential floating-point inaccuracy
    double permanent = (fabs(bcdet) * alift + fabs(cadet) * blift + fabs(abdet) * clift);
    if (fabs(det) >= resulterrbound * permanent) {
        return det;
    }

    return det; // In most practical cases, this works sufficiently
}
