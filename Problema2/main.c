#include <stdio.h>
#include <stdlib.h>

//uc2014230130 Ricardo Tavares

typedef struct
{
   double x;
   double y;
} Point;

int n;
double table[1200][1200];
Point *points;

double max(double num1, double num2)
{
   return (num1 > num2) ? num1 : num2;
}

double bottomUp(int k)
{
   int i, j, l;
   //Fill first 2 rows of the table (k = 0 -> 0, k = 1 -> area(point))
   for (i = 0; i < n; i++)
   {
      table[0][i] = 0;
      table[1][i] = points[i].x * points[i].y;
   }

   //Calculate others
   for (i = 2; i <= k; i++)
   {
      for (j = 0; j < n; j++)
      {
         for (l = j + 1; l < n; l++)
         {
            //Use the diference between the yy's to calculate the area that's not on the intersection of both points
            //Calc max of new k from previous k
            table[i][j] = max(table[i - 1][l] + (points[j].x * (points[j].y - points[l].y)), table[i][j]);
         }
      }
   }

   double maxArea = table[k][0];
   for (i = 0; i < n; i++)
   {
      maxArea = max(maxArea, table[k][i]);
   }

   return maxArea;
}

int main()
{
   int k, i, j;

   scanf("%d""%d",&n, &k);

   points = malloc(n * sizeof *points);

   for (i = 0; i < n; i++)
   {
      scanf("%lf %lf", &(points[i].x), &(points[i].y));
   }

   //Order points by x ascending, creates point order as in the problem description example
   for (i = 0; i < n; i++)
   {
      for (j = i + 1; j < n; j++)
      {
         if (points[i].x > points[j].x)
         {
            Point tmp = points[i];
            points[i] = points[j];
            points[j] = tmp;
         }
      }
   }

#ifdef DEBUG
   printf("n: %d k: %d\n", n, k);
   for (i = 0; i < n; i++)
   {
      printf("x: %f y: %f\n", points[i].x, points[i].y);
   }
#endif

   //print with 12 points of precision
   printf("%.12f\n", bottomUp(k));

   free(points);
   
   return(0);
}