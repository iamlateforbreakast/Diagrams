#ifndef TEXTBOX_H
#define TEXTBOX_H

#include "Object.h"
#include "Font.h"
#include "Color.h"

struct Textbox_Param
{
  int x;
  int y;
  char *text;
  Font *font;
  float font_size;
  Color color;
};

Object* Textbox_create(const struct Textbox_Param *params);
void Textbox_destroy(Object* self);
void Textbox_draw(Object* self);
void Textbox_add(Object* self, Object* child);
#endif /* TEXTBOX_H */
