#include <stdio.h>
#include <stdlib.h>

typedef struct
{
   float x;
   float y;
} Point;

int main()
{
   int n, k;

   scanf("%d" "%d", &n, &k);

   Point *points = malloc(n * sizeof *points);

   for (int i = 0; i < n; i++)
   {
      scanf("%f %f", &(points[i].x), &(points[i].y));
   }

#ifdef DEBUG
   printf("n: %d k: %d\n", n, k);
   for (int i = 0; i < n; i++)
   {
      printf("x: %f y: %f\n", points[i].x, points[i].y);
   }
#endif


}
