#ifndef IMAGE_H
#define IMAGE_H
#include "Constants.h"
#include "Object.h"
#include "Color.h"

//typedef struct Object Object;

typedef struct Image Image;

struct Image
{
  Object root;
  const char *name;
  unsigned char *buffer;
  int width;
  int height;
};

Image* Image_create(const char *filename, const int width, const int height,
	Color background);
void Image_destroy(Image *self);
void Image_add(Image* self, Object* child);
void Image_generate(Image *self);

#endif /* IMAGE_H */
