#include <stdio.h>
#include <stdlib.h>

#include "AVL_header.c"

AVLtree *AVLnew(void) {
  AVLtree *tree = calloc(1, sizeof(AVLnode));
  return tree;
}

void AVLfree(AVLtree *tree) {
  if (tree->root != NULL) AVLfree_recursive(tree->root);
  free(tree);
}

void AVLfree_recursive(AVLnode *node) {
  if (node->left != NULL) AVLfree_recursive(node->left);
  if (node->right != NULL) AVLfree_recursive(node->right);
  free(node);
}

AVLnode *AVLinsert(AVLtree *tree, int key) {
  AVLnode *current, *newnode;

  newnode = calloc(1, sizeof(AVLnode));
  if (newnode == NULL) {
    printf("calloc failed\n");
    return NULL;
  }

  newnode->key = key;
  current = tree->root;
  if (current == NULL) {
    tree->root = newnode;
  } else {
    AVLinsert_recursion(current, newnode, key);
  }
  return newnode;
}

enum Insert AVLinsert_recursion(AVLnode *current, AVLnode *new, int key) {
  if (key < current->key) {
    if (current->left == NULL) {
      current->left = new;
      current->factor += 1;
      switch (current->factor) {
        case SAME:
          return HASNT_GROWN;
        default:
          return HAS_GROWN;
      }
    }
    switch (AVLinsert_recursion(current->left, new, key)) {
      case MUST_ROTATE_RIGHT:
        current->left = AVLrotateRight(current->left);
        return HASNT_GROWN;
      case MUST_ROTATE_LEFT_RIGHT:
        current->left->right = AVLrotateLeft(current->left->right);
        current->left = AVLrotateRight(current->left);
        return HASNT_GROWN;
      case MUST_ROTATE_LEFT:
        current->left = AVLrotateLeft(current->left);
        return HASNT_GROWN;
      case MUST_ROTATE_RIGHT_LEFT:
        current->left->left = AVLrotateRight(current->left->left);
        current->left = AVLrotateLeft(current->left);
        return HASNT_GROWN;
      case HASNT_GROWN:
        return HASNT_GROWN;
      case HAS_GROWN:
        current->factor += 1;
        switch (current->factor) {
          case LEFT_IS_TOO_BIG:
            return (current->left->factor == RIGHT_IS_BIGGER)
                       ? MUST_ROTATE_RIGHT_LEFT
                       : MUST_ROTATE_LEFT;
          case LEFT_IS_BIGGER:
            return HAS_GROWN;
          default:
            return HASNT_GROWN;
        }
    }
  } else if (key > current->key) {
    if (current->right == NULL) {
      current->right = new;
      current->factor -= 1;
      switch (current->factor) {
        case SAME:
          return HASNT_GROWN;
        default:
          return HAS_GROWN;
      }
    }
    switch (AVLinsert_recursion(current->right, new, key)) {
      case MUST_ROTATE_RIGHT:
        current->right = AVLrotateRight(current->right);
        return HASNT_GROWN;
      case MUST_ROTATE_LEFT_RIGHT:
        current->right->right = AVLrotateLeft(current->right->right);
        current->right = AVLrotateRight(current->right);
        return HASNT_GROWN;
      case MUST_ROTATE_LEFT:
        current->right = AVLrotateLeft(current->right);
        return HASNT_GROWN;
      case MUST_ROTATE_RIGHT_LEFT:
        current->right->left = AVLrotateRight(current->right->left);
        current->right = AVLrotateLeft(current->right);
        return HASNT_GROWN;
      case HASNT_GROWN:
        return HASNT_GROWN;
      case HAS_GROWN:
        current->factor -= 1;
        switch (current->factor) {
          case RIGHT_IS_TOO_BIG:
            return (current->right->factor == LEFT_IS_BIGGER)
                       ? MUST_ROTATE_LEFT_RIGHT
                       : MUST_ROTATE_RIGHT;
          case RIGHT_IS_BIGGER:
            return HAS_GROWN;
          default:
            return HASNT_GROWN;
        }
    }
  } else {
    return HASNT_GROWN;
  }
}

AVLnode *AVLrotateLeft(AVLnode *root) {
  AVLnode *newroot = root->left;
  root->left = newroot->right;
  newroot->right = root;
  return newroot;
}

AVLnode *AVLrotateRight(AVLnode *root) {
  AVLnode *newroot = root->right;
  root->right = newroot->left;
  newroot->left = root;
  return newroot;
}

void AVLprint(AVLtree *tree) {
  AVLnode *nodes[1000];
  AVLnode *current = tree->root;
  if (current == NULL) {
    printf("Empty tree\n");
    return;
  }
  nodes[0] = current;
  int current_index = 0;
  int first_empty = 1;
  int las_non_null = 0;
  int layer = 1;
  while (current_index < 64) {
    current = nodes[current_index];
    if (current_index == (layer * 2 - 1)) {
      printf("\n");
      layer *= 2;
    }
    if (current == NULL) {
      nodes[first_empty] = NULL;
      first_empty += 1;
      nodes[first_empty] = NULL;
      first_empty += 1;
      printf("n ");
    } else {
      nodes[first_empty] = current->left;
      first_empty += 1;
      nodes[first_empty] = current->right;
      first_empty += 1;
      printf("%d ", current->factor);
    }
    current_index += 1;
  }
}

int main(void) {
  char cmd;
  int key;
  AVLtree *tree = AVLnew();
  while (scanf("%c", &cmd)) {
    switch (cmd) {
      case 'i':
        scanf("%d", &key);
        AVLinsert(tree, key);
        break;
      case 'p':
        AVLprint(tree);
        break;
    }
  }
}