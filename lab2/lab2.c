// MC202 - Lab02
// Felipe Costa Amaral - Ra:249239
// Verifica se coelhos conseguem escapar das raposas

#include <stdio.h>

int main(void)
{
  int n;                // Número de buracos
  int escapou;          // Boleano para interrupção do loop
  float xc, yc, xr, yr; // Coordenadas do coelho e da raposa
  float x, y;           // Coordenadas dos buracos
  float dc, dr;         // Quadrado da distância entre buraco e coelho/raposa

  while (scanf("%d %f %f %f %f", &n, &xc, &yc, &xr, &yr) == 5)
  {
    escapou = 0;
    for (int i = 1; i <= n; i++)
    {
      scanf("%f %f", &x, &y);

      // Se o coelho já escapou, o loop só consumirá o stdin e não realizará
      // as outras operações. A condicional abaixo garante isso.
      if (escapou)
        continue;

      dc = (x - xc) * (x - xc) + (y - yc) * (y - yc);
      dr = (x - xr) * (x - xr) + (y - yr) * (y - yr);

      // O coelho chega primeiro se sua distancia for metade da distancia da raposa.
      // Isso acontece se o quadrado da sua distancia for quatro vezes menor que o
      // quadrado da distancia da raposa. A condicional abaixo verifica isso.
      if (4 * dc < dr)
      {
        printf("O coelho pode escapar pelo buraco (%.3f,%.3f).\n", x, y);
        escapou = 1;
        continue;
      }

      if (i == n)
        printf("O coelho nao pode escapar.\n");
    }
  }
}