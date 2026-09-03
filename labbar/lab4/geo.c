#include <stdio.h>


struct point
{
    int x;
    int y;
};

typedef struct point point_t;

struct rectangle
{
    point_t ul;
    point_t br;
};

typedef struct rectangle rectangle_t;

void translate(point_t *p1, point_t *p2)
{
  p1->x += p2->x;
  p1->y += p2->y;
}

void print_point(point_t *p)
{
    printf("point(%d, %d)", p->x, p->y);
}

void print_rect(rectangle_t *r)
{
    printf("rectangle(upper_left=");
    print_point(&r->ul);
    printf(", lower_right=");
    print_point(&r->br);
    printf(")");
}

point_t make_point(int x, int y)
{
    point_t p = {.x = x, .y = y};
    return p;
}

rectangle_t make_rect(int x1, int y1, int x2, int y2)
{
    rectangle_t r = {.ul = make_point(x1, y1), .br = make_point(x2, y2)};
    return r;
}

int area_rect(rectangle_t *r) {
    return (r->br.x - r->ul.x) * (r->br.y - r->ul.y);
}

int main(void)
{
    return 0;
}
