// Referencia:
// https://en.wikipedia.org/wiki/Sparse_matrix#Compressed_sparse_row_(CSR,_CRS_or_Yale_format)

#include <stdio.h>
#include <stdlib.h>

typedef struct Tup {
  unsigned int i, j, x;
} Tup;

int sort(const void *arg1, const void *arg2) {
  Tup tup1 = *(Tup *)arg1;
  Tup tup2 = *(Tup *)arg2;
  if (tup1.i > tup2.i)
    return 1;
  if (tup1.i < tup2.i)
    return -1;
  if (tup1.j > tup2.j)
    return 1;
  if (tup1.j < tup2.j)
    return -1;
  return 0;
}

int main(void) {
  unsigned int nnz;
  scanf("%d", &nnz);
  Tup *coord = malloc(nnz * sizeof(Tup));
  for (unsigned int i = 0; i < nnz; i++)
    scanf("%d %d %d", &coord[i].i, &coord[i].j, &coord[i].x);
  qsort(coord, nnz, sizeof(Tup), sort);

  unsigned int *values = malloc(nnz * sizeof(unsigned int));
  unsigned int *columns = malloc(nnz * sizeof(unsigned int));
  unsigned int m = coord[nnz - 1].i;
  unsigned int *indexes = malloc((m + 1) * sizeof(unsigned int));

  unsigned int aux = 0;
  for (unsigned int i = 0; i < nnz; i++) {
    values[i] = coord[i].x;
    columns[i] = coord[i].j;
    while (aux <= coord[i].i) {
      indexes[aux] = i;
      aux += 1;
    }
  }
  free(coord);
  while (aux <= m)
    indexes[aux] = nnz;

  unsigned int i, j;
  while (1) {
    scanf("%d %d", &i, &j);
    if (i == -1 && j == -1)
      break;
    printf("(%d,%d) = ", i, j);
    if (indexes[i] == indexes[i + 1])
      printf("0\n");
    else {
      i = indexes[i];
      while (columns[i] != j)
        i+= 1;
      printf("%d\n", values[i]);
    }
  }
  return 0;
  free(values);
  free(columns);
  free(indexes);
}
