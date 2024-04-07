#ifndef NODE_H
#define NODE_H

#include <stdio.h>
#include "Rectangle.h"

typedef struct Node {
    char type; // 'V' or 'H' for cutline, or 0 for Rectangle
    Rectangle *rect; // Pointer to Rectangle for leaf nodes
    struct Node *left;
    struct Node *right;
} Node;

Node* create_node(char type);
Node* build_tree(FILE *input_file);
void postorder_traversal(Node *node, FILE *output_file);
void Compute_dimension(Node *node, FILE *output_file);
void Compute_coordinates(Node *node, int x, int y, FILE *output_file);

#endif /* NODE_H */
