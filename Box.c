/* Box.c */
#include "Box.h"

#include "Constants.h"
#include "Object.h"
#include "Primitives.h"
#include "Image.h"

#include <stdlib.h>

Object *Box_create(const struct Box_Param *params)
{
  Object *self = (Object*)calloc(1, sizeof(Object));

  if (self == 0) return 0;

  self->type = BOX_TYPE;
  self->properties = params;
  self->parent = 0;
  self->children = 0;
  self->destroy = Box_destroy;
  self->draw = Box_draw;

  return self;
}

void Box_destroy(Object *self)
{
  if (Object_is_invalid(self->children)) return;

  Object_destroy(self->children);
}

void Box_add(Object* self, Object* child)
{
	self->children = child;
	child->parent = self;
}

void Box_draw(Object *self)
{
  const struct Box_Param* p = (const struct Box_Param*)self->properties;
  int x = p->x;
  int y = p->y;
  int w = p->w;
  int h = p->h;
  int r = p->r;
  int g = p->g;
  int b = p->b;

  draw_rectangle(self->parent, x, y, w, h, r, g, b);

  if (self->children!=0) Object_draw(self->children);

}
