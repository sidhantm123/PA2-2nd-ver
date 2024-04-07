#ifndef RECTANGLE_H
#define RECTANGLE_H

typedef struct Rectangle {
    int label;
    int width;
    int height;
} Rectangle;

Rectangle* create_rectangle(int label, int width, int height);

#endif /* RECTANGLE_H */
