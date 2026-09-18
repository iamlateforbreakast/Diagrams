#ifndef BOX_H
#define BOX_H

#include "Object.h"

struct Box_Param
{
	int x;
	int y;
	int w;
	int h;
	int r;
	int g;
	int b;
};

Object* Box_create(const struct Box_Param *params);
void Box_destroy(Object* self);
void Box_draw(Object* self);
void Box_add(Object* self, Object* child);
#endif /* BOX_H */
