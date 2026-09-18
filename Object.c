/* Object.c */
#include "Object.h"

#include "Image.h"

void Object_destroy(Object* self)
{
  // TBC: destroy all children
  self->destroy(self);
}

int Object_is_invalid(Object* self)
{
  if (self != 0) return OBJECT_VALID;
  return OBJECT_INVALID;
}

void Object_draw(Object* self)
{
  self->draw(self);
}

unsigned char* Object_getDrawingBuffer(Object* self)
{
  if (Object_is_invalid(self)) return 0;

  if (self->type == ROOT_TYPE)
  {
	Image* image = (Image*)self;
	return image->buffer;
  }
  else
  {
	return Object_getDrawingBuffer(self->parent);
  }
}

int Object_getBufferHeight(Object* self)
{
  if (Object_is_invalid(self)) return 0;

  if (self->type == ROOT_TYPE)
  {
	Image* image = (Image*)self;
	return image->height;
  }
  else
  {
	return Object_getBufferHeight(self->parent);
  }
}
