/*
Boost Software License - Version 1.0 - August 17th, 2003

Permission is hereby granted, free of charge, to any person or organization
obtaining a copy of the software and accompanying documentation covered by
this license (the "Software") to use, reproduce, display, distribute,
execute, and transmit the Software, and to prepare derivative works of the
Software, and to permit third-parties to whom the Software is furnished to
do so, all subject to the following:

The copyright notices in the Software and this entire statement, including
the above license grant, this restriction and the following disclaimer,
must be included in all copies of the Software, in whole or in part, and
all derivative works of the Software, unless such copies or derivative
works are solely in the form of machine-executable object code generated by
a source language processor.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
DEALINGS IN THE SOFTWARE.
*/

#include "Engine.hpp"
#include "Frm.hpp"

class PaletteLoader
{
public:
	bool Load(const char* path, LDL_Palette& palette)
	{
		_File = fopen(path, "rb");

		if (_File != NULL)
		{
			LDL_Color color;

			for (size_t i = 0; i < 256; i++)
			{
				size_t result = fread(&color, 3, 1, _File);

				palette.Set(i, color);
			}

			fclose(_File);

			return true;
		}

		return false;
	}
private:
	FILE* _File;
};

#if defined(__MSDOS__)
LDL_Vec2i windowSize(320, 200);
#else
LDL_Vec2i windowSize(800, 600);
#endif

int main()
{
	LDL_Palette palette;
	PaletteLoader paletteLoader;
	paletteLoader.Load("data/COLOR.PAL", palette);

	Engine engine(windowSize, &palette);
	engine.Run();

	return 0;
}