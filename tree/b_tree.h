typedef struct node
{
  void *data;
  int left_count;
  int right_count;
  struct node *left;
  struct node *right;
} Node;

typedef struct
{
  Node *root;
} Tree;

Tree *create_tree();
Node *create_node(void *data);
Node *add_node(Node *root, void *data, int((*compare)(void *a, void *b)));
void print_tree(Node *root, void (*print)(void *data));
void *search_tree(Node *root, void *data, int((*compare)(void *a, void *b)));
int tree_depth(Node *root);
int node_height(Node *root, void *data, int((*compare)(void *a, void *b)));
int node_depth(Node *root, void *data, int((*compare)(void *a, void *b)));
void print_leaves(Node *root, void (*print)(void *data));
Node *free_tree_data(Node *root, void *(*free_data)(void *data));
Tree *free_tree(Tree *tree, void *(*free_data)(void *data));
void save_in_file(Node *root, FILE *file, void (*save)(void *data, FILE *file));