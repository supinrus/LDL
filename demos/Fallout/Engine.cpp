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

Engine::Engine(const LDL_Vec2i& size) :
	_PaletteLoader(&_ByteReader, "data/COLOR.PAL"),
	_Window(&_Result, LDL_Vec2i(0,0), size, "", LDL_WindowMode::Fixed),
	_Render(&_Window, _PaletteLoader.Result()),
	_FrmReader(&_ByteReader),
	_SpriteLoader(&_FrmReader, _PaletteLoader.Result()),
	_SpriteManager(&_SpriteLoader)
{
}

Engine::~Engine()
{
}

void Engine::Run()
{
	if (_Result.Ok())
	{
		LDL_Event report;

		while (_Window.Running())
		{
			_FpsCounter.Start();

			while (_Window.GetEvent(report))
			{
				if (report.Type == LDL_Event::IsQuit)
				{
					_Window.StopEvent();
				}
			}

			_Render.Begin();

			Sprite* sprite = _SpriteManager.GetSprite("data/art/critters/HANPWRAA.frm");
			_Render.Draw(sprite->GetFrame(0, 0)->GetImage(), LDL_Vec2i(5, 10));

			_Render.End();

			if (_FpsCounter.Calc())
			{
				_Window.Title(_Convert.Convert(_FpsCounter.Fps()));
				_FpsCounter.Clear();
			}

			_Window.PollEvents();
		}
	}
	else
	{
		printf("%s/n", _Result.Message());
	}
}