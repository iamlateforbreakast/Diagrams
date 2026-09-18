/* Font.c */
#include "Font.h"
#include "stb_truetype.h"
#include <stdio.h>
#include <stdlib.h>

struct Font
{
    char* name;
    // stb_truetype requires the raw font file buffer to stay in memory
    unsigned char* font_buffer;
    stbtt_fontinfo font_info;
};

Font* Font_create(struct Font_Param* params)
{
    Font* self = (Font*)calloc(1, sizeof(Font));
    if (self == 0) return 0;

    self->name = params->name; // Assuming name is assigned from params

    FILE* font_file = fopen(self->name, "rb");
    if (font_file == 0)
    {
        fprintf(stderr, "Error: Failed to load font file: %s\n", self->name);
        free(self);
        return 0;
    }

    // Get file size
    fseek(font_file, 0, SEEK_END);
    long size = ftell(font_file);
    fseek(font_file, 0, SEEK_SET);

    self->font_buffer = (unsigned char*)malloc(size);
    if (self->font_buffer == 0)
    {
        fclose(font_file);
        free(self);
        return 0;
    }

    size_t read = fread(self->font_buffer, 1, size, font_file);
    fclose(font_file);

    // Initialize the font info
    if ((read != (size_t)size) ||
        !stbtt_InitFont(&self->font_info, self->font_buffer, stbtt_GetFontOffsetForIndex(self->font_buffer, 0)))
    {
        fprintf(stderr, "Error: Failed to initialize font!\n");
        free(self->font_buffer);
        free(self);
        return 0;
    }

    return self;
}

void Font_destroy(Font* self)
{
    if (self == 0) return;

    if (self->font_buffer) {
        free(self->font_buffer);
    }

    free(self);
}

void Font_get_bounding_box(Font* self, char* text, float font_size, int* out_w, int* out_h)
{
    float scale = stbtt_ScaleForPixelHeight(&self->font_info, font_size);

    int ascent, descent, lineGap;
    stbtt_GetFontVMetrics(&self->font_info, &ascent, &descent, &lineGap);

    *out_h = (int)((ascent - descent) * scale);

    float current_x = 0;

    for (int i = 0; text[i]; ++i) {
        int advance_width, left_side_bearing;
        stbtt_GetCodepointHMetrics(&self->font_info, text[i], &advance_width, &left_side_bearing);

        current_x += (advance_width * scale);

        // Add kerning if not the last character
        if (text[i + 1]) {
            int kern = stbtt_GetCodepointKernAdvance(&self->font_info, text[i], text[i + 1]);
            current_x += (kern * scale);
        }
    }

    *out_w = (int)current_x;
}

// --- NEW ABSTRACTION FUNCTIONS FOR PRIMITIVES ---

void Font_calculate_baseline(Font* self, float size, int y, int* out_baseline, float* out_scale)
{
    *out_scale = stbtt_ScaleForPixelHeight(&self->font_info, size);

    int ascent, descent, lineGap;
    stbtt_GetFontVMetrics(&self->font_info, &ascent, &descent, &lineGap);

    *out_baseline = y + (int)(ascent * (*out_scale));
}

unsigned char* Font_render_character(Font* self, float scale, int codepoint, int* out_bw, int* out_bh, int* out_cx, int* out_cy, int* out_advance)
{
    int left_side_bearing, x2, y2;

    stbtt_GetCodepointHMetrics(&self->font_info, codepoint, out_advance, &left_side_bearing);
    stbtt_GetCodepointBitmapBox(&self->font_info, codepoint, scale, scale, out_cx, out_cy, &x2, &y2);

    return stbtt_GetCodepointBitmap(&self->font_info, scale, scale, codepoint, out_bw, out_bh, 0, 0);
}

void Font_free_bitmap(Font* self, unsigned char* bitmap)
{
    stbtt_FreeBitmap(bitmap, self->font_info.userdata);
}
