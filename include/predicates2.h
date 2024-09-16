#ifndef _PREDICATES
#define _PREDICATES


// Exact initialization for predicates (you can call this if needed)
void exactinit();

// Robust 2D orientation test
double orient2d(double pa[2], double pb[2], double pc[2]);

// Robust 2D incircle test
double incircle(double pa[2], double pb[2], double pc[2], double pd[2]);

#endif