#include <LDL/LDL_Image.hpp>
#include <stdio.h>

int main()
{
	LDL_ImageLoader imageLoader;

	int width;
	int heigth;
	int bpp;
	unsigned char* pixels;

	if (imageLoader.Load("test.png"))
	{
		width  = imageLoader.Width();
		heigth = imageLoader.Heigth();
		bpp    = imageLoader.Bpp();
		pixels = imageLoader.Pixels();
	}

	printf("width : %d", width);
    printf("heigth: %d", heigth);
    printf("bpp   : %d", bpp);
    printf("pixels: %p", pixels);
	
	return 0;
}