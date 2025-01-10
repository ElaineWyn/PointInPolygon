#include <stdio.h>
#include <stdbool.h>
#include <math.h>

// Simple struct for a point
typedef struct
{
	double x, y;
} Point;

// Function to check if a point is inside a polygon
bool point_in_polygon(Point point, Point *polygon, int num_vertices)
{
	double x = point.x, y = point.y;
	bool inside = false;

	Point p1 = polygon[0], p2;

	for (int i = 1; i <= num_vertices; i++)
	{
		p2 = polygon[i % num_vertices];
		// Check point against vertexes of the polygon
		if (y > fmin(p1.y, p2.y))
		{
			if (y <= fmax(p1.y, p2.y))
			{
				if (x <= fmax(p1.x, p2.x))
				{
					double x_intersection = (y - p1.y) * (p2.x - p1.x) / (p2.y - p1.y) + p1.x;

					if (p1.x == p2.x || x <= x_intersection)
					{
						// Flip the inside flag
						inside = !inside;
					}
				}
			}
		}

		// Store the current point as the first point for the next iteration
		p1 = p2;
	}

	// Return the value of the inside flag
	return inside;
}

int main()
{
	// Define a point to test
	Point point = {182, 60};

	// Define a polygon
	Point polygon[] = {
		{186, 14}, {186, 44}, {175, 115}, {175, 85}};
	int num_vertices = sizeof(polygon) / sizeof(polygon[0]);

	// Check if the point is inside the polygon
	if (point_in_polygon(point, polygon, num_vertices))
	{
		printf("Point is inside the polygon\n");
	}
	else
	{
		printf("Point is outside the polygon\n");
	}

	return 0;
}
