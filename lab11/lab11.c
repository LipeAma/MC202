// MC202 - Lab02
// Felipe Costa Amaral - Ra:249239

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
  struct Node *next;
  unsigned val;
  unsigned count;
} Node;

typedef struct List {
  Node *headDummy;
  Node *beforeTailDummy;
} List;

List *newList(unsigned n) {
  List *list = malloc(sizeof(List));
  Node *headDummy = malloc(sizeof(Node));
  Node *tailDummy = malloc(sizeof(Node));
  list->headDummy = headDummy;
  tailDummy->next = NULL;
  tailDummy->count = 0;

  Node *current = headDummy;
  for (unsigned i = 1; i <= n; i++) {
    Node *new = malloc(sizeof(Node));
    new->val = i;
    new->count = 0;
    current->next = new;
    current = new;
  }
  list->beforeTailDummy = current;
  current->next = tailDummy;
  return list;
}

void freeList(List *list) {
  Node *previous;
  Node *current = list->headDummy;
  while (current != NULL) {
    previous = current;
    current = current->next;
    free(previous);
  }
  free(list);
}

void printList(List *list) {
  Node *current = list->headDummy->next;
  while (current->next != NULL) {
    printf("%u ", current->val);
    current = current->next;
  }
  printf("\n");

  current = list->headDummy->next;
  while (current->next != NULL) {
    printf("%u ", current->count);
    current = current->next;
  }
  printf("\n");
}

void listAppend(List *list, unsigned key) {
  Node *new = malloc(sizeof(Node));
  new->val = key;
  new->count = 0;
  new->next = list->beforeTailDummy->next;
  list->beforeTailDummy->next = new;
  list->beforeTailDummy = new;
}

void listInsert(List *list, unsigned key) {
  Node *new = malloc(sizeof(Node));
  new->val = key;
  new->count = 0;
  if (list->headDummy == list->beforeTailDummy)
    list->beforeTailDummy = new;
  new->next = list->headDummy->next;
  list->headDummy->next = new;
}

unsigned sequencialSearch(List *list, unsigned key) {
  Node *current = list->headDummy->next;
  unsigned comparisons = 0;
  while (current->next != NULL) {
    comparisons++;
    if (current->val == key) {
      current->count++;
      return comparisons;
    }
    current = current->next;
  }
  listAppend(list, key);
  return comparisons;
}

unsigned mtfSearch(List *list, unsigned key) {
  Node *current = list->headDummy->next;
  Node *previous = NULL;

  unsigned comparisons = 0;
  while (current->next != NULL) {
    comparisons++;
    if (current->val == key) {
      current->count++;
      if (previous != NULL) {
        if (current == list->beforeTailDummy)
          list->beforeTailDummy = previous;
        previous->next = current->next;
        current->next = list->headDummy->next;
        list->headDummy->next = current;
      }
      return comparisons;
    }
    previous = current;
    current = current->next;
  }
  listInsert(list, key);
  return comparisons;
}

unsigned transposeSearch(List *list, unsigned key) {
  Node *current = list->headDummy->next;
  unsigned comparisons = 0;

  if (current->next == NULL)
    return comparisons;
  comparisons++;
  if (current->val == key) {
    current->count++;
    return comparisons;
  }
  Node *previous = current;
  current = current->next;

  if (current->next == NULL)
    return comparisons;
  comparisons++;
  if (current->val == key) {
    current->count++;
    list->headDummy->next = current;
    previous->next = current->next;
    current->next = previous;
    if (current == list->beforeTailDummy)
      list->beforeTailDummy = previous;
    return comparisons;
  }
  Node *previousPrevious = previous;
  previous = current;
  current = current->next;

  while (current->next != NULL) {
    comparisons++;
    if (current->val == key) {
      current->count++;
      previousPrevious->next = current;
      previous->next = current->next;
      current->next = previous;
      if (current == list->beforeTailDummy)
        list->beforeTailDummy = previous;
      return comparisons;
    }
    previousPrevious = previous;
    previous = current;
    current = current->next;
  }
  listInsert(list, key);
  return comparisons;
}

unsigned countSearch(List *list, unsigned key) {
  Node *current = list->headDummy->next;
  Node *previous = list->headDummy;
  unsigned comparisons = 0;

  while (current->next != NULL) {
    comparisons++;
    if (current->val == key) {
      Node *foundNode = current;
      foundNode->count++;
      previous->next = foundNode->next;
      if (foundNode == list->beforeTailDummy)
        list->beforeTailDummy = previous;

      current = list->headDummy->next;
      previous = list->headDummy;
      while (current->next != NULL && current->count > foundNode->count) {
        previous = current;
        current = current->next;
      }
      foundNode->next = current;
      previous->next = foundNode;
      if (previous == list->beforeTailDummy)
        list->beforeTailDummy = foundNode;
      return comparisons;
    }
    previous = current;
    current = current->next;
  }

  Node *new = malloc(sizeof(Node));
  new->val = key;
  new->count = 0;
  current = list->headDummy->next;
  previous = list->headDummy;
  while (current->next != NULL) {
    if (current->count == 0) {
      new->next = current;
      previous->next = new;
      if (previous == list->beforeTailDummy)
        list->beforeTailDummy = new;
      return comparisons;
    }
    previous = current;
    current = current->next;
  }
  return comparisons;
}

void replForTests(void) {
  List *list = NULL;
  char command;
  unsigned n;
  while (scanf("%c", &command) != EOF) {
    switch (command) {
    case 'n':
      if (list != NULL)
        break;
      printf("Numero : ");
      scanf("%u", &n);
      list = newList(n);
      printList(list);
      break;
    case 'f':
      if (list == NULL)
        break;
      freeList(list);
      list = NULL;
      printf("list free\n");
      break;
    case 'a':
      if (list == NULL)
        break;
      printf("Numero : ");
      scanf("%u", &n);
      listAppend(list, n);
      printList(list);
      break;
    case 'i':
      if (list == NULL)
        break;
      printf("Numero : ");
      scanf("%u", &n);
      listInsert(list, n);
      printList(list);
      break;
    case 'p':
      if (list == NULL)
        break;
      printList(list);
      break;
    case 's':
      if (list == NULL)
        break;
      printf("Sequential: ");
      scanf("%u", &n);
      n = sequencialSearch(list, n);
      printf("Result=%u\n", n);
      printList(list);
      break;
    case 'm':
      if (list == NULL)
        break;
      printf("MTF: ");
      scanf("%u", &n);
      n = mtfSearch(list, n);
      printf("Result=%u\n", n);
      printList(list);
      break;
    case 't':
      if (list == NULL)
        break;
      printf("Transpose: ");
      scanf("%u", &n);
      n = transposeSearch(list, n);
      printf("Result=%u\n", n);
      printList(list);
      break;
    case 'c':
      if (list == NULL)
        break;
      printf("Count: ");
      scanf("%u", &n);
      n = countSearch(list, n);
      printf("Result=%u\n", n);
      printList(list);
      break;
    }
  }
}

int main(void) {
  // replForTests();
  unsigned n, r, sum;
  List *list;
  scanf("%u %u", &n, &r);
  unsigned *keys = malloc(sizeof(unsigned) * r);
  for (unsigned i = 0; i < r; i++) {
    scanf("%u", &keys[i]);
  }

  sum = 0;
  list = newList(n);
  for (unsigned i = 0; i < r; i++) {
    sum += sequencialSearch(list, keys[i]);
  }
  freeList(list);
  printf("Sequencial: %u\n", sum);

  sum = 0;
  list = newList(n);
  for (unsigned i = 0; i < r; i++) {
    sum += mtfSearch(list, keys[i]);
  }
  freeList(list);
  printf("MTF: %u\n", sum);

  sum = 0;
  list = newList(n);
  for (unsigned i = 0; i < r; i++) {
    sum += transposeSearch(list, keys[i]);
  }
  freeList(list);
  printf("Transpose: %u\n", sum);

  sum = 0;
  list = newList(n);
  for (unsigned i = 0; i < r; i++) {
    sum += countSearch(list, keys[i]);
  }
  freeList(list);
  printf("Count: %u\n", sum);
}