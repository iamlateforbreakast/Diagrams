/* Primitives.c */
#include "Primitives.h"
#include "Constants.h"
#include "Object.h"
// stb_truetype.h is intentionally removed to ensure isolation

void draw_rectangle(Object* obj, int x, int y, int w, int h, int r, int g, int b) {
    if (w < 1) w = 1; // Ensure even 0-tick tasks show up as at least 1 pixel wide

    unsigned char* drawing_buffer = Object_getDrawingBuffer(obj);
    int buffer_height = Object_getBufferHeight(obj);

    for (int i = y; i < y + h; i++)
    {
        for (int j = x; j < x + w; j++)
        {
            if (i >= 0 && i < buffer_height && j >= 0 && j < IMG_WIDTH)
            {
                int idx = (i * IMG_WIDTH + j) * CHANNELS;
                drawing_buffer[idx + 0] = r;
                drawing_buffer[idx + 1] = g;
                drawing_buffer[idx + 2] = b;
            }
        }
    }
}

void draw_line(Object* obj, int x0, int y0, int x1, int y1, int r, int g, int b) {

    unsigned char* drawing_buffer = Object_getDrawingBuffer(obj);
    int buffer_height = Object_getBufferHeight(obj);

    // Calculate differences and directions
    int dx = (x1 > x0 ? x1 - x0 : x0 - x1);
    int sx = x0 < x1 ? 1 : -1;
    int dy = -(y1 > y0 ? y1 - y0 : y0 - y1);
    int sy = y0 < y1 ? 1 : -1;

    int err = dx + dy;
    int e2;

    while (1)
    {
        // Bounds check before drawing the pixel
        if (x0 >= 0 && x0 < IMG_WIDTH && y0 >= 0 && y0 < buffer_height)
        {
            int idx = (y0 * IMG_WIDTH + x0) * CHANNELS;
            drawing_buffer[idx + 0] = r;
            drawing_buffer[idx + 1] = g;
            drawing_buffer[idx + 2] = b;
        }

        // Check if we have reached the destination pixel
        if (x0 == x1 && y0 == y1)
        {
            break;
        }

        // Calculate error for the next step
        e2 = 2 * err;

        if (e2 >= dy)
        {
            err += dy;
            x0 += sx;
        }
        if (e2 <= dx) {
            err += dx;
            y0 += sy;
        }
    }
}

void draw_text(Object* obj, Font* font, float size, int x, int y, const char* text)
{
    unsigned char* drawing_buffer = Object_getDrawingBuffer(obj);
    int buffer_height = Object_getBufferHeight(obj);

    float scale;
    int baseline;

    // Retrieve metrics from the Font object rather than calling STB directly
    Font_calculate_baseline(font, size, y, &baseline, &scale);

    for (int i = 0; text[i]; ++i)
    {
        int advance_width, bw, bh, c_x1, c_y1;

        unsigned char* bitmap = Font_render_character(font, scale, text[i], &bw, &bh, &c_x1, &c_y1, &advance_width);

        if (bitmap)
        {
            int y_offset = baseline + c_y1;
            int x_offset = x + c_x1;

            // Blit
            for (int r = 0; r < bh; r++)
            {
                for (int c = 0; c < bw; c++)
                {
                    int img_y = y_offset + r;
                    int img_x = x_offset + c;

                    if (img_x >= 0 && img_x < IMG_WIDTH && img_y >= 0 && img_y < buffer_height)
                    {
                        int img_idx = (img_y * IMG_WIDTH + img_x) * CHANNELS;
                        float alpha = bitmap[r * bw + c] / 255.0f;
                        drawing_buffer[img_idx + 0] = (unsigned char)(drawing_buffer[img_idx + 0] * (1.0f - alpha));
                        drawing_buffer[img_idx + 1] = (unsigned char)(drawing_buffer[img_idx + 1] * (1.0f - alpha));
                        drawing_buffer[img_idx + 2] = (unsigned char)(drawing_buffer[img_idx + 2] * (1.0f - alpha));
                    }
                }
            }

            Font_free_bitmap(font, bitmap);
        }

        x += (int)(advance_width * scale);
    }
}
