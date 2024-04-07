#include "Rectangle.h"
#include <stdlib.h>
#include <stdio.h>

Rectangle* create_rectangle(int label, int width, int height) {
    Rectangle *rect = (Rectangle*)malloc(sizeof(Rectangle));
    if (rect == NULL) {
        fprintf(stderr, "Memory allocation failed for rectangle\n");
        exit(EXIT_FAILURE);
    }
    rect->label = label;
    rect->width = width;
    rect->height = height;
    return rect;
}
