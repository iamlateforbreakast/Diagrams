#ifndef PRIMITIVES_H
#define PRIMITIVES_H

#include "Constants.h"
#include "Object.h"
#include "Font.h"

void draw_rectangle(Object *obj, int x, int y, int w, int h, int r, int g, int b);
void draw_line(Object *obj, int x0, int y0, int x1, int y1, int r, int g, int b);
void draw_line_thick(Object *obj, int x0, int y0, int x1, int y1, int weight, int r, int g, int b);
void draw_text(Object* obj, Font* font, float size, int x0, int y0);

#endif /* PRIMITIVES_H */
