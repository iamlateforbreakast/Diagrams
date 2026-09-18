#ifndef TEXTBOX_H
#define TEXTBOX_H

#include "Object.h"
#include "Font.h"

struct Textbox_Param
{
  int x;
  int y;
  char *text;
  Font *font;
  float font_size;
};

Object* Textbox_create(struct Textbox_Param *params);
void Textbox_destroy(Object* self);
void Textbox_draw(Object* self);
void Textbox_add(Object* self, Object* child);
#endif /* TEXTBOX_H */
