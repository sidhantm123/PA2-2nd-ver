#include <stdio.h>
#include <stdlib.h>
#include "Node.h"

int main(int argc, char *argv[]) {
    // Check if correct number of command-line arguments are provided
    if (argc != 5) {
        fprintf(stderr, "Usage: %s <input_file> <output_file> <output_file1> <output_file2>\n", argv[0]);
        return EXIT_FAILURE;
    }

    // Open input file
    FILE *input_file = fopen(argv[1], "r");
    if (input_file == NULL) {
        fprintf(stderr, "Error opening input file: %s\n", argv[1]);
        return EXIT_FAILURE;
    }

    // Build the binary tree
    Node *root = build_tree(input_file);
    fclose(input_file);

    // Open output file for post-order traversal
    FILE *output_file = fopen(argv[2], "w");
    if (output_file == NULL) {
        fprintf(stderr, "Error opening output file: %s\n", argv[2]);
        return EXIT_FAILURE;
    }

    // Perform post-order traversal and write to output file 1
    postorder_traversal(root, output_file);
    fclose(output_file);

    // Open output file for computing dimensions
    FILE *output_file1 = fopen(argv[3], "w");
    if (output_file1 == NULL) {
        fprintf(stderr, "Error opening output file: %s\n", argv[3]);
        return EXIT_FAILURE;
    }

    // Compute the dimensions and write into output file 2
    Compute_dimension(root, output_file1);
    fclose(output_file1);

    // Open output file for writing the coordinates
    FILE *output_file2 = fopen(argv[4], "w");
    if (output_file2 == NULL) {
        fprintf(stderr, "Error opening output file: %s\n", argv[4]);
        return EXIT_FAILURE;
    }

    // Calculate the coordinates and write to output file 3
    Compute_coordinates(root, 0, 0, output_file2);
    fclose(output_file2);

    return EXIT_SUCCESS;
}
