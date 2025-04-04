#include <stdlib.h>
#include <stdio.h>
#include "b_tree.h"

Tree *create_tree()
{
  Tree *tree = (Tree *)calloc(1, sizeof(Tree));
  if (tree == NULL)
  {
    printf("Error creating tree\n");
    return NULL;
  }
  return tree;
}

Node *create_node(void *data)
{
  if (data == NULL)
  {
    printf("Error creating node: data is NULL\n");
    return NULL;
  }
  Node *node = (Node *)calloc(1, sizeof(Node));
  node->data = data;
  return node;
}

Node *add_node(Node *root, void *data, int((*compare)(void *a, void *b)))
{
  if (!root)
  {
    return create_node(data);
  }

  if (compare(root->data, data) > 0)
  {
    printf("Adding to left\n");
    root->left_count++;
    root->left = add_node(root->left, data, compare);
    return root;
  }
  printf("Adding to right\n");
  root->right_count++;
  root->right = add_node(root->right, data, compare);
  return root;
}

void print_tree(Node *root, void (*print)(void *data))
{
  if (!root)
    return;
  print_tree(root->left, print);
  print(root->data);
  printf("LEFT: %d\n", root->left_count);
  printf("RIGHT: %d\n\n", root->right_count);
  print_tree(root->right, print);
}

void *search_tree(Node *root, void *data, int((*compare)(void *a, void *b)))
{
  if (!root)
    return NULL;
  if (compare(root->data, data) == 0)
    return root->data;
  if (compare(root->data, data) < 0)
    return search_tree(root->right, data, compare);
  return search_tree(root->left, data, compare);
}

int tree_depth(Node *root)
{
  if (!root)
    return 0;
  int left_height = tree_depth(root->left);
  int right_height = tree_depth(root->right);
  return (left_height > right_height ? left_height : right_height) + 1;
}

int node_height(Node *root, void *data, int((*compare)(void *a, void *b)))
{
  if (!root)
    return -1;
  if (compare(root->data, data) == 0)
    return tree_depth(root)-1;
  if (compare(root->data, data) < 0)
    return node_height(root->right, data, compare);
  return node_height(root->left, data, compare);
}

int node_depth(Node *root, void *data, int((*compare)(void *a, void *b)))
{
  if (!root)
    return -1;
  if (compare(root->data, data) == 0)
    return 0;
  if (compare(root->data, data) < 0)
    return node_depth(root->right, data, compare) + 1;
  return node_depth(root->left, data, compare) + 1;
}

void print_leaves(Node *root, void (*print)(void *data))
{
  if (!root)
    return;
  if (!root->left && !root->right)
  {
    print(root->data);
    printf("LEFT: %d\n", root->left_count);
    printf("RIGHT: %d\n\n", root->right_count);
    return;
  }
  print_leaves(root->left, print);
  print_leaves(root->right, print);
}

Node *free_tree_data(Node *root, void *(*free_data)(void *data))
{
  if (!root)
    return NULL;
  root->left = free_tree_data(root->left, free_data);
  root->data = free_data(root->data);
  root->right = free_tree_data(root->right, free_data);
  free(root);
  return NULL;
}

Tree *free_tree(Tree *tree, void *(*free_data)(void *data))
{
  if (!tree)
    return NULL;
  tree->root = free_tree_data(tree->root, free_data);
  free(tree);
  return NULL;
}

void save_in_file(Node *root, FILE *file, void (*save)(void *data, FILE *file))
{
  if (!root)
    return;
  save(root->data, file);
  fprintf(file, "LEFT : %d\n", root->left_count);
  fprintf(file, "RIGHT: %d\n", root->right_count);
  fprintf(file, "\n");
  save_in_file(root->left, file, save);
  save_in_file(root->right, file, save);
}
