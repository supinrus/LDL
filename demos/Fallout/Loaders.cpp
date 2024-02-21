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

#include "Loaders.hpp"

PaletteLoader::PaletteLoader(ByteReader* reader, const char* path) :
	_Reader(reader)
{
	_Reader->Open(path);

	if (_Reader->IsOpen())
	{
		LDL_Color color;

		for (size_t i = 0; i < 256; i++)
		{
			color.r = _Reader->u8();
			color.g = _Reader->u8();
			color.b = _Reader->u8();

			_Palette.Set(i, color);
		}

		_Reader->Close();
	}
}

LDL_Palette* PaletteLoader::Result()
{
	return &_Palette;
}

SpriteLoader::SpriteLoader(FrmReader* frmReader, LDL_Palette* palette) :
	_FrmReader(frmReader),
	_Palette(palette)
{
}

Sprite* SpriteLoader::GetSprite(const char* path)
{
	Sprite* result = NULL;

	if (_FrmReader->Open(path))
	{
		_FrmReader->ReadFrmFile(&_FrmFile);

		_FrmReader->ReadFrmFrame(&_FrmFrame);

		result = new Sprite();

		LDL_Texture* texture = new LDL_Texture(LDL_Vec2i(_FrmFrame.width, _FrmFrame.height), _FrmFrame.indexes, _Palette);
		
		SpriteFrame* frame = new SpriteFrame(texture);
		
		result->Append(0, frame);
	}

	return result;
}
