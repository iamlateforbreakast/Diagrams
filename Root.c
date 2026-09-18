/* Root.c */
#include "Root.h"

#include "Constants.h"
#include "Object.h"
#include "Primitives.h"
#include "Image.h"

#include <stdlib.h>

Object* Root_create(const int* params)
{
	Object* self = (Object*)calloc(1, sizeof(Object));

	if (self == 0) return 0;

	self->type = ROOT_TYPE;
	self->properties = params;
	self->parent = 0;
	self->children = 0;
	self->destroy = Root_destroy;
	self->draw = Root_draw;

	return self;
}

void Root_destroy(Object* self)
{
	(void)self;
	//Object_destroy(self);
}

void Root_draw(Object* self)
{
	if (self->parent->type == ROOT_TYPE)
	{
		Image* image = (Image*)self->parent;
		(void)image;
		//draw_rectangle(image->buffer, image->height, x, y, w, h, r, g, b);
	}
	else
	{
		//Object_draw_rectangle(self->parent, x, y, w, h, r, g, b);
	}
}
