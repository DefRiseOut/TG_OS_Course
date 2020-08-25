#include <stdio.h>
#include <limits.h>
#include <float.h>
 
int main(void) {
  int i;
  float f;
  double d;
  i = INT_MAX;
  f = FLT_MAX;
  d = DBL_MAX;
  printf("%lu %d\n", sizeof(i), i);
  printf("%lu %f\n", sizeof(f), f);
  printf("%lu %f\n", sizeof(d), d);
}
