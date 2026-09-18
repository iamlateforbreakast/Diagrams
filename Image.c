/* Image.c */
#include "Image.h"

#include "Root.h"
#include "stb_image_write.h"

#include <stdio.h>
#include <stdlib.h>

Image* Image_create(const char* filename, const int width, const int height,
    const int r, const int g, const int b)
{
  if (filename == 0) return 0;

  if ((width <= 0) || (height <= 0)) return 0;

  Image* self = (Image*)calloc(1, sizeof(Image));

  if (self == 0) return 0;

  self->buffer = (unsigned char*)malloc(width * height * CHANNELS);

  if (self->buffer == 0)
  {
    free(self);
    return 0;
  }

  /* Set background to r,g,b */
  for (int i = 0; i < width * height; i++)
  {
    self->buffer[i * CHANNELS] = r;
    self->buffer[i * CHANNELS + 1] = g;
    self->buffer[i * CHANNELS + 2] = b;
  }

  self->name = filename;
  self->width = width;
  self->height = height;
  self->root.type = ROOT_TYPE;
  self->root.properties = 0;
  self->root.children = 0;
  self->root.parent = 0;
  self->root.destroy = 0;
  self->root.draw = 0;

  return self;
}

void Image_destroy(Image* self)
{
  if (self == 0) return;
  
  /* Free the allocated pixel buffer */
  if (self->buffer != 0)
  {
    free(self->buffer);
  }
  
  Object_destroy(self->root.children);

  /* Free the main Image struct */
  free(self);
}

void Image_add(Image* self, Object* child)
{
  /* Safety check to ensure neither pointer is null */
  if (self == 0 || child == 0) return;

  Object* p = self->root.children;
  if (p == 0)
  {
    child->parent = &self->root;
    self->root.children = child;
  }
  else
  {
    printf("Error: Image children are assigned already.\n");
  }
}

void Image_generate(Image* self)
{
  Object_draw(self->root.children);
  int status = stbi_write_png(self->name, self->width, self->height, CHANNELS, self->buffer, self->width * CHANNELS);

  if (status == 0)
  {
    printf("Error: Failed to write %s\n", self->name);
  }
}
