// MC202 - Lab05
// Felipe Costa Amaral - Ra:249239

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
  double average = 0, stdev = 0;
  int size;
  scanf("%d", &size);
  int n_elementos = ((1 + size) * size) / 2;

  // leiura e calculo da media
  double **matriz = malloc(sizeof(double *) * size);
  for (int i = 0; i < size; i++) {
    matriz[i] = malloc(sizeof(double) * (i + 1));
    for (int j = 0; j <= i; j++) {
      scanf("%lf", &matriz[i][j]);
      average += matriz[i][j];
    }
  }
  average /= n_elementos;

  // calculo do desvio padrao
  for (int i = 0; i < size; i++) {
    for (int j = 0; j <= i; j++) {
      stdev += pow(matriz[i][j] - average, 2.0);
    }
  }
  stdev /= n_elementos;
  stdev = sqrt(stdev);

  // print
  for (int i = 0; i < size; i++) {
    printf("%.4lf", (matriz[i][0] - average) / stdev);
    for (int j = 1; j <= i; j++)
      printf(" %.4lf", (matriz[i][j] - average) / stdev);
    free(matriz[i]);
    printf("\n");
  }
  printf("\n%0.4lf %0.4lf\n", average, stdev);
}
