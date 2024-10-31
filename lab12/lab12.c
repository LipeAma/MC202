#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Tree {
    char name[101];
    float points;
    int key;
    struct Tree *left;
    struct Tree *right;
} Tree;

Tree *scanTree(void) {
    Tree *tree = malloc(sizeof(Tree));
    if (tree == NULL) {
        printf("memoria insuficiente");
        return NULL;
    }
    scanf("%d", &tree->key);
    scanf(", %100[^,]", tree->name);
    scanf(", %f", &tree->points);
    tree->left = tree->right = NULL;
    return tree;
}

void insertTree(Tree **ptree, Tree *new) {
    int key = new->key;
    Tree *tree = *ptree;
    while (1) {
        if (key < tree->key) {
            if (tree->left != NULL) {
                tree = tree->left;
                continue;
            } else {
                tree->left = new;
                break;
            }
        } else if (key > tree->key) {
            if (tree->right != NULL) {
                tree = tree->right;
                continue;
            } else {
                tree->right = new;
                break;
            }
        } else if (key == tree->key) {
            break;
        }
        break;
    }
    return;
}

void removeTree(Tree **ptree, int key) {
    Tree *predecessor, *tree;
    predecessor = tree = *ptree;
    while (1) {
        if (key < tree->key) {
            if (tree->left == NULL)
                break;
            predecessor = tree;
            tree = tree->left;
            continue;
        } else if (key > tree->key) {
            if (tree->right == NULL)
                break;
            tree = tree->right;
            continue;
        } else if (key == tree->key) {
            break;
        }
        break;
    }
    return;
}

void printTree(Tree *tree) {
    if (tree->left != NULL)
        printTree(tree->left);
    printf("%s (%d) ", tree->name, tree->key);
    if (tree->right != NULL)
        printTree(tree->right);
}

// void freeTree(Tree **tree) {}

int main(void) {
    char command[17];
    Tree *tree = NULL;
    while (scanf(" %s", command) != EOF) {
        if (strcmp(command, "criar") == 0) {
            if (tree != NULL)
                //freeTree(&tree);
            continue;
        }
        if (strcmp(command, "inserir") == 0) {
            Tree *new = scanTree();
            if (tree == NULL) {
                tree = new;
            } else if (new != NULL){
                insertTree(&tree, new);
            }
            continue;
        }
        if (strcmp(command, "remover") == 0) {
            continue;
        }
        if (strcmp(command, "buscar") == 0) {
            continue;
        }
        if (strcmp(command, "imprimir") == 0) {
            if (tree != NULL)
                printTree(tree);
            continue;
        }
        if (strcmp(command, "minimo") == 0) {
            continue;
        }
        if (strcmp(command, "maximo") == 0) {
            continue;
        }
        if (strcmp(command, "sucessor") == 0) {
            continue;
        }
        if (strcmp(command, "predecessor") == 0) {
            continue;
        }
        if (strcmp(command, "buscar-intervalo") == 0) {
            continue;
        }
        if (strcmp(command, "terminar") == 0) {
            continue;
        }  
    }
}