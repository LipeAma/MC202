#include <math.h>
#include <stdio.h>

#define func(x) x

#include "../dequef.h"

typedef int (*func_type)(void);

int compare_floats(float a, float b) { return fabs(a - b) < 1e-9; }

int teste_1() {
  // Simple insert
  float cur_data[8] = {1.0, 2.0, 3.0, 5.0, 8.0, 13.0, 21.0, 34.0};
  dequef *res = df_alloc(8, 2.0);
  for (int i = 0; i < 7; i++)
    res->data[i] = cur_data[i];
  res->first = 0;
  res->size = 7;
  if (!df_push(res, 34.0))
    return 0;
  if (res->first != 0)
    return 0;
  if (res->size != 8)
    return 0;
  if (res->cap != 8)
    return 0;
  if (res->mincap != 8)
    return 0;
  if (!compare_floats(res->factor, 2.0))
    return 0;
  for (int i = 0; i < 8; i++) {
    if (!compare_floats(cur_data[i], df_get(res, i)))
      return 0;
  }
  return 1;
}

int teste_2() {
  // Simple insert with first in the middle
  float cur_data[8] = {21.0, 34.0, 1.0, 2.0, 3.0, 5.0, 8.0, 13.0};
  dequef *res = df_alloc(8, 2.0);
  res->data[0] = cur_data[0];
  for (int i = 2; i < 8; i++)
    res->data[i] = cur_data[i];
  res->data[1] = 0.0;
  res->first = 2;
  res->size = 7;
  if (!df_push(res, 34.0))
    return 0;
  if (res->first != 2)
    return 0;
  if (res->size != 8)
    return 0;
  if (res->cap != 8)
    return 0;
  if (res->mincap != 8)
    return 0;
  if (!compare_floats(res->factor, 2.0))
    return 0;
  for (int i = 0; i < 8; i++) {
    if (!compare_floats(cur_data[(i + 2) % 8], df_get(res, i)))
      return 0;
  }
  return 1;
}

int teste_3() {
  // Simple insert with resizing
  float cur_data[16] = {1.0,  2.0, 3.0, 5.0, 8.0, 13.0, 21.0, 34.0,
                        55.0, 0.0, 0.0, 0.0, 0.0, 0.0,  0.0};
  dequef *res = df_alloc(8, 2.0);
  for (int i = 0; i < 8; i++)
    res->data[i] = cur_data[i];
  res->first = 0;
  res->size = 8;
  if (!df_push(res, 55.0))
    return 0;
  if (res->size != 9)
    return 0;
  if (res->cap != 16)
    return 0;
  if (res->mincap != 8)
    return 0;
  if (!compare_floats(res->factor, 2.0))
    return 0;
  for (int i = 0; i < 9; i++) {
    if (!compare_floats(cur_data[i], df_get(res, i)))
      return 0;
  }
  return 1;
}

int teste_4() {
  // Simple insert with first in the middle with resizing
  float cur_data[16] = {1.0,  2.0, 3.0, 5.0, 8.0, 13.0, 21.0, 34.0,
                        55.0, 0.0, 0.0, 0.0, 0.0, 0.0,  0.0};
  dequef *res = df_alloc(8, 2.0);
  for (int i = 0; i + 3 < 8; i++)
    res->data[i + 3] = cur_data[i];
  for (int i = 5; i < 8; i++)
    res->data[i - 5] = cur_data[i];
  res->first = 3;
  res->size = 8;
  if (!df_push(res, 55.0))
    return 0;
  if (res->size != 9)
    return 0;
  if (res->cap != 16)
    return 0;
  if (res->mincap != 8)
    return 0;
  if (!compare_floats(res->factor, 2.0))
    return 0;
  for (int i = 0; i < 9; i++) {
    if (!compare_floats(cur_data[i], df_get(res, i)))
      return 0;
  }
  return 1;
}

int main() {
  func_type func[4] = {&teste_1, &teste_2, &teste_3, &teste_4};
  int NO_TESTS = 4;
  for (int i = 0; i < NO_TESTS; i++) {
    if (!func[i]())
      printf("Test %d - FAILED\n", i + 1);
    else
      printf("Test %d - Passed\n", i + 1);
  }
  return 0;
}