#include <stdio.h>

int main(void) {
  int x1, y1, x2, y2, n_meteoros, n_meteoros_dentro;
  int x, y;
  for (int n_teste = 1;; n_teste++) {
    // scan da fazenda
    scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
    if (x1 == y1 && x2 == y2 && y1 == x2 && x1 == 0) return 1;

    scanf("%d", &n_meteoros);
    n_meteoros_dentro = 0;

    // detecção dos meteoros
    for (int i = 0; i < n_meteoros; i++) {
      scanf("%d %d", &x, &y);
      if (x1 <= x && x <= x2 && y2 <= y && y <= y1) n_meteoros_dentro++;
    }
    printf("Teste %d\n%d\n\n", n_teste, n_meteoros_dentro);
  }
}