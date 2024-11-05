#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "funcoes.h"

int main(void) {
  Tree *tree = NULL;

  float points;
  char *name, command[17];
  while (scanf(" %s", command) != EOF) {
    if (strcmp(command, "criar") == 0) {
      if (tree != NULL) freeTree(tree);
      tree = newTree();
    }

    else if (strcmp(command, "inserir") == 0) {
      int key;
      scanf("%d, ", &key);
      name = calloc(101, sizeof(char));
      scanf(" %100[^,] ", name);
      scanf(" ,%f", &points);
      insert(tree, key, name, points);
    }

    else if (strcmp(command, "remover") == 0) {
      int key;
      scanf("%d", &key);
      removeNode(tree, key);
    }

    else if (strcmp(command, "imprimir") == 0) {
      if (tree->root == NULL) {
        printf("arvore vazia\n");
      } else {
        printTree(tree);
      }

    }

    else if (strcmp(command, "buscar") == 0) {
      int key;
      scanf("%d", &key);
      Node *node = getNode(tree, key);
      if (node == NULL)
        printf("nao ha cliente %d\n", key);
      else
        printf("cliente %d: %s, %.2f pontos\n", node->key, node->name,
               node->points);
    }

    else if (strcmp(command, "minimo") == 0) {
      if (tree->root == NULL) {
        printf("arvore vazia\n");
      } else {
        printf("minimo: %d\n", treeMin(tree));
      }
    } else if (strcmp(command, "maximo") == 0) {
      if (tree->root == NULL) {
        printf("arvore vazia\n");
      } else {
        printf("maximo: %d\n", treeMax(tree));
      }
    }

    else if (strcmp(command, "sucessor") == 0) {
      int key;
      int error;
      scanf("%d", &key);
      int result = getNextNode(tree->root, key, &error);
      if (error == -1) {
        printf("nao ha cliente %d\n", key);
      } else if (error == 1) {
        printf("sucessor de %d: nao ha\n", key);
      } else {
        printf("sucessor de %d: %d\n", key, result);
      }
    }

    else if (strcmp(command, "predecessor") == 0) {
      int key;
      int error;
      scanf("%d", &key);
      int result = getPrevNode(tree->root, key, &error);
      if (error == -1) {
        printf("nao ha cliente %d\n", key);
      } else if (error == 1) {
        printf("predecessor de %d: nao ha\n", key);
      } else {
        printf("predecessor de %d: %d\n", key, result);
      }
    }

    else if (strcmp(command, "buscar-intervalo") == 0) {
      int a, b;
      scanf("%d", &a);
      scanf("%d", &b);
      printf("clientes no intervalo [%d,%d]: ", a, b);
      if (getRange(tree, a, b) == 0) {
        printf("nenhum");
      }
      printf("\n");
    }

    else if (strcmp(command, "terminar") == 0) {
      if (tree != NULL) freeTree(tree);
      break;
    }
  }
}