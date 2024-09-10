#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define quad(x) x**x

int main(void) {
  double media = 0, stdev = 0;
  int ordem;
  scanf("%d", &ordem);
  int n_elementos = ((1+ordem)*ordem)/2;

  double** matriz = (double**)malloc(sizeof(double**) * ordem);
  for (int i = 0; i<ordem; i++) {
    matriz[i] = (double*)malloc(sizeof(double)*(i+1));
    for (int j = 0; j <= i; j++) {
      scanf("%lf", &matriz[i][j]);
      media += matriz[i][j]
    }
  }
  media /= n_elementos;

  for (int i = 0; i<ordem; i++) {
    for (int j = 0; j <= i; j++)
      stdev += quad(matriz[i][j]-media);
    stdev /= n_elementos;
    stdev = sqrt(stdev);
  }

  for (int i = 0; i<ordem; i++) {
    for (int j = 0; j <= i; j++)
      printf("%lf ", (matriz[i][j]-media)/stdev);
    free(matriz[i]);
    printf("\n");
  }
  printf("\n%lf %lf\n", &media, &stdev);
}
