typedef struct Node {
  int key;
  struct Node *left, *right;
  char *name;
  float points;
} Node;

typedef struct Tree {
  struct Node *root;
  unsigned number;
} Tree;

Tree *newTree(void);

Node *newNode(int, char *, float);

void freeTree_recursive(Node *);

void freeTree(Tree *);

int insertRecursion(Node **, int, char *, float);

void insert(Tree *, int, char *, float);

Node *removeMax(Node **);

Node *getMaxNode(Node *);

Node *getMinNode(Node *);

void removeNode(Tree *, int);

int treeMax(Tree *);

int treeMin(Tree *);

void print_recursive(Node *);

void printTree(Tree *);

Node *getNode(Tree *, int);

int getNextNode(Node *, int, int *);

int getPrevNode(Node *, int, int *);

int getRange_recursive(Node *, int a, int b);

int getRange(Tree *, int a, int b);