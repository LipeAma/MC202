// MC202 - Lab03
// Felipe Costa Amaral - Ra:249239
// Atualiza verifica máximo de arrays com truque √n

#include <stdio.h>
#include <math.h>

int main(void) {
    int n;  // tamanho do array de input
    scanf("%d", &n);

    int r;  // Tamanho máximo da fatia utilizada no truque
    r = ceil(sqrt((double) n));

    int S[n];   // Input
    int M[r];   // Maior elemento de cada uma das r fatias utilizadas no truque

    // Leitura do array inicial e calcula os maximos de cada fatia
    for (int i = 0; i < n; i++) {
        scanf("%d", &S[i]);
        if (i % r == 0 || S[i] > M[i / r])
            M[i / r] = S[i];
    }

    char action; // Ação a ser realizada
    int a, b; // Parâmetros da ação que será realizada 

    while (scanf(" %c %d %d", &action, &a, &b) == 3) {
        
        if (action == 'a') {
            int temp1, temp2;
            temp1 = a / r;
            temp2 = S[a];
            S[a] = b;
	    // Testa se o número substituido era o maior daquela fatia,
	    // se for, calcula novamente o maximo da fatia
            if (M[temp1] <= b)
                M[temp1] = b;
            else if (M[temp1] == temp2) {
                temp2 = a - a % r + r;
                M[temp1] = 0;
                for (int i = a - a % r; i < temp2 && i < n; i++) {
                    if (M[temp1] < S[i]) M[temp1] = S[i];
                }
            }
        }

        if (action == 'm') {
            int max = 0;
            for (int i = a; i <= b; i++) {
                if (i % r == 0 && i + r - 1 <= b) {
                    if (max < M[i / r])
                        max = M[i / r];
                    i = (i/r+1)*r-1;
                    continue;
                }

                if (max < S[i])
                    max = S[i];
            }
            printf("%d\n", max);
        }
    }
}
