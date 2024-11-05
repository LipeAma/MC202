enum Insert {
  HAS_GROWN,
  HASNT_GROWN,
  MUST_ROTATE_RIGHT,
  MUST_ROTATE_LEFT_RIGHT,
  MUST_ROTATE_LEFT,
  MUST_ROTATE_RIGHT_LEFT,
};

enum BalancingFactor {
  LEFT_IS_TOO_BIG = 2,
  LEFT_IS_BIGGER = 1,
  SAME = 0,
  RIGHT_IS_BIGGER = -1,
  RIGHT_IS_TOO_BIG = -2,
};

typedef struct AVLnode {
  enum BalancingFactor factor;
  int key;
  struct AVLnode *right, *left;
} AVLnode;

typedef struct AVLtree {
  struct AVLnode *root;
  unsigned size;
} AVLtree;

typedef struct AVLinfo {
  struct AVLnode *parent, *result, *last_right, *last_left;
} AVLinfo;

AVLtree *AVLnew(void);

void AVLfree(AVLtree *tree);

void AVLfree_recursive(AVLnode *node);

AVLnode *AVLinsert(AVLtree *, int);

enum Insert AVLinsert_recursion(AVLnode *, AVLnode *, int);

AVLnode *AVLrotateRight(AVLnode *);

AVLnode *AVLrotateLeft(AVLnode *);

int AVLremove(AVLtree *, int);

AVLnode *AVLnext(AVLnode *, int);

AVLnode *AVLprev(AVLnode *, int);

AVLnode *AVLget(AVLnode *, int);

AVLinfo *AVLgetinfo(AVLnode *, int);

unsigned AVLrange(AVLnode *, int, int, int *);