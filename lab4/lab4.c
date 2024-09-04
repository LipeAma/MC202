#include <stdio.h>
#include <stdlib.h>

char* extendString(long n, char String[n]) {
	long size = n * sizeof(char);
	char* pNewString = (char*) malloc(size*2);
	for (int i = 0; i < n; i++) {
		pNewString[i] = String[i];
	}
	return pNewString;
}

int main(void) {
	char frase[11] = "1234567890";
	printf("frase:%s | size=%ld\n", frase, sizeof(frase));
	char* fraseGrande = extendString(11, frase);
	printf("frase:%s | size=%ld\n", frase, sizeof(frase));
	printf("frase:%s | size=%ld\n", fraseGrande, sizeof(fraseGrande));

}
