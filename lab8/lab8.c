#include <stdio.h>
#include <stdlib.h>

typedef struct Set {
  struct Element *firstDummy;
  struct Element *lastDummy;
} Set;

typedef union Val {
  int num;
  struct {
    int name;
    Set *pointer;
  } set;
} Val;

typedef struct Element {
  Val val;
  struct Element *next;
  struct Element *prev;
} Element;

Set *newSet(void) {
  Set *set = (Set *)malloc(sizeof(Set));
  if (set == NULL)
    return NULL;
  set->firstDummy = (Element *)calloc(1, sizeof(Element));
  if (set->firstDummy == NULL) {
    free(set);
    return NULL;
  }
  set->lastDummy = (Element *)calloc(1, sizeof(Element));
  if (set->lastDummy == NULL) {
    free(set->firstDummy);
    free(set);
    return NULL;
  }
  set->firstDummy->next = set->lastDummy;
  set->lastDummy->prev = set->firstDummy;
  return set;
}

void freeSet(Set *set) {
  Element *element = set->firstDummy;
  while (element->next != NULL) {
    element = element->next;
    free(element->prev);
  }
  free(element);
  free(set);
  return;
}

int containsVal(int val, Set *set) {
  int retVal = 0;
  for (Element *element = set->firstDummy->next; element->next != NULL;
       element = element->next) {
    if (element->val.num == val) {
      retVal = 1;
      break;
    }
  }
  return retVal;
}

void insertVal(int val, Set *set) {
  for (Element *element = set->firstDummy->next; element->next != NULL;
       element = element->next) {
    if (element->val.num == val)
      return;
  }

  Element *element = (Element *)malloc(sizeof(Element));
  if (element == NULL)
    return;

  Element *aux = set->firstDummy->next;
  while (aux->next != NULL) {
    if (aux->val.num > val)
      break;
    aux = aux->next;
  }
  element->val.num = val;
  element->next = aux;
  element->prev = aux->prev;
  element->prev->next = element;
  element->next->prev = element;
  return;
}

void removeVal(int val, Set *set) {
  for (Element *element = set->firstDummy->next; element->next != NULL;
       element = element->next) {
    if (element->val.num == val) {
      element->prev->next = element->next;
      element->next->prev = element->prev;
      free(element);
    }
  }
  return;
}

Set *actionC(Set *setOfSets, int newSetName) {
  if (newSetName == -1)
    scanf("%d", &newSetName);
  for (Element *set = setOfSets->firstDummy->next; set->next != NULL;
       set = set->next) {
    if (set->val.set.name == newSetName) {
      freeSet(set->val.set.pointer);
      set->val.set.pointer = newSet();
      return set->val.set.pointer;
    }
  }
  Element *set = malloc(sizeof(Element));
  set->val.set.name = newSetName;
  set->val.set.pointer = newSet();
  set->next = setOfSets->lastDummy;
  set->prev = set->next->prev;
  set->prev->next = set;
  set->next->prev = set;
  return set->val.set.pointer;
}

void actionI(Set *setOfSets) {
  int setName;
  int num;
  scanf("%d", &setName);
  int len;
  scanf("%d", &len);

  for (Element *set = setOfSets->firstDummy->next; set->next != NULL;
       set = set->next) {
    if (set->val.set.name == setName) {
      for (int i = 1; i <= len; i++) {
        scanf("%d", &num);
        insertVal(num, set->val.set.pointer);
      }
      break;
    }
  }
  return;
}

void actionR(Set *setOfSets) {
  int setName;
  int num;
  scanf("%d", &setName);
  int len;
  scanf("%d", &len);

  for (Element *set = setOfSets->firstDummy->next; set->next != NULL;
       set = set->next) {
    if (set->val.set.name == setName) {
      for (int i = 1; i <= len; i++) {
        scanf("%d", &num);
        removeVal(num, set->val.set.pointer);
      }
      break;
    }
  }
  return;
}

void actionU(Set *setOfSets) {
  int nameA, nameB, nameC;
  scanf("%d %d %d", &nameA, &nameB, &nameC);

  Set *A = actionC(setOfSets, nameA), *B = NULL, *C = NULL;
  for (Element *set = setOfSets->firstDummy->next; set->next != NULL;
       set = set->next) {
    if (set->val.set.name == nameB)
      B = set->val.set.pointer;
    if (set->val.set.name == nameC)
      C = set->val.set.pointer;
    if (B && C)
      break;
  }

  for (Element *element = B->firstDummy->next; element->next != NULL;
       element = element->next) {
    insertVal(element->val.num, A);
  }

  for (Element *element = C->firstDummy->next; element->next != NULL;
       element = element->next) {
    insertVal(element->val.num, A);
  }
  return;
}

void actionN(Set *setOfSets) {
  int nameA, nameB, nameC;
  scanf("%d %d %d", &nameA, &nameB, &nameC);

  Set *A = actionC(setOfSets, nameA), *B = NULL, *C = NULL;
  for (Element *set = setOfSets->firstDummy->next; set->next != NULL;
       set = set->next) {
    if (set->val.set.name == nameB)
      B = set->val.set.pointer;
    if (set->val.set.name == nameC)
      C = set->val.set.pointer;
    if (B && C)
      break;
  }

  for (Element *element = B->firstDummy->next; element->next != NULL;
       element = element->next) {
    if (containsVal(element->val.num, C))
      insertVal(element->val.num, A);
  }
  return;
}

void actionM(Set *setOfSets) {
  int nameA, nameB, nameC;
  scanf("%d %d %d", &nameA, &nameB, &nameC);

  Set *A = actionC(setOfSets, nameA), *B = NULL, *C = NULL;
  for (Element *set = setOfSets->firstDummy->next; set->next != NULL;
       set = set->next) {
    if (set->val.set.name == nameB)
      B = set->val.set.pointer;
    if (set->val.set.name == nameC)
      C = set->val.set.pointer;
    if (B && C)
      break;
  }

  for (Element *element = B->firstDummy->next; element->next != NULL;
       element = element->next) {
    if (!containsVal(element->val.num, C))
      insertVal(element->val.num, A);
  }
  return;
}

void actionE(Set *setOfSets) {
  int setName;
  int num;
  scanf("%d %d", &setName, &num);

  Set *A = NULL;
  for (Element *set = setOfSets->firstDummy->next; set->next != NULL;
       set = set->next) {
    if (set->val.set.name == setName) {
      A = set->val.set.pointer;
      break;
    }
  }
  if (A == NULL) {
    A = actionC(setOfSets, -1);
  }
  if (containsVal(num, A))
    printf("%d esta em C%d\n", num, setName);
  else
    printf("%d nao esta em C%d\n", num, setName);
  return;
}

void actionP(Set *setOfSets) {
  int setName;
  scanf("%d", &setName);

  Set *A = NULL;
  for (Element *set = setOfSets->firstDummy->next; set->next != NULL;
       set = set->next) {
    if (set->val.set.name == setName) {
      A = set->val.set.pointer;
      break;
    }
  }

  if (A == NULL) {
    A = actionC(setOfSets, -1);
  }
  printf("C%d = {", setName);
  Element *element = A->firstDummy->next;
  while (element->next != NULL) {
    printf("%d", element->val.num);
    element = element->next;
    if (element->next != NULL)
      printf(", ");
  }
  printf("}\n");
}

void actionT(Set *setOfSets) {
  for (Element *set = setOfSets->firstDummy->next; set->next != NULL;
       set = set->next)
    freeSet(set->val.set.pointer);
  free(setOfSets);
}

int main(void) {
  Set *setOfSets = newSet();
  char action;
  while (scanf("%c", &action) != EOF) {
    switch (action) {
    case 'c':
      actionC(setOfSets, -1);
      break;
    case 'i':
      actionI(setOfSets);
      break;
    case 'r':
      actionR(setOfSets);
      break;
    case 'u':
      actionU(setOfSets);
      break;
    case 'n':
      actionN(setOfSets);
      break;
    case 'm':
      actionM(setOfSets);
      break;
    case 'e':
      actionE(setOfSets);
      break;
    case 'p':
      actionP(setOfSets);
      break;
    case 't':
      actionT(setOfSets);
      break;
    default:
      break;
    }
  }
}
