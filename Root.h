#ifndef ROOT_H
#define ROOT_H

#include "Object.h"

Object* Root_create(const int* params);
void Root_destroy(Object* self);
void Root_draw(Object* self);

#endif /* ROOT_H */
