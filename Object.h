#ifndef OBJECT_H
#define OBJECT_H

#define OBJECT_VALID (0)
#define OBJECT_INVALID (1)

typedef struct Object Object;

struct Object
{
  int type;
  const void *properties;
  Object *parent;
  Object *children;
  void (*destroy)(Object *self);
  void (*draw)(Object *self);
};

void Object_destroy(Object* self);
void Object_draw(Object* self);
int Object_is_invalid(Object* self);
unsigned char* Object_getDrawingBuffer(Object* self);
int Object_getBufferHeight(Object* self);

#endif /* OBJECT_H */
