#include <LDL/LDL.hpp>
#include <stdio.h>

int main()
{
	LDL_Result result;

	LDL_Window window(&result, LDL_Vec2i(0, 0), LDL_Vec2i(800, 600), "05Img");
	LDL_Render render(&window);

	LDL_FpsCounter     fpsCounter;
	LDL_NumberToString convert;

	LDL_Surface surf(LDL_Vec2i(800, 600), LDL_Vec2i(800, 600), 4);

	LDL_Color* pixels = (LDL_Color*)surf.Pixels();

	size_t count = surf.Size().x * surf.Size().y;

	for (size_t i = 0; i < count; i++)
	{
		pixels[i].r = 34;
		pixels[i].g = 177;
		pixels[i].b = 76;
		pixels[i].a = 255;
	}

	if (result.Ok())
	{
		LDL_Texture texture(surf.Size(), (uint8_t*)surf.Pixels(), surf.Bpp());

		render.SetColor(LDL_Color(0, 162, 232));

		LDL_Event report;

		while (window.Running())
		{
			fpsCounter.Start();

			while (window.GetEvent(report))
			{
				if (report.Type == LDL_Event::IsQuit)
				{
					window.StopEvent();
				}
			}

			render.Begin();

			render.SetColor(LDL_Color(0, 162, 232));
			render.Clear();

			render.Draw(&texture, LDL_Vec2i(0, 0));

			render.End();

			if (fpsCounter.Calc())
			{
				window.Title(convert.Convert(fpsCounter.Fps()));
				fpsCounter.Clear();
			}

			window.PollEvents();
		}
	}
	else
	{
		printf("%s/n", result.Message());
	}

	return 0;
}