#include <stdbool.h>

#include <math.h>

bool gtkplt_linesegment_intersection(double x1, double y1, double x2, double y2,
                                     double x3, double y3, double x4, double y4,
                                     double *xs, double* ys) {
   double x21 = x2-x1;
   double x43 = x4-x3;
   double x31 = x3-x1;
   double y21 = y2-y1;
   double y43 = y4-y3;
   double y31 = y3-y1;

   double detdenom = x43*y21-x21*y43;
   if (fabs(detdenom) < 10e-10) {
      return false;
   }
   double t = (x21*y31-x31*y21) / detdenom;
   double s = (x43*y31-x31*y43) / detdenom;

   if (t >= 0 && t <= 1 && s >= 0 && s <= 1) {
      *xs = x1+s*x21;
      *ys = y1+s*y21;
      return true;
   } else {
      return false;
   }
}
