/* Color.c */
#include "Color.h"

Color Color_make(unsigned char r, unsigned char g, unsigned char b)
{
    Color color = { r, g, b };
    return color;
}

Color Color_from_hex(unsigned long hex)
{
    Color color;
    color.r = (unsigned char)((hex >> 16) & 0xFF);
    color.g = (unsigned char)((hex >> 8) & 0xFF);
    color.b = (unsigned char)(hex & 0xFF);
    return color;
}

static unsigned char blend_channel(unsigned char dst, unsigned char src, float alpha)
{
    return (unsigned char)(dst * (1.0f - alpha) + src * alpha + 0.5f);
}

Color Color_blend(Color dst, Color src, float alpha)
{
    Color out;
    out.r = blend_channel(dst.r, src.r, alpha);
    out.g = blend_channel(dst.g, src.g, alpha);
    out.b = blend_channel(dst.b, src.b, alpha);
    return out;
}
