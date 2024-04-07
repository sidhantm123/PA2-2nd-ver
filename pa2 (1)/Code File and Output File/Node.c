#include "Node.h"
#include <stdlib.h>

Node* create_node(char type) {
    Node *new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        fprintf(stderr, "Memory allocation failed for node\n");
        exit(EXIT_FAILURE);
    }
    new_node->type = type;
    new_node->rect = NULL;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

Node* build_tree(FILE *input_file) {
    char line[20]; // Assuming maximum line length is 20 characters

    // Read the first line of the input file
    fgets(line, sizeof(line), input_file);
    char type = line[0];

    // Create the root node
    Node *root = create_node(type);

    // If the root is a leaf node (rectangle), create a rectangle object and assign it to the root
    if (type != 'V' && type != 'H') {
        int label, width, height;
        sscanf(line, "%d(%d,%d)\n", &label, &width, &height);
        root->rect = create_rectangle(label, width, height);
    } else {
        // If the root is an internal node, recursively build the left and right subtrees
        root->left = build_tree(input_file);
        root->right = build_tree(input_file);
    }

    return root;
}

void postorder_traversal(Node *node, FILE *output_file) {
    if (node == NULL) return;

    postorder_traversal(node->left, output_file);
    postorder_traversal(node->right, output_file);

    if (node->type != 'V' && node->type != 'H') {
        fprintf(output_file, "%d(%d,%d)\n", node->rect->label, node->rect->width, node->rect->height);
    } else {
        fprintf(output_file, "%c\n", node->type);
    }
}

void Compute_dimension(Node *node, FILE *output_file) {
    if (node == NULL) return;

    Compute_dimension(node->left, output_file);
    Compute_dimension(node->right, output_file);

    if (node->type != 'V' && node->type != 'H') {
        fprintf(output_file, "%d(%d,%d)\n", node->rect->label, node->rect->width, node->rect->height);
    } else {
        int width = 0, height = 0;

        if (node->left != NULL && node->left->rect != NULL) {
            width += node->left->rect->width;
            height = node->left->rect->height;
        }

        if (node->type == 'V') {
            if (node->right != NULL && node->right->rect != NULL) {
                height = (node->right->rect->height < height) ? height : node->right->rect->height;
                width += node->right->rect->width;
                node->rect = create_rectangle(0, width, height);
            }
            fprintf(output_file, "%c(%d,%d)\n", node->type, width, height);
        } else if (node->type == 'H') {
            if (node->right != NULL && node->right->rect != NULL) {
                width = (node->right->rect->width < width) ? width : node->right->rect->width;
                height += node->right->rect->height;
                node->rect = create_rectangle(0, width, height);
            }
            fprintf(output_file, "%c(%d,%d)\n", node->type,  width, height);
        }
    }
}

void Compute_coordinates(Node *node, int x, int y, FILE *output_file) {
    if (node == NULL) return;

    if (node->type != 'V' && node->type != 'H') {
        fprintf(output_file, "%d((%d,%d)(%d,%d))\n", node->rect->label,node->rect->width,node->rect->height, x, y);
    } else {
        int left_x = x, left_y = y;
        int right_x = x, right_y = y;

        if (node->left != NULL && node->left->rect != NULL) {
            left_x = x;
            left_y = y;

            if (node->type == 'H') {
                left_x = x;
                left_y = y + node->left->rect->height;
            }
            Compute_coordinates(node->left, left_x, left_y, output_file);
        }

        if (node->right != NULL && node->right->rect != NULL) {
            right_x = x;
            right_y = y;

            if (node->type == 'V') {
                right_x = x + node->left->rect->width;
                right_y = y;
            }
            Compute_coordinates(node->right, right_x, right_y, output_file);
        }
    }
}
