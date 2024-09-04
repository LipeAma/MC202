#include <stdio.h>

int main(void) {
	printf("char: min=1 | actual=%ld\n", sizeof(char));
	printf("unsigned char: min=1 | actual=%ld\n", sizeof(unsigned char));
	
	printf("short: min=2 | actual=%ld\n", sizeof(short));
	printf("unsigned short: min=2 | actual=%ld\n", sizeof(unsigned short));
	
	printf("int: min=2 | actual=%ld\n", sizeof(int));
	printf("unsigned int: min=2 | actual=%ld\n", sizeof(unsigned));
	printf("long: min=4 | actual=%ld\n", sizeof(long));
	printf("unsigned long: min=4 | actual=%ld\n", sizeof(unsigned long));
	printf("long long: min=8 | actual=%ld\n", sizeof(long long));
	printf("unsigned long long: min=8 | actual=%ld\n", sizeof(unsigned long long));

	printf("float: min=4 | actual=%ld\n", sizeof(float));
	printf("double: min= | actual=%ld\n", sizeof(double));
	printf("long double: min= | actual=%ld\n", sizeof(long double));
}


