#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define func(x) x

#include "../dequef.h"

typedef int (*func_type)(void);

int teste_1() {
  // Simple create
  long capacity = 100;
  double factor = 1.5;
  dequef *res = df_alloc(capacity, factor);
  if (res->cap != capacity)
    return 0;
  if (res->mincap != capacity)
    return 0;
  if (res->size != 0)
    return 0;
  if (res->data == NULL)
    return 0;
  return res != NULL;
}

int teste_2() {
  // Memory limit exceeded for malloc
  // Too much capacity requested
  long capacity = 100000000;
  double factor = 2.0;
  dequef *res = df_alloc(capacity, factor);
  return res == NULL;
}

int main() {
  func_type func[2] = {&teste_1, &teste_2};
  int NO_TESTS = 2;
  for (int i = 0; i < NO_TESTS; i++) {
    if (!func[i]())
      printf("Test %d - FAILED\n", i + 1);
    else
      printf("Test %d - Passed\n", i + 1);
  }
  return 0;
}