#include <stdio.h>
#include <stdlib.h>

int main (int argc, char **argv) {
  int arr[16], a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p;
  printf("Enter the numbers from 1 to 16 in any order: ");
  scanf("%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d", &a, &b, &c, &d, &e, &f, &g, &h, &i, &j, &k, &l, &m, &n, &o, &p);
  printf("\n");
  printf("%d %d %d %d\n", a, b, c, d);
  printf("%d %d %d %d\n", e, f, g, h);
  printf("%d %d %d %d\n", i, j, k, l);
  printf("%d %d %d %d\n", m, n, o, p);
  printf("\n");
  int r1Sum = a + b + c + d;
  int r2Sum = e + f + g + h;
  int r3Sum = i + j + k + l;
  int r4Sum = m + n + o + p;
  printf("Row Sums: %d %d %d %d\n", r1Sum, r2Sum, r3Sum, r4Sum);
  int c1Sum = a + e + i + m;
  int c2Sum = b + f + j + n;
  int c3Sum = c + g + k + o;
  int c4Sum = d + h + l + p;
  printf("Column Sums: %d %d %d %d\n", c1Sum, c2Sum, c3Sum, c4Sum);
  int d1Sum = a + f + k + p;
  int d2Sum = d + g + j + m;
  printf("Diagonal Sums: %d %d\n", d1Sum, d2Sum);
}
