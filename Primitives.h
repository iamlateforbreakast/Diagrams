#ifndef PRIMITIVES_H
#define PRIMITIVES_H

#include "Constants.h"
#include "Object.h"
#include "Font.h"
#include "Color.h"

void draw_rectangle(Object *obj, int x, int y, int w, int h, Color color);
void draw_line(Object *obj, int x0, int y0, int x1, int y1, Color color);
void draw_line_thick(Object *obj, int x0, int y0, int x1, int y1, int weight, Color color);
void draw_text(Object* obj, Font* font, float size, int x, int y, const char* text, Color color);

#endif /* PRIMITIVES_H */
