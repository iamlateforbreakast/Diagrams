/* stb_impl.c - single translation unit holding the stb_* implementations. */

#include <stdio.h>

/* stb_image_write.h ships with __STDC_LIB_EXT1__ force-defined, so it reaches
   for the Annex K sprintf_s that glibc does not provide. Map it onto snprintf,
   which has the same bounded-write semantics here. */
#if !defined(_MSC_VER)
#define sprintf_s(buf, sz, ...) snprintf(buf, sz, __VA_ARGS__)
#endif

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#define STB_TRUETYPE_IMPLEMENTATION
#include "stb_truetype.h"
