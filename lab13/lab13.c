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
} hashTable;

unsigned long djb2(char *str) {
  unsigned long hash = 5381;
  int c;
  while ((c = *str++)) {
    hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
  }
  return hash;
}

unsigned hash(char *str, unsigned n_of_collisions, unsigned table_size) {
  unsigned long x = djb2(str);
  return ((x % table_size) + n_of_collisions) % table_size;
}

hashTable *newHashTable(unsigned capacity) {
  hashTable *table = calloc(1, sizeof(hashTable));
  if (table == NULL)
    fprintf(stderr,
            "Error while allocating memory for hashTable with size %u\n",
            capacity);
  table->capacity = capacity;
  table->size = 0;
  table->table = calloc(capacity, sizeof(Person *));
  return table;
}

Person *newPerson(char *name) {
  Person *new_person = malloc(sizeof(Person));
  if (new_person == NULL)
    fprintf(stderr, "Error while allocating memory for person (%s)\n", name);
  strcpy(new_person->name, name);
  new_person->known_by = 0;
  new_person->knows = 0;
  return new_person;
}

Person *increaseKnownBy(hashTable *table, char *name) {
  // Increases the counter which tracks how many people know <name>, and then
  // returns it.
  unsigned n_of_collisions = 0;
  unsigned key_hash;
  Person **pperson;
  Person *person;

  while (1) {
    key_hash = hash(name, n_of_collisions, table->capacity);
    pperson = &table->table[key_hash];
    person = *pperson;

    if (person == NULL) {
      *pperson = newPerson(name);
      ++(*pperson)->known_by;
      ++table->size;
      return *pperson;
    }

    if (strcmp(person->name, name)) {
      ++n_of_collisions;
      continue;
    } else {
      ++person->known_by;
      return person;
    }
  }
}

void increseKnows(hashTable *table, char *name) {
  // Increases the counter which tracks how many people know <name>, and then
  // returns it.
  unsigned n_of_collisions = 0;
  unsigned key_hash;
  Person **pperson;
  Person *person;

  while (1) {
    key_hash = hash(name, n_of_collisions, table->capacity);
    pperson = &table->table[key_hash];
    person = *pperson;

    if (person == NULL) {
      *pperson = newPerson(name);
      ++(*pperson)->knows;
      ++table->size;
      return;
    }

    if (strcmp(person->name, name)) {
      ++n_of_collisions;
      continue;
    } else {
      ++person->knows;
      return;
    }
  }
}

int main(void) {
  char str1[110];
  Person *most_known = NULL, *person;
  unsigned n_of_people = 0;
  hashTable *hash_table = newHashTable(N_OF_PEOPLE * 1.5);
  while (scanf(" %109[^\n]", str1) != EOF) {
    char *str2 = strstr(str1, " conhece ");
    if (str2 == NULL) continue;
    str2[0] = '\0';
    str2 += 9;

    increseKnows(hash_table, str1);

    person = increaseKnownBy(hash_table, str2);
    if (most_known == NULL || person->known_by > most_known->known_by) {
      most_known = person;
    }
  }
  if (most_known->knows == 0 && most_known->known_by == hash_table->size - 1) {
    printf("%s e' celebridade.\n", most_known->name);
  } else {
    printf("Nao ha' celebridade.\n");
  }
}