#include "funcoes.h"

#include <stdio.h>
#include <stdlib.h>

Tree *newTree(void) {
  Tree *tree = calloc(1, sizeof(Tree));
  return tree;
}

Node *newNode(int key, char *name, float points) {
  Node *newNode = calloc(1, sizeof(Node));
  if (newNode == NULL) return NULL;
  newNode->key = key;
  newNode->name = name;
  newNode->points = points;
  return newNode;
}

void freeTree_recursive(Node *current) {
  if (current->left != NULL)
    freeTree_recursive(current->left);
  else if (current->right != NULL)
    freeTree_recursive(current->right);
  free(current->name);
  free(current);
}

void freeTree(Tree *tree) {
  if (tree->root != NULL) freeTree_recursive(tree->root);
  free(tree);
}

int insertRecursion(Node **pcurruent, int key, char *name, float points) {
  Node *current = *pcurruent;
  if (current == NULL) {
    *pcurruent = newNode(key, name, points);
    return 1;
  } else {
    if (key < current->key) {
      return insertRecursion(&(current->left), key, name, points);
    } else if (key > current->key) {
      return insertRecursion(&(current->right), key, name, points);
    } else {
      return 0;
    }
  }
}

void insert(Tree *tree, int key, char *name, float points) {
  if (tree->root == NULL) {
    tree->root = newNode(key, name, points);
    tree->number += 1;
  }
  if (insertRecursion(&(tree->root), key, name, points) == 1) {
    tree->number += 1;
  }
}

Node *removeMax(Node **pcurrent) {
  if (*pcurrent == NULL) return NULL;
  while ((*pcurrent)->right != NULL) {
    pcurrent = &(*pcurrent)->right;
  }
  Node *current = *pcurrent;
  *pcurrent = current->left;
  current->left = NULL;
  return current;
}

Node *getMaxNode(Node *current) {
  if (current == NULL) return NULL;
  while (current->right != NULL) {
    current = current->right;
  }
  return current;
}

Node *getMinNode(Node *current) {
  if (current == NULL) return NULL;
  while (current->left != NULL) {
    current = current->left;
  }
  return current;
}

void removeNode(Tree *tree, int key) {
  Node **pcurrent = &tree->root;
  Node *current;
  while (1) {
    current = *pcurrent;
    if (current == NULL) return;

    if (key < current->key)
      pcurrent = &current->left;
    else if (key > current->key)
      pcurrent = &current->right;
    else
      break;
  }

  if (current->right == NULL) {
    *pcurrent = current->left;
    free(current->name);
    free(current);
  } else if (current->left == NULL) {
    *pcurrent = current->right;
    free(current->name);
    free(current);
  } else {
    *pcurrent = removeMax(&current->left);
    (*pcurrent)->left = current->left;
    (*pcurrent)->right = current->right;
  }
}

int treeMax(Tree *tree) {
  Node *max = getMaxNode(tree->root);
  return max->key;
}

int treeMin(Tree *tree) {
  Node *min = getMinNode(tree->root);
  return min->key;
}

void print_recursive(Node *current) {
  if (current == NULL) return;
  print_recursive(current->left);
  printf("%s (%d) ", current->name, current->key);
  print_recursive(current->right);
}

void printTree(Tree *tree) {
  printf("clientes: ");
  print_recursive(tree->root);
  printf("\n");
}

Node *getNode(Tree *tree, int key) {
  Node *current = tree->root;
  while (current != NULL) {
    if (key < current->key)
      current = current->left;
    else if (key > current->key)
      current = current->right;
    else
      return current;
  }
  return NULL;
}

int getNextNode(Node *current, int key, int *error) {
  Node *lastLeft = NULL;
  while (1) {
    if (current == NULL) {
      *error = -1;
      return 0;
    }

    if (key < current->key) {
      lastLeft = current;
      current = current->left;
    } else if (key > current->key) {
      current = current->right;
    } else {
      break;
    }
  }
  if (current->right == NULL) {
    if (lastLeft == NULL) {
      *error = 1;
      return 0;
    } else
      return lastLeft->key;
  } else
    current = current->right;
  while (current->left != NULL) current = current->left;
  return current->key;
}

int getPrevNode(Node *current, int key, int *error) {
  Node *lastRight = NULL;
  while (1) {
    if (current == NULL) {
      *error = -1;
      return 0;
    }

    if (key < current->key) {
      current = current->left;
    } else if (key > current->key) {
      lastRight = current;
      current = current->right;
    } else {
      break;
    }
  }
  if (current->left == NULL) {
    if (lastRight == NULL) {
      *error = 1;
      return 0;
    } else
      return lastRight->key;
  } else {
    current = current->left;
  }
  while (current->right != NULL) current = current->right;
  return current->key;
}

int getRange_recursive(Node *current, int a, int b) {
  int amount = 0;
  if (current == NULL) return amount;
  amount += getRange_recursive(current->left, a, b);
  if (current->key >= a && current->key <= b) {
    printf("%d ", current->key);
    amount += 1;
  }
  amount += getRange_recursive(current->right, a, b);
  return amount;
}

int getRange(Tree *tree, int a, int b) {
  Node *current = tree->root;
  int amount = 0;
  if (current == NULL) return amount;
  amount += getRange_recursive(current, a, b);
  return amount;
}