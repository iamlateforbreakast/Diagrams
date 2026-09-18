/* Textbox.c */
#include "Textbox.h"
#include "Constants.h"
#include "Object.h"
#include <stdlib.h> // For calloc, free

Object* Textbox_create(const void* params)
{
    if (!params) return 0;

    Object* self = (Object*)calloc(1, sizeof(Object));

    if (!self) return 0;

    self->type = TEXTBOX_TYPE;
    self->properties = (struct Textbox_Param*)params; // Store params directly
    self->destroy = Textbox_destroy;
    self->draw = Textbox_draw;

    return self;
}

void Textbox_destroy(Object* self)
{
    if (Object_is_invalid(self)) return;

    struct Textbox_Param* p = (struct Textbox_Param*)self->properties;

    // WARNING: Ensure you actually want the Textbox to own and destroy the Font.
    // If Fonts are shared across multiple UI elements, remove this line.
    if (p && p->font) {
        Font_destroy(p->font);
    }

    // Note: if 'params' was dynamically allocated when passed into Textbox_create,
    // it should also be freed here (free(p)).

    free(self);
}

// Calculates the bounding box (width and height) of the text in pixels.
void Textbox_get_bounding_box(Object* self, int* out_w, int* out_h)
{
    if (!self || !out_w || !out_h) return;

    struct Textbox_Param* p = (struct Textbox_Param*)self->properties;

    *out_w = 0;
    *out_h = 0;

    if (!p || !p->text || !p->font) return;

    // Actually call the font class to calculate the box
    Font_get_bounding_box(p->font, p->text, p->font_size, out_w, out_h);
}

void Textbox_draw(Object* self)
{
    if (Object_is_invalid(self)) return;

    struct Textbox_Param* p = (struct Textbox_Param*)self->properties;

    if (!p || !p->text || !p->font) return;

    // Fixed argument order to match Primitives.c
    draw_text(self, p->font, p->font_size, p->x, p->y, p->text);
}

void Textbox_add(Object* self, Object* child)
{
    // Unimplemented, likely meant for UI node-tree relationships
}
