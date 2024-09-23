#include "dequef.h"
#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
Cria um deque de floats.

capacity: (>=1) Capacidade mínima de floats no deque.
resizeFactor: (>1) Fator de redimensionamento. Valores mais altos consomem mais
memória.

Sucesso -> dequef*
Fracasso -> NULL
 */
dequef *df_alloc(long capacity, double resizeFactor) {
  if (capacity < 1 || resizeFactor <= 1 || capacity * sizeof(float) > 32000000)
    return NULL;

  dequef *deque = malloc(sizeof(dequef));
  if (deque == NULL)
    return NULL;

  deque->size = 0;
  deque->first = 0;
  deque->mincap = capacity;
  deque->cap = capacity;
  deque->factor = resizeFactor;

  deque->data = malloc(capacity * sizeof(float));
  if (deque->data == NULL) {
    printf("eita");
    free(deque);
    return NULL;
  }

  return deque;
}

/**
Remove um deque da memória.
**/
void df_free(dequef *deque) {
  free(deque->data);
  free(deque);
}

/**
Retorna a quantidade de elementos em um deque.
**/
long df_size(dequef *deque) { return deque->size; }

/**
Aumenta um deque de acordo com seu fator de redimensionamento, apenas se
estiver cheio. Caso de falhe, mantém o deque inalterado.

Sucesso -> 1
Falha -> 0
**/
int df_upscale(dequef *deque) {
  if (deque->cap == deque->size) {

    long novaCapacidade = deque->cap * deque->factor;
    if (novaCapacidade == deque->cap)
      return 0;

    float *arrayFloat = realloc(deque->data, novaCapacidade * sizeof(float));

    /*
    Ao aumentar o vetor, é necessário mover para o fim do vetor grande os
    valores que encontravam-se no fim no vetor pequeno. Exemplo:

    Antes :            c d e _ _ _ a b
    Logo após aumento: c d e _ _ _ a b _ _ _ _ _
    Arrumado :         c d e _ _ _ _ _ _ _ _ a b

    Dada a implementação, se não houver espaços vazios entre os valores eles
    serão deslocadas para o final, mesmo que isso seja desnecessário. Exemplo:

    Antes:             a b c d e _ _ _
    Logo após aumento: a b c d e _ _ _ _ _ _ _ _
    Arrumado :         _ _ _ _ _ _ _ _ a b c d e

    O código abaixo encarrega-se disso.
    */
    for (long i = 1; i <= deque->cap - deque->first; i++) {
      arrayFloat[novaCapacidade - i] = arrayFloat[deque->cap - i];
    }
    deque->first += novaCapacidade - deque->cap;
    deque->data = arrayFloat;
    deque->cap = novaCapacidade;
  }
  return 1;
}

/**
Diminui um deque de acordo com seu fator de redimensionamento, apenas se
necessário. Caso de falhe, pode alterar o deque.

Sucesso -> 1
Falha -> 0
**/
int df_downscale(dequef *deque) {
  if (deque->cap / pow(deque->factor, 2.0) >= deque->size) {

    long novaCapacidade = deque->cap / deque->factor;
    if (novaCapacidade == deque->cap)
      return 0;
    if (novaCapacidade < deque->mincap)
      novaCapacidade = deque->mincap;

    /*
    Ao diminuir o vetor, é preciso que todos os valores estejam na região que se
    manterá para que não haja perdas, por exemplo:

    Caso 1 - Há espaços vazios entre os valores.
    Antes:                      c d e _ _ _ _ _ _ _ _ a b
    Se diminuisse sem arrumar:  c d e _ _ _ _ _
    Arrumado:                   c d e _ _ _ a b _ _ _ _ _
    Logo após diminuição:       c d e _ _ _ a b

    Caso 2 - Não há espaços vazios entre os valores.
    Antes:                      _ _ _ _ a b c d e _ _ _ _
    Se diminuisse sem arrumar:  _ _ _ _ a b c d
    Arrumado:                   a b c d e _ _ _ _ _ _ _ _
    Logo após diminuição:       a b c d e _ _ _

    O código abaixo encarrega-se disso.
    */
    if (deque->first + deque->size >= deque->cap) {
      for (long i = 1; i <= deque->cap - deque->first; i++) {
        deque->data[novaCapacidade - i] = deque->data[deque->cap - i];
      }
      deque->first += novaCapacidade - deque->cap;
    } else if (deque->first + deque->size > novaCapacidade) {
      for (long i = 0; i < deque->size; i++)
        deque->data[i] = deque->data[deque->first + i];
      deque->first = 0;
    }

    float *arrayFloat = realloc(deque->data, novaCapacidade * sizeof(float));
    if (arrayFloat == NULL)
      return 0;

    deque->data = arrayFloat;
    deque->cap = novaCapacidade;
  }
  return 1;
}

/**
Adiciona um valor no final do deque. Aumenta a capacidade do deque se necessário
e possível.

deque: O deque.
valor: O float a ser adicionado.

Sucesso -> 1
Falha -> 0
**/
int df_push(dequef *deque, float valor) {

  if (df_upscale(deque) == 0)
    return 0;

  long insertPosition = deque->first + deque->size;
  if (insertPosition >= deque->cap)
    insertPosition -= deque->cap;

  deque->data[insertPosition] = valor;
  deque->size += 1;

  return 1;
}

/**
Remove um float do fim do deque e o retorna. Diminui o tamanho deque se
necessário e possível.

Sucesso -> Valor removido
Falha -> 0
**/
float df_pop(dequef *deque) {

  if (deque->size == 0)
    return 0.0f;

  long popPosition = deque->first + deque->size - 1;
  if (popPosition >= deque->cap)
    popPosition -= deque->cap;

  float returnValue = deque->data[popPosition];
  deque->size -= 1;
  if (df_downscale(deque) == 0)
    return 0;

  return returnValue;
}

/**
Adiciona um valor no início do deque. Aumenta a capacidade do deque se
necessário e possível.

Sucesso -> 1
Falha -> 0
**/
int df_inject(dequef *deque, float valor) {

  if (df_upscale(deque) == 0)
    return 0;

  long insertPosition = deque->first - 1;
  if (insertPosition == -1)
    insertPosition += deque->cap;

  deque->data[insertPosition] = valor;
  deque->size += 1;
  deque->first = insertPosition;

  return 1;
}

/**
Remove um float do inicio do deque e o retorna. Diminui o tamanho deque se
necessário e possível.

Sucesso -> Valor removido
Falha -> 0
**/
float df_eject(dequef *deque) {

  if (deque->size == 0)
    return 0.0f;

  float returnValue = deque->data[deque->first];
  deque->first += 1;
  deque->size -= 1;
  if (deque->first >= deque->cap)
    deque->first = 0;

  if (df_downscale(deque) == 0)
    return 0.0f;

  return returnValue;
}

/**
Retorna o valor na posição especificada.

Sucesso -> Valor removido
Falha -> 0
**/
float df_get(dequef *deque, long posicao) {

  if (posicao < 0 || posicao >= deque->size) {
    errno = 33;
    return 0.0f;
  } else {
    long getPosition = deque->first + posicao;
    if (getPosition >= deque->cap)
      getPosition -= deque->cap;
    return deque->data[getPosition];
  }
}

/**
Modifica a posição especificada para o valor especificado.
**/
void df_set(dequef *deque, long posicao, float valor) {
  if (posicao >= 0 && posicao < deque->size) {
    long setPosition = deque->first + posicao;
    if (setPosition >= deque->cap)
      setPosition -= deque->cap;
    deque->data[setPosition] = valor;
  } else {
    errno = 33;
  }
}

/**
Imprime os elementos do deque.
**/
void df_print(dequef *deque) {
  if (deque == NULL) {
    errno = 22;
  } else {
    printf("deque (%ld):", deque->size);
    for (long i = deque->first; i < deque->first + deque->size; i++) {
      if (i >= deque->cap)
        printf(" %.1f", deque->data[i - deque->cap]);
      else
        printf(" %.1f", deque->data[i]);
    }
    printf("\n");
  }
}

/**
Imprime o array, incluido valores vazios.
**/
void df_printArray(dequef *deque) {
  if (deque == NULL) {
    errno = 22;
  } else {
    printf("deque (%ld):", deque->size);
    long blanksBeforeFirst = deque->first;
    if (deque->first + deque->size >= deque->cap) {
      long numOfElements = deque->first + deque->size - deque->cap;
      blanksBeforeFirst -= numOfElements;
      for (int i = 0; i < numOfElements; i++)
        printf(" %.1f", deque->data[i]);
    }
    for (int i = 0; i < blanksBeforeFirst; i++)
      printf(" _");
    for (int i = deque->first; i < deque->cap; i++) {
      if (i >= deque->first + deque->size)
        printf(" _");
      else
        printf(" %.1f", deque->data[i]);
    }
    printf("\n");
  }
}
