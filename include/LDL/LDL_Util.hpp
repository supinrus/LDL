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

#ifndef LDL_Util_hpp
#define LDL_Util_hpp
/********************************************************************************************************************************
													   	 Includes
********************************************************************************************************************************/
#include <stdio.h>

#if defined(_WIN32)
#pragma comment(lib, "gdi32.lib" )
#pragma comment(lib, "winmm.lib" )
#pragma comment(lib, "user32.lib" )
#pragma comment(lib, "opengl32.lib" )

#define STRICT
#undef UNICODE
#undef _UNICODE

#ifdef NOMINMAX
#include <windows.h>
#else
#define NOMINMAX
#include <windows.h>
#undef NOMINMAX
#endif

#if !defined INVALID_ATOM
#define INVALID_ATOM ((ATOM)0)
#endif

#if !defined INVALID_FILE_ATTRIBUTES
#define INVALID_FILE_ATTRIBUTES ((DWORD)-1)
#endif

#if !defined VK_OEM_1
#define VK_OEM_1 0xBA
#endif

#if !defined VK_OEM_2
#define VK_OEM_2 0xBF
#endif

#if !defined VK_OEM_3
#define VK_OEM_3 0xC0
#endif

#if !defined VK_OEM_4
#define VK_OEM_4 0xDB
#endif

#if !defined VK_OEM_5
#define VK_OEM_5 0xDC
#endif

#if !defined VK_OEM_6
#define VK_OEM_6 0xDD
#endif

#if !defined VK_OEM_7
#define VK_OEM_7 0xDE
#endif

#if !defined VK_OEM_PLUS
#define VK_OEM_PLUS 0xBB
#endif

#if !defined VK_OEM_COMMA
#define VK_OEM_COMMA 0xBC
#endif

#if !defined VK_OEM_MINUS
#define VK_OEM_MINUS 0xBD
#endif

#if !defined VK_OEM_PERIOD
#define VK_OEM_PERIOD 0xBE
#endif

#if !defined WM_MOUSEWHEEL
#define WM_MOUSEWHEEL 0x020A
#endif

#if !defined WM_MOUSEHWHEEL
#define WM_MOUSEHWHEEL 0x020E
#endif
#elif defined(__unix__)
#endif
/********************************************************************************************************************************
														   Types
********************************************************************************************************************************/
typedef void(*LDL_VoidFuncPtr)(void);
/********************************************************************************************************************************
														  LDL_Color
********************************************************************************************************************************/
class LDL_NumberToString
{
public:
	const char* Convert(int num, unsigned char base = 10)
	{
		int i = 0;
		bool isNegative = false;

		/* Handle 0 explicitly, otherwise empty string is printed for 0 */
		if (num == 0)
		{
			_Buffer[i++] = '0';
			_Buffer[i] = '\0';
		}

		// In standard itoa(), negative numbers are handled only with
		// base 10. Otherwise numbers are considered unsigned.
		if (num < 0 && base == 10)
		{
			isNegative = true;
			num = -num;
		}

		// Process individual digits
		while (num != 0)
		{
			int rem = num % base;
			_Buffer[i++] = (rem > 9) ? (rem - 10) + 'a' : rem + '0';
			num = num / base;
		}

		// If number is negative, append '-'
		if (isNegative)
			_Buffer[i++] = '-';

		_Buffer[i] = '\0'; // Append string terminator

		// Reverse the string
		Reverse(_Buffer, i);

		return _Buffer;
	}

private:
	void Swap(char& t1, char& t2)
	{
		char tmp = t1;
		t1 = t2;
		t2 = tmp;
	}

	void Reverse(char* str, size_t length)
	{
		size_t start = 0;
		size_t end = length - 1;

		while (start < end)
		{
			Swap(*(str + start), *(str + end));
			start++;
			end--;
		}
	}

	char _Buffer[32];
	int _Result;
};
/********************************************************************************************************************************
														  LDL_Color
********************************************************************************************************************************/
class LDL_Color
{
public:
	LDL_Color() :
#if defined(_WIN32)
		b(0),
		g(0),
		r(0),
#else
		r(0),
		g(0),
		b(0),
#endif
		a(255)
	{
	}

	LDL_Color(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha = 255) :
#if defined(_WIN32)
		b(blue),
		g(green),
		r(red),
#else
		r(red),
		g(green),
		b(blue),
#endif
		a(alpha)
	{
	}

	int toInt() const
	{
		return (int)((r << 24) | (g << 16) | (b << 8) | a);
	}

#if defined(_WIN32)
	unsigned char b;
	unsigned char g;
	unsigned char r;
#else
	unsigned char r;
	unsigned char g;
	unsigned char b;
#endif
	unsigned char a;
};
/********************************************************************************************************************************
													      LDL_Mat4f
********************************************************************************************************************************/
class LDL_Mat4f
{
public:
	LDL_Mat4f()
	{
		Identity();
	}

	LDL_Mat4f& operator=(const LDL_Mat4f& source)
	{
		if (this == &source)
			return *this;

		memcpy(&_Values, source._Values, sizeof(_Values));

		return *this;
	}

	float* Values()
	{
		return _Values;
	}

	void Identity()
	{
		_Values[0] = 1;
		_Values[1] = 0;
		_Values[2] = 0;
		_Values[3] = 0;
		_Values[4] = 0;
		_Values[5] = 1;
		_Values[6] = 0;
		_Values[7] = 0;
		_Values[8] = 0;
		_Values[9] = 0;
		_Values[10] = 1;
		_Values[11] = 0;
		_Values[12] = 0;
		_Values[13] = 0;
		_Values[14] = 0;
		_Values[15] = 1;
	}

	LDL_Mat4f operator * (const LDL_Mat4f& m) const {
		LDL_Mat4f ret;

		ret._Values[0] = ((_Values[0] * m._Values[0]) + (_Values[1] * m._Values[4]) + (_Values[2] * m._Values[8]) + (_Values[3] * m._Values[12]));
		ret._Values[1] = ((_Values[0] * m._Values[1]) + (_Values[1] * m._Values[5]) + (_Values[2] * m._Values[9]) + (_Values[3] * m._Values[13]));
		ret._Values[2] = ((_Values[0] * m._Values[2]) + (_Values[1] * m._Values[6]) + (_Values[2] * m._Values[10]) + (_Values[3] * m._Values[14]));
		ret._Values[3] = ((_Values[0] * m._Values[3]) + (_Values[1] * m._Values[7]) + (_Values[2] * m._Values[11]) + (_Values[3] * m._Values[15]));

		ret._Values[4] = ((_Values[4] * m._Values[0]) + (_Values[5] * m._Values[4]) + (_Values[6] * m._Values[8]) + (_Values[7] * m._Values[12]));
		ret._Values[5] = ((_Values[4] * m._Values[1]) + (_Values[5] * m._Values[5]) + (_Values[6] * m._Values[9]) + (_Values[7] * m._Values[13]));
		ret._Values[6] = ((_Values[4] * m._Values[2]) + (_Values[5] * m._Values[6]) + (_Values[6] * m._Values[10]) + (_Values[7] * m._Values[14]));
		ret._Values[7] = ((_Values[4] * m._Values[3]) + (_Values[5] * m._Values[7]) + (_Values[6] * m._Values[11]) + (_Values[7] * m._Values[15]));

		ret._Values[8] = ((_Values[8] * m._Values[0]) + (_Values[9] * m._Values[4]) + (_Values[10] * m._Values[8]) + (_Values[11] * m._Values[12]));
		ret._Values[9] = ((_Values[8] * m._Values[1]) + (_Values[9] * m._Values[5]) + (_Values[10] * m._Values[9]) + (_Values[11] * m._Values[13]));
		ret._Values[10] = ((_Values[8] * m._Values[2]) + (_Values[9] * m._Values[6]) + (_Values[10] * m._Values[10]) + (_Values[11] * m._Values[14]));
		ret._Values[11] = ((_Values[8] * m._Values[3]) + (_Values[9] * m._Values[7]) + (_Values[10] * m._Values[11]) + (_Values[11] * m._Values[15]));

		ret._Values[12] = ((_Values[12] * m._Values[0]) + (_Values[13] * m._Values[4]) + (_Values[14] * m._Values[8]) + (_Values[15] * m._Values[12]));
		ret._Values[13] = ((_Values[12] * m._Values[1]) + (_Values[13] * m._Values[5]) + (_Values[14] * m._Values[9]) + (_Values[15] * m._Values[13]));
		ret._Values[14] = ((_Values[12] * m._Values[2]) + (_Values[13] * m._Values[6]) + (_Values[14] * m._Values[10]) + (_Values[15] * m._Values[14]));
		ret._Values[15] = ((_Values[12] * m._Values[3]) + (_Values[13] * m._Values[7]) + (_Values[14] * m._Values[11]) + (_Values[15] * m._Values[15]));

		return ret;
	}

	float _Values[16];
};
/********************************************************************************************************************************
												LDL_Mat4f - functions
********************************************************************************************************************************/
LDL_Mat4f Ortho(float left, float right, float bottom, float top, float farv, float nearv)
{
	LDL_Mat4f result;

	result._Values[0] = (2.0f / (right - left));
	result._Values[5] = (2.0f / (top - bottom));
	result._Values[10] = (-1.0);
	result._Values[12] = (-(right + left) / (right - left));
	result._Values[13] = (-(top + bottom) / (top - bottom));
	result._Values[14] = (-(farv + nearv) / (farv - nearv));

	return result;
}
/********************************************************************************************************************************
														LDL_Vec2i
********************************************************************************************************************************/
class LDL_Vec2i
{
public:
	LDL_Vec2i() :
		x(0),
		y(0)
	{
	}

	LDL_Vec2i(int x, int y) :
		x(x),
		y(y)
	{
	}

	int x;
	int y;
};
/********************************************************************************************************************************
														LDL_Result
********************************************************************************************************************************/
class LDL_Result
{
public:
	enum
	{
		Max = 64
	};

	LDL_Result()
	{
		Clear();
	}

	void Clear()
	{
		_Ok = true;
		memset(&_Message, 0, Max);
	}

	bool Ok()
	{
		return _Ok;
	}

	const char* Message()
	{
		return _Message;
	}

	void Message(const char* message)
	{
		Clear();

		_Ok = false;
		strcpy(_Message, message);
	}
private:
	bool _Ok;
	char _Message[Max];
};
/********************************************************************************************************************************
													      LDL_Abort
********************************************************************************************************************************/
void LDL_Abort(const char* message, const char* detail)
{
	printf("%s %s/n", message, detail);
	abort();
}

void LDL_Abort(const char* message)
{
	LDL_Abort(message, "");
}

void LDL_Abort()
{
	LDL_Abort("", "");
}
/********************************************************************************************************************************
									                        Ticks
********************************************************************************************************************************/
#if defined(_WIN32)
size_t LDL_Ticks()
{
	return timeGetTime();
}

void LDL_Delay(size_t count)
{
	Sleep((DWORD)count);
}
#endif
/********************************************************************************************************************************
													      LDL_Library
********************************************************************************************************************************/
#if defined(_WIN32)
class LDL_Library
{
public:
	bool Open(const char* path)
	{
		Close();

		_HMODULE = LoadLibrary(path);

		return _HMODULE != NULL;
	}

	void Close()
	{
		if (_HMODULE != NULL)
		{
			FreeLibrary(_HMODULE);
		}
	}

	~LDL_Library()
	{
		Close();
	}

	LDL_VoidFuncPtr Function(const char* name)
	{
		return (LDL_VoidFuncPtr)GetProcAddress(_HMODULE, name);
	}
private:
	HMODULE _HMODULE;
};
#elif defined(__unix__) 
#endif
/********************************************************************************************************************************
												       LDL_OpenGLFunctions
********************************************************************************************************************************/
#if defined(_WIN32)
class LDL_OpenGLFunctions
{
public:
	LDL_OpenGLFunctions()
	{
		_Library.Open("opengl32.dll");
	}

	~LDL_OpenGLFunctions()
	{
		_Library.Close();
	}

	LDL_VoidFuncPtr Function(const char* name)
	{
		LDL_VoidFuncPtr result = (LDL_VoidFuncPtr)wglGetProcAddress(name);

		if (IsValid(result))
		{
			result = _Library.Function(name);

			if (result == NULL)
			{
				LDL_Abort("Not found function:", name);
			}
		}

		return result;
	}
private:
	bool IsValid(LDL_VoidFuncPtr ptr)
	{
		return (ptr == 0 || (ptr == (LDL_VoidFuncPtr)0x1) || (ptr == (LDL_VoidFuncPtr)0x2) || (ptr == (LDL_VoidFuncPtr)0x3) || (ptr == (LDL_VoidFuncPtr)-1));
	}

	LDL_Library _Library;
};
#elif defined(__unix__) 
#endif
/********************************************************************************************************************************
													   LDL_FpsCounter
********************************************************************************************************************************/
class LDL_FpsCounter
{
public:
	LDL_FpsCounter() :
		_Current(0),
		_Delta(0),
		_Old(0),
		_Fps(0)
	{
	}

	void Start()
	{
		_Current = LDL_Ticks();
	}

	bool Calc()
	{
		_Fps++;

		_Delta = LDL_Ticks() - _Current;

		_Old += _Delta;

		if (_Old >= 1000)
		{
			return  true;
		}

		return false;
	}

	size_t Fps()
	{
		return _Fps;
	}

	void Clear()
	{
		_Fps = 0;
		_Old = 0;
	}
private:
	size_t _Current;
	size_t	_Delta;
	size_t	_Old;
	size_t _Fps;
};
/********************************************************************************************************************************
													   LDL_FpsLimiter
********************************************************************************************************************************/
class LDL_FpsLimiter
{
public:
	LDL_FpsLimiter(size_t fps = 60) :
		_Fps(fps),
		_Ticks(0)
	{
	}

	void Mark()
	{
		_Ticks = LDL_Ticks();
	}

	void Throttle() const
	{
		if (1000 / _Fps > LDL_Ticks() - _Ticks)
		{
			LDL_Delay(1000 / _Fps - (LDL_Ticks() - _Ticks));
		}
	}
private:
	size_t _Fps;
	size_t _Ticks;
};

#endif
