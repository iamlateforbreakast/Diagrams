/* main.c */
#include "Image.h"
#include "Constants.h"
#include "Palette.h"
#include "Box.h"
#include "Textbox.h"
#include "Font.h"
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	int error_status = FAILED;
	int width = 640;
	int height = 480;
	int background_r = ARCTIC_SUNRISE_RARIFIED_AIR_R;
	int background_g = ARCTIC_SUNRISE_RARIFIED_AIR_G;
	int background_b = ARCTIC_SUNRISE_RARIFIED_AIR_B;

	Image* image = Image_create("test.png", width, height,
		background_r, background_g, background_b);

	if (image == 0)
	{
		printf("Failed to allocate image.\n");
		return error_status;
	}

	struct Font_Param font1_param = { .name = "DroidSans.ttf" };
	Font* font1 = Font_create(&font1_param);

	if (font1 == 0)
	{
	  printf("Error: Cannot open font %s\n", font1_param.name);
	  exit(2);
	}

	struct Box_Param box1_param = {
		.x = 160, .y = 60, .w = 100, .h = 200,
		.r = ARCTIC_SUNRISE_AZURE_GREEN_BLUE_R,
		.g = ARCTIC_SUNRISE_AZURE_GREEN_BLUE_G,
		.b = ARCTIC_SUNRISE_AZURE_GREEN_BLUE_B
	};

	struct Textbox_Param textbox1_param = {
		.x = 120, .y = 100, .text = "hello",
		.font = font1, .font_size = 24.0f,
		.r = ARCTIC_SUNRISE_AZURE_GREEN_BLUE_R,
		.g = ARCTIC_SUNRISE_AZURE_GREEN_BLUE_G,
		.b = ARCTIC_SUNRISE_AZURE_GREEN_BLUE_B
	};

	Object* box1 = Box_create(&box1_param);
	Object* textbox1 = Textbox_create(&textbox1_param);

	Image_add(image, box1);
	Box_add(box1, textbox1);

	Image_generate(image);

	// Cleanup
	Image_destroy(image);
	Font_destroy(font1);  // Ensure Textbox_destroy no longer frees this!

	error_status = OK; // Update status so the program exits cleanly
	return error_status;
}
