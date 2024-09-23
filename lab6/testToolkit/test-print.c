#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define func(x) x

#include "../dequef.h"

typedef int (*func_type)(void);

/*
    To test df_print you must edit errno with some non-zero value when your
   function is expected to report a failure and then return.

    In addition, the output from this execution must be compared with the file
   "expected_print_output.txt".

    Notice that the tests' veredicts will be printed in the terminal.
*/

int teste_1() {
  // print with first = 0
  float cur_data[8] = {1.0, 2.0, 3.0, 5.0, 8.0, 13.0, 21.0, 34.0};
  dequef *res = df_alloc(8, 2.0);
  for (int i = 0; i < 8; i++)
    res->data[i] = cur_data[i];
  res->first = 0;
  res->size = 8;
  errno = 0;
  df_print(res);
  if (errno) {
    return 0;
  }
  return 1;
}

int teste_2() {
  // print with first in the middle
  float cur_data[8] = {1.0, 2.0, 3.0, 5.0, 8.0, 13.0, 21.0, 34.0};
  dequef *res = df_alloc(8, 2.0);
  for (int i = 0; i + 2 < 8; i++)
    res->data[i + 2] = cur_data[i];
  for (int i = 6; i < 8; i++)
    res->data[i - 6] = cur_data[i];
  res->first = 2;
  res->size = 8;
  errno = 0;
  df_print(res);
  if (errno) {
    return 0;
  }
  return 1;
}

int teste_3() {
  // print empty deque
  dequef *res = df_alloc(8, 2.0);
  res->first = 0;
  res->size = 0;
  errno = 0;
  df_print(res);
  if (errno) {
    return 0;
  }
  return 1;
}

int teste_4() {
  // print empty deque with first in the middle
  dequef *res = df_alloc(8, 2.0);
  res->first = 2;
  res->size = 0;
  errno = 0;
  df_print(res);
  if (errno) {
    return 0;
  }
  return 1;
}

int teste_5() {
  // report error for print(NULL)
  dequef *res = NULL;
  errno = 0;
  df_print(res);
  if (!errno) {
    return 0;
  }
  return 1;
}

int main() {
  func_type func[5] = {&teste_1, &teste_2, &teste_3, &teste_4, &teste_5};
  int NO_TESTS = 5;
  for (int i = 0; i < NO_TESTS; i++) {
    if (!func[i]())
      fprintf(stderr, "Test %d - FAILED\n", i + 1);
    else
      fprintf(stderr, "Test %d - Passed\n", i + 1);
  }
  return 0;
}