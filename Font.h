#ifndef FONT_H
#define FONT_H

#include "stb_truetype.h"

typedef struct Font Font;
struct Font_Param
{
	char* name;
};

Font* Font_create(struct Font_Param* params);
void Font_destroy(Font *self);
void Font_get_bounding_box(Font* self, char* text, float size, int* w, int* h);
void Font_calculate_baseline(Font* self, float size, int y, int* out_baseline, float* out_scale);
unsigned char* Font_render_character(Font* self, float scale, int codepoint, int* out_bw, int* out_bh, int* out_cx, int* out_cy, int* out_advance);
void Font_free_bitmap(Font* self, unsigned char* bitmap);
#endif /* FONT_H */
