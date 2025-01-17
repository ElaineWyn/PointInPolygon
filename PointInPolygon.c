#include <stdio.h>
#include <stdlib.h>

// To avoid libraries, simple struct for a point
typedef struct Point {
    double x, y;
    struct Point *next;
} Point;

// Function to check if a point is inside a polygon
int point_in_polygon(Point point, Point *polygon) {
    double x = point.x, y = point.y;
    int inside = 0;

    if (!polygon) return 0; // In case some buffon gives an empty polygon

    Point *p1 = polygon;
    Point *p2 = polygon->next;

    do {
        if (p2 == NULL) p2 = polygon;

        if (y > (p1->y < p2->y ? p1->y : p2->y)) {
            if (y <= (p1->y > p2->y ? p1->y : p2->y)) {
                if (x <= (p1->x > p2->x ? p1->x : p2->x)) {
                    double x_intersection = (y - p1->y) * (p2->x - p1->x) / (p2->y - p1->y) + p1->x;

                    if (p1->x == p2->x || x <= x_intersection) {
                        // Flip the inside flag
                        inside = !inside;
                    }
                }
            }
        }

        // Continue to the next point
        p1 = p2;
        p2 = p2->next;
    } while (p1 != polygon);
    
    return inside;
}

// Dummy Function to create a new point
Point *create_point(double x, double y) {
    Point *new_point = (Point *)malloc(sizeof(Point));
    if (!new_point) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    new_point->x = x;
    new_point->y = y;
    new_point->next = NULL;
    return new_point;
}

// Function to add a point to our polygon
void add_point(Point **polygon, double x, double y) {
    Point *new_point = create_point(x, y);
    if (!*polygon) {
        *polygon = new_point;
        new_point->next = new_point; // Make it circular
    } else {
        Point *temp = *polygon;
        while (temp->next != *polygon) {
            temp = temp->next;
        }
        temp->next = new_point;
        new_point->next = *polygon; // Maintain circularity
    }
}

// Function to free the linked list
void free_polygon(Point *polygon) {
    if (!polygon) return;

    Point *current = polygon;
    Point *next;

    do {
        next = current->next;
        free(current);
        current = next;
    } while (current != polygon);
}

int main() {
    // Define a point to test
    Point test_point = {182, 60, NULL};

    // Define a polygon
    Point *polygon = NULL;
    add_point(&polygon, 186, 14);
    add_point(&polygon, 186, 44);
    add_point(&polygon, 175, 115);
    add_point(&polygon, 175, 85);

    // Check if the point is inside the polygon
    if (point_in_polygon(test_point, polygon)) {
        printf("Point is inside the polygon\n");
    } else {
        printf("Point is outside the polygon\n");
    }

    // Free the allocated memory
    free_polygon(polygon);

    return 0;
}
