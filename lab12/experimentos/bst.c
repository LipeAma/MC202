#include "bst.h"

#include <stdio.h>
#include <stdlib.h>

Tree *newTree(void) {
  Tree *tree = calloc(1, sizeof(Tree));
  return tree;
}

Node *newNode(int key) {
  Node *newNode = calloc(1, sizeof(Node));
  if (newNode != NULL) newNode->key = key;
  return newNode;
}

void insert(Tree *tree, int key) {
  if (tree->root == NULL) {
    tree->root = newNode(key);
    tree->number += 1;
  }
  if (insertRecursion(&(tree->root), key) == 1) {
    tree->number += 1;
  }
}

int insertRecursion(Node **pcurruent, int key) {
  Node *current = *pcurruent;
  if (current == NULL) {
    *pcurruent = newNode(key);
    return 1;
  } else {
    if (key < current->key) {
      return insertRecursion(&(current->left), key);
    } else if (key > current->key) {
      return insertRecursion(&(current->right), key);
    } else {
      return 0;
    }
  }
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
    free(current);
  } else if (current->left == NULL) {
    *pcurrent = current->right;
    free(current);
  } else {
    *pcurrent = removeMax(&current->left);
    (*pcurrent)->left = current->left;
    (*pcurrent)->right = current->right;
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
  printf("%2d | ", current->key);
  if (current->left)
    printf("%2d e ", current->left->key);
  else
    printf("-- e ");
  if (current->right)
    printf("%2d\n", current->right->key);
  else
    printf("--\n");
  print_recursive(current->left);
  print_recursive(current->right);
}

int getNextNode(Node *current, int key) {
  Node *lastLeft = NULL;
  while (1) {
    if (current == NULL) return 0;
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
    if (lastLeft == NULL)
      return 0;
    else
      return lastLeft->key;
  } else
    current = current->right;
  while (current->left != NULL) current = current->left;
  return current->key;
}

int getPrevNode(Node *current, int key) {
  Node *lastRight = NULL;
  while (1) {
    if (current == NULL) return 0;
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
    if (lastRight == NULL)
      return 0;
    else
      return lastRight->key;
  } else {
    current = current->left;
  }
  while (current->right != NULL) current = current->right;
  return current->key;
}

void getRange(Tree *tree, int a, int b) {
  Node *current = tree->root;
  if (current == NULL) return;
  getRange_recursive(current, a, b);
  printf("\n");
}

void getRange_recursive(Node *current, int a, int b) {
  if (current == NULL) return;
  getRange_recursive(current->left, a, b);
  if (current->key >= a && current->key <= b) printf("%d ", current->key);
  getRange_recursive(current->right, a, b);
}

void REPL() {
  char cmd;
  Tree *tree = NULL;
  int key, a, b;
  while (1) {
    printf("cmd: ");
    if (scanf(" %c", &cmd) == EOF) break;
    switch (cmd) {
      case 'n':
        tree = newTree();
        break;
      case 'i':
        scanf("%d", &key);
        insert(tree, key);
        break;
      case 'r':
        scanf("%d", &key);
        removeNode(tree, key);
        break;
      case 'p':
        print_recursive(tree->root);
        break;
      case 'l':
        scanf("%d", &key);
        printf("%d", getNextNode(tree->root, key));
        break;
      case 'k':
        scanf("%d", &key);
        printf("%d", getPrevNode(tree->root, key));
        break;
      case 'g':
        scanf("%d", &a);
        scanf("%d", &b);
        getRange(tree, a, b);
        break;
    }
  }
}

int main(void) { REPL(); }

/*
i50
i20
i10
i5
i1
i7
i15
i12
i17
i30
i25
i21
i27
i35
i32
i37
i70
i60
i55
i51
i57
i65
i62
i67
i80
i75
i71
i77
i85
i82
i87
*/