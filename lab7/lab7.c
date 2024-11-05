#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
  double val;
  struct Node *next;
} Node;

typedef struct {
  unsigned long lenght;
  Node *head;
} ChainList;

// Cria e retorna uma lista vazia.
ChainList *listNew() {
  ChainList *list = (ChainList *)calloc(1, sizeof(ChainList));
  if (list == NULL) {
    fprintf(stderr, "Erro ao alocar memória para lista encadeada.");
    exit(1);
  }
  return list;
}

// Escaneia o numero a ser inserido, bem como a posição da inserção,
// e executa a inserção. Todos os inteiros positivos são posições válidas. Se a
// posição for maior que a lista, o numero será inserido no fim da lista.
void listInsert(ChainList *list) {
  double value;
  unsigned long position;
  Node *current, *auxiliar;
  if (scanf(" %lu %lf ", &position, &value) != 2) {
    fprintf(stderr, "Comando faltando argumentos.");
    exit(1);
  }
  if (position > list->lenght) position = list->lenght;

  auxiliar = (Node *)malloc(sizeof(Node));
  if (auxiliar == NULL) {
    fprintf(stderr, "Erro ao alocar memória para nó da lista encadeada");
    exit(1);
  }
  auxiliar->val = value;

  current = list->head;
  if (position == 0) {
    auxiliar->next = current;
    list->head = auxiliar;
  } else {
    for (unsigned long i = 1; i < position; i++) current = current->next;
    auxiliar->next = current->next;
    current->next = auxiliar;
  }
  list->lenght += 1;
}

// Escaneia o numero a posição a ser removida, e executa a remoção. Todos os
// inteiros positivos são posições válidas. Se a posição for maior que a lista,
// nenhum número será removido.
void listRemove(ChainList *list) {
  unsigned long position;
  Node *current, *removed;

  if (scanf(" %lu ", &position) != 1) {
    fprintf(stderr, "Comando faltando argumentos.");
    exit(1);
  }
  if (position >= list->lenght) return;

  current = list->head;
  if (position == 0) {
    list->head = current->next;
    free(current);
  } else {
    for (unsigned long i = 1; i < position; i++) current = current->next;
    removed = current->next;
    current->next = removed->next;
    free(removed);
  }
  list->lenght -= 1;
}

// Imprime o conteúdo da lista em uma linha única. Apenas 2 casas decimais são
// representadas.
void listPrint(ChainList *list) {
  Node *current;
  current = list->head;
  while (current != NULL) {
    printf("%.2lf ", current->val);
    current = current->next;
  }
  printf("\n");
}

// Escaneia duas posições, que determinam uma região da lista, e inverte a ordem
// dos nodos dessa região. A região escaneada será considerada válida se a
// primeira posição for menor que a segunda, e a segunda posição for menor que o
// tamanho da lista.
void listReverse(ChainList *list) {
  unsigned long start, end;
  Node *current, *next1, *next2, *beforeStart;

  if (scanf(" %lu %lu ", &start, &end) != 2) {
    fprintf(stderr, "Comando faltando argumentos.");
    exit(1);
  }

  if (start >= end || end >= list->lenght) return;

  // Passo 1:
  current = list->head;
  if (start != 0) {
    for (unsigned long i = 1; i < start; i++) {
      current = current->next;
    }
    beforeStart = current;
    current = current->next;
  }
  next1 = current->next;
  // currentNode aponta para X_{pos1}.
  // beforePos1 aponta para o antecessor de currentNode, se houver.
  // nextNode1 aponta para o sucessor de currentNode.

  // Passo 2:
  // currentNode percorrerá de X_{pos1} até X_{pos2-1} a cada iteração fará
  // seu sucessor apontar para ele.
  for (unsigned long i = start; i < end; i++) {
    next2 = next1->next;
    next1->next = current;
    current = next1;
    next1 = next2;
  }
  // currentNode aponta para X_{pos2}
  // nextNode1 e nextNode2 apontam para o sucessor de currentNode

  // Passo 3:
  // Arrumar quem aponta para X_{pos2} e arrumar quem é apontado por X_{pos1}
  if (start == 0) {
    list->head->next = next1;
    list->head = current;
  } else {
    beforeStart->next->next = next1;
    beforeStart->next = current;
  }
}

void listMove(ChainList *list) {
  unsigned long start, end, position;

  if (scanf(" %lu %lu %lu ", &start, &end, &position) != 3) {
    fprintf(stderr, "Comando faltando argumentos.");
    exit(1);
  }

  if (start > end || end >= list->lenght || position > list->lenght ||
      (position >= start && position <= end) || end + 1 == position)
    return;

  Node *auxiliar;
  Node *beforeStart = NULL;
  Node *atEnd;
  Node *beforePosition = NULL;

  auxiliar = list->head;
  unsigned long range = (end < position) ? position : end + 1;
  for (unsigned long i = 1; i <= range; i++) {
    if (i == start) beforeStart = auxiliar;
    if (i == end + 1) atEnd = auxiliar;
    if (i == position) beforePosition = auxiliar;
    auxiliar = auxiliar->next;
  }

  auxiliar = atEnd->next;
  atEnd->next = (beforePosition == NULL) ? list->head : beforePosition->next;
  if (beforeStart == NULL) {
    beforePosition->next = list->head;
    list->head = auxiliar;
  } else {
    if (beforePosition == NULL)
      list->head = beforeStart->next;
    else
      beforePosition->next = beforeStart->next;
    beforeStart->next = auxiliar;
  }
}

// Deleta uma lista.
void listFree(ChainList *list) {
  Node *current, *previous;

  current = list->head;
  free(list);

  while (current != NULL) {
    previous = current;
    current = current->next;
    free(previous);
  }
}

int main(void) {
  ChainList *list = NULL;
  char command;

  while (scanf("%c", &command) != EOF) {
    switch (command) {
      case 'c':
        if (list != NULL) listFree(list);
        list = listNew();
        break;
      case 'i':
        listInsert(list);
        break;
      case 'r':
        listRemove(list);
        break;
      case 'p':
        listPrint(list);
        break;
      case 'v':
        listReverse(list);
        break;
      case 'x':
        listMove(list);
        break;
      case 't':
        if (list != NULL) listFree(list);
        break;
    }
  }
  return 0;
}