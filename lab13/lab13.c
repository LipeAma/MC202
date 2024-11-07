#define N_OF_PEOPLE 100000

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  char name[50];
  unsigned known_by;
  unsigned knows;
} Person;

typedef struct {
  Person **table;
  unsigned capacity;
  unsigned size;
} Hash;

unsigned long djb2(char *str) {
  unsigned long hash = 5381;
  int c;
  while ((c = *str++)) {
    hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
  }
  return hash;
}

unsigned hashString(char *str, unsigned n_of_collisions, unsigned capacity) {
  unsigned long x = djb2(str);
  return ((x % capacity) + n_of_collisions) % capacity;
}

Hash *newHashTable(unsigned capacity) {
  Hash *hash = (Hash *)calloc(1, sizeof(Hash));
  if (hash == NULL)
    fprintf(stderr,
            "Error while allocating memory for hashTable with capacity %u\n",
            capacity);
  hash->capacity = capacity;
  hash->size = 0;
  hash->table = (Person **)calloc(capacity, sizeof(Person *));
  return hash;
}

Person *newPerson(char *name) {
  Person *new_person = (Person *)malloc(sizeof(Person));

  if (new_person == NULL)
    fprintf(stderr, "Error while allocating memory for person (%s)\n", name);

  strcpy(new_person->name, name);
  new_person->known_by = 0;
  new_person->knows = 0;

  return new_person;
}

Person *getOrAdd(Hash *hash, char *name) {
  unsigned n_of_collisions = 0;
  unsigned key_hash;
  Person **p_person;
  Person *person;

  while (1) {
    key_hash = hashString(name, n_of_collisions, hash->capacity);
    p_person = &hash->table[key_hash];
    person = *p_person;

    if (person == NULL) {
      *p_person = newPerson(name);
      ++hash->size;
      return *p_person;
    } else if (strcmp(person->name, name)) {
      ++n_of_collisions;
      continue;
    } else {
      return person;
    }
  }
}

int main(void) {
  char str1[110];
  Hash *hash = newHashTable(N_OF_PEOPLE * 1.5);

  // default value to prevent NULL access within loop.
  Person *default_most_known = newPerson((char *)"default");
  default_most_known->known_by = 0;
  Person *most_known = default_most_known;

  while (scanf(" %109[^\n]", str1) != EOF) {
    char *str2 = strstr(str1, " conhece ");
    if (str2 == NULL) continue;
    str2[0] = '\0';
    str2 += 9;  // size of " conhece "

    // now str1 is the first name and str2 is the second.

    Person *person1, *person2;
    person1 = getOrAdd(hash, str1);
    person2 = getOrAdd(hash, str2);
    if (strcmp(str1, str2)) {
      ++person1->knows;
      ++person2->known_by;
    }
    if (person2->known_by >= most_known->known_by) {
      most_known = person2;
    }
  }

  if (most_known->knows == 0 && most_known->known_by == hash->size - 1) {
    printf("%s e' celebridade.\n", most_known->name);
  } else {
    printf("Nao ha' celebridade.\n");
  }

  // TODO: free default_most_known and free hashTable.
}