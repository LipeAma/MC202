typedef struct Node {
    int key;
    struct Node *left, *right;
} Node;

typedef struct Tree {
    struct Node *root;
    unsigned number;
} Tree;

Tree *newTree(void);
Node *newNode(int);
void insert(Tree *, int);
int insertRecursion(Node **, int);
void removeNode(Tree *, int);
int removeRecursion(Node **, int);

Node *removeMax(Node **);
Node *getMaxNode(Node *);
Node *getMinNode(Node *);
int treeMax(Tree *);
int treeMin(Tree *);
int getNextNode(Node *, int);
void print_recursive(Node *);
void getRange(Tree *, int , int );
void getRange_recursive(Node *, int, int);
