#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <stdbool.h>
bool gtkplt_linesegment_intersection(double x1, double y1, double x2, double y2,
                                     double x3, double y3, double x4, double y4,
                                     double *xs, double* ys);

#endif
