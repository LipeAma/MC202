/**
  dequef.h
  Declarations for a deque of floats stored in a dynamic array.
**/

#ifndef DEQUEF_H
#define DEQUEF_H

typedef struct {

  float *data; // The array of floats.

  unsigned long first; // The index of the first element in the deque.
  unsigned long size;  // The deque size.

  unsigned long cap;    // The array size.
  unsigned long mincap; // The minimum array size.
  double factor;        // The resizing factor.

} dequef;

dequef *df_alloc(long capacity, double factor);
void df_free(dequef *D);

long df_size(dequef *A);

int df_push(dequef *D, float x);
float df_pop(dequef *D);

int df_inject(dequef *D, float x);
float df_eject(dequef *D);

float df_get(dequef *D, long i);
void df_set(dequef *D, long i, float x);

void df_print(dequef *A);

#endif
