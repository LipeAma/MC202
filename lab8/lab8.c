#include <stdio.h>
#include <stdlib.h>

// -------------------------- Declarações ----------------------------------

typedef struct Element {
  struct Element *next;
  long val; // Não foi especificado os limites
} Element;

typedef struct Set {
  struct Element *dummyInicio;
  unsigned long name;   // Não foi esoecificado o limite superior
  unsigned long length; // Não foi especificado o limite superior
  struct Set *next;
  struct Set *previous;
} Set;

typedef struct ListOfSets {
  struct Set *dummy;
  unsigned char length; // é no maximo 127
} ListOfSets;

int setCreate(ListOfSets *);
int setInsertMultiple(ListOfSets *);
int setRemove(ListOfSets *);
int setUnion(ListOfSets *);
int setIntersect(ListOfSets *);
int setComplement(ListOfSets *);
int setContains(ListOfSets *);
int setPrint(ListOfSets *);
int setTerminate(ListOfSets *);

// ---------------------------- Definições ----------------------------------

int main(void) {
  int returnVal;
  char command;
  ListOfSets *list = (ListOfSets *)malloc(sizeof(ListOfSets));
  list->length = 0;
  list->dummy = (Set *)calloc(1, sizeof(Set));

  while (scanf("%c", &command) != EOF) {
    switch (command) {
    case 'c':
      returnVal = setCreate(list);
      break;
    case 'i':
      returnVal = setInsertMultiple(list);
      break;
    case 'r':
      returnVal = setRemove(list);
      break;
    case 'u':
      returnVal = setUnion(list);
      break;
    case 'n':
      returnVal = setIntersect(list);
      break;
    case 'm':
      returnVal = setComplement(list);
      break;
    case 'e':
      returnVal = setContains(list);
      break;
    case 'p':
      returnVal = setPrint(list);
      break;
    case 't':
      returnVal = setTerminate(list);
      break;
    }
  }
  return 0;
}

void freeSet(Set *set) {
  Element *aux;
  while (set->dummyInicio != NULL) {
    aux = set->dummyInicio;
    set->dummyInicio = aux->next;
    free(aux);
  }
  free(set);
}
Set *getSet(ListOfSets *list, unsigned long setName) {
  Set *set = list->dummy;
  for (; set != NULL && set->name != setName; set = set->next) {
  }
  return set;
}
void setInsertOne(Set *set, long val) {
  for (Element *current = set->dummyInicio->next; current != NULL;
       current = current->next) {
    if (current->val == val)
      return;
  }
  Element *new = (Element *)malloc(sizeof(Element));
  new->val = val;
  new->next = set->dummyInicio->next;
  set->dummyInicio->next = new;
}

// implementar error handling em tudo
int setCreate(ListOfSets *list) {
  // Scaneia o nome do set que será criado.
  unsigned long setName;
  if (scanf(" %lu", &setName) != 1)
    return 1;

  // Anda pela lista para verificar se existe um set com esse nome.
  // Se existir, ele será deletado.
  Set *set = getSet(list, setName);
  if (set != NULL) {
    set->previous->next = set->next;
    freeSet(set);
  }

  // Cria o novo set e adiciona na lista.
  Set *new = (Set *)malloc(sizeof(Set));
  new->dummyInicio = calloc(1, sizeof(Element));
  new->length = 0;
  new->name = setName;
  new->previous = list->dummy;
  new->next = list->dummy->next;
  list->dummy->next = new;
  if (new->next != NULL)
    new->next->previous = new;
  return 0;
}
// implementar error handling
int setInsertMultiple(ListOfSets *list) {
  // Scaneia o nome do set no qual será inserido.
  unsigned long setName;
  if (scanf(" %lu", &setName) != 1)
    return 1;
  Set *set = getSet(list, setName);
  if (set == NULL)
    return 0;

  char linebreak;
  long val;
  while (scanf("%c", &linebreak) && linebreak != '\n') {
    scanf("%ld", &val);
    setInsertOne(set, val);
  }
  return 0;
}

int setRemove(ListOfSets *list) { return 0; }
int setUnion(ListOfSets *list) { return 0; }
int setIntersect(ListOfSets *list) { return 0; }
int setComplement(ListOfSets *list) { return 0; }
int setContains(ListOfSets *list) { return 0; }
int setPrint(ListOfSets *list) { return 0; }