#include <math.h>
#include <stdio.h>

float dist(float x1, float y1, float x2, float y2) {
  return ((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

int main(void) {
  int n_buracos, escapou;
  float x_coelho, y_coelho, x_raposa, y_raposa;
  float x_buraco, y_buraco;
  float d_coelho, d_raposa;

  while (scanf("%d %f %f %f %f", &n_buracos, &x_coelho, &y_coelho, &x_raposa,
               &y_raposa) == 5) {
    escapou = 0;
    for (int i = 1; i <= n_buracos; i++) {
      scanf("%f %f", &x_buraco, &y_buraco);
      if (escapou)
        continue;
      d_coelho = dist(x_coelho, y_coelho, x_buraco, y_buraco);
      d_raposa = dist(x_raposa, y_raposa, x_buraco, y_buraco);

      if (4 * d_coelho < d_raposa) {
        printf("O coelho pode escapar pelo buraco (%.3f,%.3f)\n", x_buraco,
               y_buraco);
        escapou = 1;
        continue;
      }

      if (i == n_buracos) {
        printf("O coelho nao pode escapar\n");
      }
    }
  }
}
