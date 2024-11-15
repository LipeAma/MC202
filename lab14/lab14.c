/*
- c n
criar um heap vazio com n pares {chave,custo}. Se já houver um heap, deve ser
removido e um novo heap vazio deve ser criado.

- i chave custo
Inserir o par {chave,custo} no heap indexado. Se estiver no heap, não fazer
nada.

- m
Remover o mínimo do heap indexado e imprimir. S vazio imprimir "heap vazio". Se
houver mais de um mínimo, o a menor chave deve ser removido.

- d chave custo
Diminuir o custo da chave.

- t
terminar, toda memória deve ser liberada.
*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
  unsigned key;
  int cost;
} Pair;

typedef struct {
  Pair *pairs;
  unsigned *index, capacity, size;
} Heap;

void heapFree(Heap *heap){
  free(heap->pairs);
  free(heap->index);    
  free(heap);
}

Heap *heapNew(unsigned capacity){
  if (capacity == UINT_MAX) return NULL;
  Heap *heap = malloc(sizeof(Heap));
  heap->pairs = malloc(sizeof(Pair)*capacity);
  heap->index = malloc(sizeof(unsigned)*capacity);
  for (unsigned i = 0; i < capacity; i++)
    heap->index[i] = UINT_MAX;
  heap->capacity = capacity;
  heap->size = 0;
  return heap;
}

void heapInsert(Heap *heap, unsigned key, int cost){
  if (heap->index[key] != UINT_MAX) return;
  unsigned i = heap->size;
  Pair *pair = &heap->pairs[i];
  pa
  while (heap->pairs[(i-1)/2]){
    ;
  }
}

Pair *heapRemove(Heap *);
void heapDecrease(Heap *, unsigned, int);

int main(void) {
  char command;
  int cost;
  unsigned key;
  Heap *heap = NULL;

  while (scanf(" %c", &command) != EOF) {
    switch (command) {
      case 'c':
        if (heap == NULL) {
          heapFree(heap);
          heap = NULL;
        }
        scanf("%d", &cost);
        heap = heapNew(cost);
        break;

      case 'i':
        if (heap == NULL) continue;
        scanf("%u %d", &key, &cost);
        heapInsert(heap, key, cost);
        break;

      case 'm':
        if (heap == NULL) continue;
        Pair *pair = heapRemove(heap);
        if (pair == NULL)
          printf("heap vazio\n");
        else
          printf("minimo {%u,%d}\n", pair->key, pair->cost);
        break;

      case 'd':
        if (heap == NULL) continue;
        scanf("%u %d", &key, &cost);
        heapDecrease(heap, key, cost);
        break;

      case 't':
        if (heap == NULL) break;
        heapFree(heap);
        break;
    }
  }
}
