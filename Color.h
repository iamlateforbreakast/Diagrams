#ifndef COLOR_H
#define COLOR_H

/* An 8-bit-per-channel RGB colour. Matches CHANNELS in Constants.h: this
   library has no alpha channel of its own, so blending always takes its
   opacity as a separate parameter (glyph coverage, corner coverage, ...)
   rather than storing it on the Color. */
typedef struct Color
{
    unsigned char r;
    unsigned char g;
    unsigned char b;
} Color;

Color Color_make(unsigned char r, unsigned char g, unsigned char b);

/* Builds a Color from a packed 0xRRGGBB value, e.g. Color_from_hex(0x006C84). */
Color Color_from_hex(unsigned long hex);

/* Source-over blend of src onto dst by alpha (0 = keep dst, 1 = replace with src). */
Color Color_blend(Color dst, Color src, float alpha);

#endif /* COLOR_H */
