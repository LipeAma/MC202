#include <stdio.h>
#include <math.h>

int main(void) {
    int n, r;
    scanf("%d", &n);
    r = ceil(sqrt((double) n));
    printf("%d", r);
}
