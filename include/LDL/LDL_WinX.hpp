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

#ifndef LDL_WinX_hpp
#define LDL_WinX_hpp
/********************************************************************************************************************************
														Defines
********************************************************************************************************************************/
#if defined(_WIN32)
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
#endif

/********************************************************************************************************************************
														Includes
********************************************************************************************************************************/
#include "LDL_Util.hpp"
#include <string.h>
#include <assert.h>
/********************************************************************************************************************************
                                                        Enums
********************************************************************************************************************************/
class LDL_KeyboardKey
{
public:
	enum
	{
		Unknown = 1,
		LSystem,
		RSystem,
		Menu,
		Semicolon,
		Slash,
		Equal,
		Hyphen,
		LBracket,
		RBracket,
		Comma,
		Period,
		Quote,
		Backslash,
		Tilde,
		Escape,
		Space,
		Enter,
		Backspace,
		Tab,
		PageUp,
		PageDown,
		End,
		Home,
		Insert,
		Delete,
		Add,
		Subtract,
		Multiply,
		Divide,
		Pause,
		F1,
		F2,
		F3,
		F4,
		F5,
		F6,
		F7,
		F8,
		F9,
		F10,
		F11,
		F12,
		F13,
		F14,
		F15,
		Left,
		Right,
		Up,
		Down,
		Numpad0,
		Numpad1,
		Numpad2,
		Numpad3,
		Numpad4,
		Numpad5,
		Numpad6,
		Numpad7,
		Numpad8,
		Numpad9,
		A,
		Z,
		E,
		R,
		T,
		Y,
		U,
		I,
		O,
		P,
		Q,
		S,
		D,
		F,
		G,
		H,
		J,
		K,
		L,
		M,
		W,
		X,
		C,
		V,
		B,
		N,
		Num0,
		Num1,
		Num2,
		Num3,
		Num4,
		Num5,
		Num6,
		Num7,
		Num8,
		Num9,
		Leftshift,
		RightShift,
		LeftControl,
		RightControl
	};
};

class LDL_ButtonState
{
public:
	enum
	{
		Pressed = 1,
		Released
	};
};

class LDL_MouseButton
{
public:
	enum
	{
		Left = 1,
		Right,
		Middle
	};
};

class LDL_MouseScroll
{
public:
	enum
	{
		Vertical = 1,
		Horizontal
	};
};

class LDL_WindowMode
{
public:
	enum
	{
		Resized = 1,
		Fixed,
		FullScreen
	};
};
/********************************************************************************************************************************
														Events
********************************************************************************************************************************/
class LDL_EventQuit
{
public:
	unsigned char Type;
};

class LDL_EventMouse
{
public:
	unsigned char Type;
	size_t  PosX;
	size_t  PosY;
	unsigned char State;
	unsigned char Button;
	size_t  Scroll;
	size_t  Delta;
};

class LDL_EventResize
{
public:
	unsigned char Type;
	size_t Width;
	size_t Height;
};

class LDL_EventKeyboard
{
public:
	unsigned char Type;
	unsigned char State;
	unsigned char Key;
};

class LDL_EventGainedFocus
{
public:
	unsigned char Type;
};

class LDL_EventLostFocus
{
public:
	unsigned char Type;
};
/********************************************************************************************************************************
														LDL_Event
********************************************************************************************************************************/
class LDL_Event
{
public:
	enum
	{
		IsQuit = 1,
		IsMouseMove,
		IsMouseClick,
		IsResize,
		IsKeyboard,
		IsGainedFocus,
		IsLostFocus,
		IsMouseScroll
	};

	union
	{
		unsigned char Type;
		LDL_EventQuit        Quit;
		LDL_EventMouse       Mouse;
		LDL_EventResize      Resize;
		LDL_EventKeyboard    Keyboard;
		LDL_EventGainedFocus GainedFocus;
		LDL_EventLostFocus   LostFocus;
	};

	bool IsKeyPressed(unsigned char key)
	{
		return (Type == IsKeyboard && Keyboard.Key == key && Keyboard.State == LDL_ButtonState::Pressed);
	}

	bool IsKeyReleased(unsigned char key)
	{
		return (Type == IsKeyboard && Keyboard.Key == key && Keyboard.State == LDL_ButtonState::Released);
	}

	bool IsMousePressed(unsigned char key)
	{
		return (Type == IsMouseClick && Mouse.Button == key && Mouse.State == LDL_ButtonState::Pressed);
	}

	bool IsMouseReleased(unsigned char key)
	{
		return (Type == IsMouseClick && Mouse.Button == key && Mouse.State == LDL_ButtonState::Released);
	}
private:
};
/********************************************************************************************************************************
														LDL_EventQueue
********************************************************************************************************************************/
class LDL_EventQueue
{
public:
	enum
	{
		Max = 256
	};
	LDL_EventQueue() :
		_Head(-1),
		_Tail(0),
		_Length(0),
		_Capacity(Max)
	{
		memset(_Content, 0, sizeof(_Content));
	}

	bool IsEmpty()
	{
		return _Length == 0;
	}

	bool IsFull()
	{
		return _Length == _Capacity;
	}

	size_t NextPosition(size_t position)
	{
		return (position + 1) % _Capacity;
	}

	bool Dequeue(LDL_Event& element)
	{
		if (!IsEmpty())
		{
			element = _Content[_Tail];
			_Tail = NextPosition(_Tail);
			_Length--;

			return true;
		}

		return false;
	}

	void Enqueue(const LDL_Event& element)
	{
		_Head = NextPosition(_Head);

		_Content[_Head] = element;

		if (IsFull())
			_Tail = NextPosition(_Tail);
		else
			_Length++;
	}
private:
	LDL_Event _Content[Max];
	size_t _Head;
	size_t _Tail;
	size_t _Length;
	size_t _Capacity;
};
/********************************************************************************************************************************
														LDL_Eventer
********************************************************************************************************************************/
class LDL_Eventer
{
public:
	LDL_Eventer() :
		_Running(true)
	{
	}

	void Push(LDL_Event& event)
	{
		_Queue.Enqueue(event);
	}

	bool Pop(LDL_Event& event)
	{
		if (!_Queue.IsEmpty())
		{
			_Queue.Dequeue(event);

			return true;
		}

		return false;
	}

	bool Running()
	{
		return _Running;
	}

	void Stop()
	{
		_Running = false;
	}

	bool Empty()
	{
		return _Queue.IsEmpty();
	}
private:
	bool _Running;
	LDL_EventQueue _Queue;
};
/********************************************************************************************************************************
											   	    	LDL_BaseWindow
********************************************************************************************************************************/
class LDL_BaseWindow
{
public:
	enum
	{
		Max = 64
	};

	LDL_BaseWindow(const LDL_Vec2i& pos, const LDL_Vec2i& size, const char* title, int mode) :
		_Pos(pos),
		_Size(size),
		_WindowMode(mode)
	{
		Title(title);
	}

	~LDL_BaseWindow()
	{
	}

	const char* Title()
	{
		return _Title;
	}

	void Title(const char* title)
	{
		memset(_Title, 0, Max);
		strcpy(_Title, title);
	}

	const LDL_Vec2i& Pos()
	{
		return _Pos;
	}

	void Pos(const LDL_Vec2i& pos)
	{
		_Pos = pos;
	}

	const LDL_Vec2i& Size()
	{
		return _Size;
	}

	void Size(const LDL_Vec2i& size)
	{
		_Size = size;
	}

	int Mode()
	{
		return _WindowMode;
	}
private:
	LDL_Vec2i _Pos;
	LDL_Vec2i _Size;
	char      _Title[Max];
	int       _WindowMode;
};
/********************************************************************************************************************************
													   LDL_Surface
********************************************************************************************************************************/
class LDL_Surface
{
public:
	LDL_Surface(const LDL_Vec2i& capacity, int bpp):
		_Bpp(bpp),
		_Capacity(capacity),
		_Size(capacity)
	{
		assert(bpp >= 0 && bpp <= 4);

		_Pixels = (unsigned char*)malloc(_Capacity.x * _Capacity.y * bpp);
	}

	LDL_Surface(const LDL_Vec2i& capacity, const LDL_Vec2i& size, int bpp) :
		_Bpp(bpp),
		_Capacity(capacity),
		_Size(size)
	{
		assert(bpp >= 0 && bpp <= 4);
		assert(size.x <= capacity.x);
		assert(size.y <= capacity.y);

		_Pixels = (unsigned char*)malloc(_Capacity.x * _Capacity.y * bpp);
	}

	~LDL_Surface()
	{
		free(_Pixels);
	}

	const LDL_Vec2i& Capacity()
	{
		return _Capacity;
	}

	const LDL_Vec2i& Size()
	{
		return _Size;
	}
private:
	int _Bpp;
	LDL_Vec2i _Capacity;
	LDL_Vec2i _Size;
	unsigned char* _Pixels;
};
/********************************************************************************************************************************
													   LDL_PixelCopier
********************************************************************************************************************************/
class LDL_PixelCopier
{
public:
private:
};
/********************************************************************************************************************************
									         	   	  LDL_MainWindow
********************************************************************************************************************************/
#if defined(_WIN32)
static const char LDL_AppName[] = "MainWindow";
static const UINT period = 1;

class LDL_MainWindow
{
public:
	LDL_MainWindow(LDL_Result* result, const LDL_Vec2i& pos, const LDL_Vec2i& size, const char* title, int mode) :
		_Result(result),
		_BaseWindow(pos, size, title, mode)
	{
		timeBeginPeriod(period);
		
		ZeroMemory(&_WNDCLASS, sizeof(WNDCLASS));
		ZeroMemory(&_HINSTANCE, sizeof(HINSTANCE));
		ZeroMemory(&_MSG, sizeof(MSG));
		ZeroMemory(&_ATOM, sizeof(ATOM));
		ZeroMemory(&_HWND, sizeof(HWND));
		ZeroMemory(&_HDC, sizeof(HDC));

		if (!InitHinstance())
			return;

		if (!InitWndClass())
			return;

		if (!InitStyle())
			return;

		if (!InitAdjustRect())
			return;

		if (!InitHwnd())
			return;

		if (!InitHdc())
			return;

		Title(title);
	}

	~LDL_MainWindow()
	{
		timeEndPeriod(period);

		UnregisterClass(LDL_AppName, _HINSTANCE);
		ReleaseDC(_HWND, _HDC);
		PostQuitMessage(0);
	}

	void Update()
	{
		ShowWindow(_HWND, SW_SHOW);
	}

	unsigned char ConvertKey(size_t key)
	{
		switch (key)
		{
		case VK_LWIN:       return LDL_KeyboardKey::LSystem;
		case VK_RWIN:       return LDL_KeyboardKey::RSystem;
		case VK_APPS:       return LDL_KeyboardKey::Menu;
		case VK_OEM_1:      return LDL_KeyboardKey::Semicolon;
		case VK_OEM_2:      return LDL_KeyboardKey::Slash;
		case VK_OEM_PLUS:   return LDL_KeyboardKey::Equal;
		case VK_OEM_MINUS:  return LDL_KeyboardKey::Hyphen;
		case VK_OEM_4:      return LDL_KeyboardKey::LBracket;
		case VK_OEM_6:      return LDL_KeyboardKey::RBracket;
		case VK_OEM_COMMA:  return LDL_KeyboardKey::Comma;
		case VK_OEM_PERIOD: return LDL_KeyboardKey::Period;
		case VK_OEM_7:      return LDL_KeyboardKey::Quote;
		case VK_OEM_5:      return LDL_KeyboardKey::Backslash;
		case VK_OEM_3:      return LDL_KeyboardKey::Tilde;
		case VK_ESCAPE:     return LDL_KeyboardKey::Escape;
		case VK_SPACE:      return LDL_KeyboardKey::Space;
		case VK_RETURN:     return LDL_KeyboardKey::Enter;
		case VK_BACK:       return LDL_KeyboardKey::Backspace;
		case VK_TAB:        return LDL_KeyboardKey::Tab;
		case VK_PRIOR:      return LDL_KeyboardKey::PageUp;
		case VK_NEXT:       return LDL_KeyboardKey::PageDown;
		case VK_END:        return LDL_KeyboardKey::End;
		case VK_HOME:       return LDL_KeyboardKey::Home;
		case VK_INSERT:     return LDL_KeyboardKey::Insert;
		case VK_DELETE:     return LDL_KeyboardKey::Delete;
		case VK_ADD:        return LDL_KeyboardKey::Add;
		case VK_SUBTRACT:   return LDL_KeyboardKey::Subtract;
		case VK_MULTIPLY:   return LDL_KeyboardKey::Multiply;
		case VK_DIVIDE:     return LDL_KeyboardKey::Divide;
		case VK_PAUSE:      return LDL_KeyboardKey::Pause;
		case VK_F1:         return LDL_KeyboardKey::F1;
		case VK_F2:         return LDL_KeyboardKey::F2;
		case VK_F3:         return LDL_KeyboardKey::F3;
		case VK_F4:         return LDL_KeyboardKey::F4;
		case VK_F5:         return LDL_KeyboardKey::F5;
		case VK_F6:         return LDL_KeyboardKey::F6;
		case VK_F7:         return LDL_KeyboardKey::F7;
		case VK_F8:         return LDL_KeyboardKey::F8;
		case VK_F9:         return LDL_KeyboardKey::F9;
		case VK_F10:        return LDL_KeyboardKey::F10;
		case VK_F11:        return LDL_KeyboardKey::F11;
		case VK_F12:        return LDL_KeyboardKey::F12;
		case VK_F13:        return LDL_KeyboardKey::F13;
		case VK_F14:        return LDL_KeyboardKey::F14;
		case VK_F15:        return LDL_KeyboardKey::F15;
		case VK_LEFT:       return LDL_KeyboardKey::Left;
		case VK_RIGHT:      return LDL_KeyboardKey::Right;
		case VK_UP:         return LDL_KeyboardKey::Up;
		case VK_DOWN:       return LDL_KeyboardKey::Down;
		case VK_NUMPAD0:    return LDL_KeyboardKey::Numpad0;
		case VK_NUMPAD1:    return LDL_KeyboardKey::Numpad1;
		case VK_NUMPAD2:    return LDL_KeyboardKey::Numpad2;
		case VK_NUMPAD3:    return LDL_KeyboardKey::Numpad3;
		case VK_NUMPAD4:    return LDL_KeyboardKey::Numpad4;
		case VK_NUMPAD5:    return LDL_KeyboardKey::Numpad5;
		case VK_NUMPAD6:    return LDL_KeyboardKey::Numpad6;
		case VK_NUMPAD7:    return LDL_KeyboardKey::Numpad7;
		case VK_NUMPAD8:    return LDL_KeyboardKey::Numpad8;
		case VK_NUMPAD9:    return LDL_KeyboardKey::Numpad9;
		case 'A':           return LDL_KeyboardKey::A;
		case 'Z':           return LDL_KeyboardKey::Z;
		case 'E':           return LDL_KeyboardKey::E;
		case 'R':           return LDL_KeyboardKey::R;
		case 'T':           return LDL_KeyboardKey::T;
		case 'Y':           return LDL_KeyboardKey::Y;
		case 'U':           return LDL_KeyboardKey::U;
		case 'I':           return LDL_KeyboardKey::I;
		case 'O':           return LDL_KeyboardKey::O;
		case 'P':           return LDL_KeyboardKey::P;
		case 'Q':           return LDL_KeyboardKey::Q;
		case 'S':           return LDL_KeyboardKey::S;
		case 'D':           return LDL_KeyboardKey::D;
		case 'F':           return LDL_KeyboardKey::F;
		case 'G':           return LDL_KeyboardKey::G;
		case 'H':           return LDL_KeyboardKey::H;
		case 'J':           return LDL_KeyboardKey::J;
		case 'K':           return LDL_KeyboardKey::K;
		case 'L':           return LDL_KeyboardKey::L;
		case 'M':           return LDL_KeyboardKey::M;
		case 'W':           return LDL_KeyboardKey::W;
		case 'X':           return LDL_KeyboardKey::X;
		case 'C':           return LDL_KeyboardKey::C;
		case 'V':           return LDL_KeyboardKey::V;
		case 'B':           return LDL_KeyboardKey::B;
		case 'N':           return LDL_KeyboardKey::N;
		case '0':           return LDL_KeyboardKey::Num0;
		case '1':           return LDL_KeyboardKey::Num1;
		case '2':           return LDL_KeyboardKey::Num2;
		case '3':           return LDL_KeyboardKey::Num3;
		case '4':           return LDL_KeyboardKey::Num4;
		case '5':           return LDL_KeyboardKey::Num5;
		case '6':           return LDL_KeyboardKey::Num6;
		case '7':           return LDL_KeyboardKey::Num7;
		case '8':           return LDL_KeyboardKey::Num8;
		case '9':           return LDL_KeyboardKey::Num9;
		case VK_LSHIFT:     return LDL_KeyboardKey::Leftshift;
		case VK_RSHIFT:     return LDL_KeyboardKey::RightShift;
		case VK_LCONTROL:   return LDL_KeyboardKey::LeftControl;
		case VK_RCONTROL:   return LDL_KeyboardKey::RightControl;
		}

		return LDL_KeyboardKey::Unknown;
	}

	LRESULT CALLBACK Handler(UINT Message, WPARAM WParam, LPARAM LParam)
	{
		LDL_Event event;

		ZeroMemory(&event, sizeof(event));

		switch (Message)
		{
		case WM_PAINT:
			break;

		case WM_DESTROY:
			break;

		case WM_MOUSEMOVE:
			event.Type = LDL_Event::IsMouseMove;
			event.Mouse.PosX = LOWORD(LParam);
			event.Mouse.PosY = HIWORD(LParam);
			_Eventer.Push(event);
			break;

		case WM_LBUTTONDOWN:
			event.Type = LDL_Event::IsMouseClick;
			event.Mouse.State = LDL_ButtonState::Pressed;
			event.Mouse.Button = LDL_MouseButton::Left;
			event.Mouse.PosX = LOWORD(LParam);
			event.Mouse.PosY = HIWORD(LParam);
			_Eventer.Push(event);
			break;

		case WM_LBUTTONUP:
			event.Type = LDL_Event::IsMouseClick;
			event.Mouse.State = LDL_ButtonState::Released;
			event.Mouse.Button = LDL_MouseButton::Left;
			event.Mouse.PosX = LOWORD(LParam);
			event.Mouse.PosY = HIWORD(LParam);
			_Eventer.Push(event);
			break;

		case WM_RBUTTONDOWN:
			event.Type = LDL_Event::IsMouseClick;
			event.Mouse.State = LDL_ButtonState::Pressed;
			event.Mouse.Button = LDL_MouseButton::Right;
			event.Mouse.PosX = LOWORD(LParam);
			event.Mouse.PosY = HIWORD(LParam);
			_Eventer.Push(event);
			break;

		case WM_RBUTTONUP:
			event.Type = LDL_Event::IsMouseClick;
			event.Mouse.State = LDL_ButtonState::Released;
			event.Mouse.Button = LDL_MouseButton::Right;
			event.Mouse.PosX = LOWORD(LParam);
			event.Mouse.PosY = HIWORD(LParam);
			_Eventer.Push(event);
			break;

		case WM_MBUTTONDOWN:
			event.Type = LDL_Event::IsMouseClick;
			event.Mouse.State = LDL_ButtonState::Pressed;
			event.Mouse.Button = LDL_MouseButton::Middle;
			event.Mouse.PosX = LOWORD(LParam);
			event.Mouse.PosY = HIWORD(LParam);
			_Eventer.Push(event);
			break;

		case WM_MBUTTONUP:
			event.Type = LDL_Event::IsMouseClick;
			event.Mouse.State = LDL_ButtonState::Released;
			event.Mouse.Button = LDL_MouseButton::Middle;
			event.Mouse.PosX = LOWORD(LParam);
			event.Mouse.PosY = HIWORD(LParam);
			_Eventer.Push(event);
			break;

		case WM_SIZE:
			event.Type = LDL_Event::IsResize;
			event.Resize.Width = LOWORD(LParam);
			event.Resize.Height = HIWORD(LParam);
			_Eventer.Push(event);
			break;

		case WM_CLOSE:
			event.Type = LDL_Event::IsQuit;
			_Eventer.Push(event);
			break;

		case WM_KEYDOWN:
		case WM_SYSKEYDOWN:
			event.Type = LDL_Event::IsKeyboard;
			event.Keyboard.State = LDL_ButtonState::Pressed;
			event.Keyboard.Key = ConvertKey(WParam);
			_Eventer.Push(event);
			break;

		case WM_KEYUP:
		case WM_SYSKEYUP:
			event.Type = LDL_Event::IsKeyboard;
			event.Keyboard.State = LDL_ButtonState::Released;
			event.Keyboard.Key = ConvertKey(WParam);
			_Eventer.Push(event);
			break;

		case WM_SETFOCUS:
			event.Type = LDL_Event::IsGainedFocus;
			_Eventer.Push(event);
			break;

		case WM_KILLFOCUS:
			event.Type = LDL_Event::IsLostFocus;
			_Eventer.Push(event);
			break;

		case WM_MOUSEWHEEL:
			event.Type = LDL_Event::IsMouseScroll;
			event.Mouse.Scroll = LDL_MouseScroll::Vertical;
			event.Mouse.Delta = HIWORD(WParam);
			event.Mouse.PosX = LOWORD(LParam);
			event.Mouse.PosY = HIWORD(LParam);
			_Eventer.Push(event);
			break;

		case WM_MOUSEHWHEEL:
			event.Type = LDL_Event::IsMouseScroll;
			event.Mouse.Scroll = LDL_MouseScroll::Vertical;
			event.Mouse.Delta = HIWORD(WParam);
			event.Mouse.PosX = LOWORD(LParam);
			event.Mouse.PosY = HIWORD(LParam);
			_Eventer.Push(event);
			break;
		}

		return DefWindowProc(_HWND, Message, WParam, LParam);
	}

	static LRESULT CALLBACK WndProc(HWND Hwnd, UINT Message, WPARAM WParam, LPARAM LParam)
	{
		LRESULT result;

#ifdef _WIN64
		LDL_MainWindow* This = (LDL_MainWindow*)GetWindowLongPtr(Hwnd, GWLP_USERDATA);
#elif _WIN32
		LDL_MainWindow* This = (LDL_MainWindow*)GetWindowLong(Hwnd, GWL_USERDATA);
#endif  

		if (This != NULL)
			result = This->Handler(Message, WParam, LParam);
		else
			result = DefWindowProc(Hwnd, Message, WParam, LParam);

		return result;
	}

	bool InitHinstance()
	{
		_HINSTANCE = GetModuleHandle(NULL);

		if (_HINSTANCE == NULL)
			_Result->Message("GetModuleHandle failed");

		return _Result->Ok();
	}

	bool InitWndClass()
	{
		_WNDCLASS.hInstance     = _HINSTANCE;
		_WNDCLASS.lpszClassName = LDL_AppName;
		_WNDCLASS.lpfnWndProc   = WndProc;
		_WNDCLASS.style         = CS_HREDRAW | CS_VREDRAW;
		_WNDCLASS.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
		_WNDCLASS.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
		_WNDCLASS.hCursor       = LoadCursor(NULL, IDC_ARROW);

		_ATOM = RegisterClass(&_WNDCLASS);

		if (_ATOM == INVALID_ATOM)
			_Result->Message("RegisterClass failed");

		return _Result->Ok();
	}

	bool InitStyle()
	{
		if (_BaseWindow.Mode() == LDL_WindowMode::Fixed)
			_Style = WS_OVERLAPPED | WS_SYSMENU;
		else if (_BaseWindow.Mode() == LDL_WindowMode::Resized)
			_Style = WS_OVERLAPPEDWINDOW;
		else
			_Result->Message("WindowMode failed");

		return _Result->Ok();
	}

	bool InitAdjustRect()
	{
		_Rect.left   = (LONG)_BaseWindow.Pos().x;
		_Rect.top    = (LONG)_BaseWindow.Pos().y;
		_Rect.right  = (LONG)_BaseWindow.Size().x;
		_Rect.bottom = (LONG)_BaseWindow.Size().y;

		if (!AdjustWindowRect(&_Rect, _Style, FALSE))
			_Result->Message("AdjustWindowRect failed");

		return _Result->Ok();
	}

	bool InitHwnd()
	{
		_HWND = CreateWindow(LDL_AppName, "", _Style, (int)_BaseWindow.Pos().x, (int)_BaseWindow.Pos().y, _Rect.right - _Rect.left, _Rect.bottom - _Rect.top, 0, 0, _HINSTANCE, 0);

		if (_HWND == INVALID_HANDLE_VALUE)
		{
			_Result->Message("CreateWindow failed");
		}
		else
		{

#ifdef _WIN64
			SetWindowLongPtr(_HWND, GWLP_WNDPROC, (LONG_PTR)WndProc);
			SetWindowLongPtr(_HWND, GWLP_USERDATA, (LONG_PTR)this);
#elif _WIN32
			SetWindowLong(_HWND, GWL_WNDPROC, (LONG)WndProc);
			SetWindowLong(_HWND, GWL_USERDATA, (LONG)this);
#endif  

		}

		return _Result->Ok();
	}

	bool InitHdc()
	{
		_HDC = GetDC(_HWND);

		if (_HDC == INVALID_HANDLE_VALUE)
			_Result->Message("GetDC failed");

		return _Result->Ok();
	}

	bool Running()
	{
		return _Eventer.Running();
	}

	void PollEvents()
	{
		while (PeekMessage(&_MSG, _HWND, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&_MSG);
			DispatchMessage(&_MSG);
		}
	}

	bool GetEvent(LDL_Event& event)
	{
		if (!_Eventer.Empty())
		{
			_Eventer.Pop(event);

			return true;
		}

		return false;
	}

	bool WaitEvent(LDL_Event& event)
	{
		if (_Eventer.Running())
		{
			if (GetMessage(&_MSG, _HWND, 0, 0) == -1)
			{
				_Result->Message("GetMessage failed");
			}
			else
			{
				_Eventer.Pop(event);

				TranslateMessage(&_MSG);
				DispatchMessage(&_MSG);
			}
		}

		return _Eventer.Running();
	}

	void StopEvent()
	{
		_Eventer.Stop();
	}

	void Title(const char* title)
	{
		_BaseWindow.Title(title);

		SetWindowText(_HWND, _BaseWindow.Title());
	}

	const char* Title()
	{
		return _BaseWindow.Title();
	}

	const LDL_Vec2i& Size()
	{
		RECT rect;

		if (!GetClientRect(_HWND, &rect))
			_Result->Message("GetClientRect failed");

		_BaseWindow.Size(LDL_Vec2i(rect.right + Pos().x, rect.bottom + Pos().y));

		return _BaseWindow.Size();
	}

	const LDL_Vec2i& Pos()
	{
		return _BaseWindow.Pos();
	}
private:
	LDL_Result*    _Result;
	LDL_BaseWindow _BaseWindow;
	LDL_Eventer    _Eventer;
	WNDCLASS       _WNDCLASS;
	HINSTANCE      _HINSTANCE;
	MSG            _MSG;
	ATOM           _ATOM;
	DWORD          _Style;
	RECT           _Rect;
public:
	HWND           _HWND;
	HDC            _HDC;
};
#elif defined(__unix__) 
#endif
/********************************************************************************************************************************
												    LDL_MainWindow - OpenGL 1
********************************************************************************************************************************/
#if defined(_WIN32) && defined(LDL_RENDER_OPENGL1)
class LDL_Window
{
public:
	LDL_Window(LDL_Result* result, const LDL_Vec2i& pos, const LDL_Vec2i& size, const char* title, int mode = LDL_WindowMode::Resized) :
		_Result(result),
		_HGLRC(NULL),
		_Window(result, pos, size, title, mode)
	{
		PIXELFORMATDESCRIPTOR pfd;

		ZeroMemory(&pfd, sizeof(PIXELFORMATDESCRIPTOR));

		if (!_Result->Ok())
			return;

		_Window._HDC = GetDC(_Window._HWND);

		if (_Window._HDC == NULL)
		{
			_Result->Message("GetDC failed");
			return;
		}

		pfd.nSize = sizeof(pfd);
		pfd.nVersion = 1;
		pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
		pfd.iPixelType = PFD_TYPE_RGBA;
		pfd.cColorBits = 24;
		pfd.cDepthBits = 16;
		pfd.iLayerType = PFD_MAIN_PLANE;

		int format = ChoosePixelFormat(_Window._HDC, &pfd);

		if (format == 0)
		{
			_Result->Message("ChoosePixelFormat failed");
			return;
		}

		if (!SetPixelFormat(_Window._HDC, format, &pfd))
		{
			_Result->Message("SetPixelFormat failed");
			return;
		}

		_HGLRC = wglCreateContext(_Window._HDC);

		if (_HGLRC == NULL)
		{
			_Result->Message("wglCreateContext failed");
			return;
		}

		if (!wglMakeCurrent(_Window._HDC, _HGLRC))
		{
			_Result->Message("wglMakeCurrent failed");
			return;
		}
	}

	~LDL_Window()
	{
		wglMakeCurrent(NULL, NULL);
		wglDeleteContext(_HGLRC);

		ReleaseDC(_Window._HWND, _Window._HDC);
	}

	bool Running()
	{
		return _Window.Running();
	}

	void Present()
	{
		if (!SwapBuffers(_Window._HDC))
		{
			_Result->Message("SwapBuffers failed");
		}

		Update();
	}

	void PollEvents()
	{
		_Window.PollEvents();
	}

	const LDL_Vec2i& Size()
	{
		return _Window.Size();
	}

	const LDL_Vec2i& Pos()
	{
		return _Window.Pos();
	}

	bool GetEvent(LDL_Event& event)
	{
		return _Window.GetEvent(event);
	}

	bool WaitEvent(LDL_Event& event)
	{
		return _Window.WaitEvent(event);
	}

	void StopEvent()
	{
		_Window.StopEvent();
	}

	const char* Title()
	{
		return _Window.Title();
	}

	void Title(const char* title)
	{
		_Window.Title(title);
	}

	void* NativeHandle()
	{
		return _Window._HWND;
	}

	void Update()
	{
		_Window.Update();
	}
private:
	LDL_Result* _Result;
	HGLRC _HGLRC;
	LDL_MainWindow _Window;
};
#elif defined(__unix__)
#endif

/********************************************************************************************************************************
													LDL_MainWindow - OpenGL 3
********************************************************************************************************************************/
#if defined(_WIN32) && defined(LDL_RENDER_OPENGL3)
typedef HGLRC(WINAPI* PFNWGLCREATECONTEXT)(HDC);
typedef BOOL(WINAPI* PFNWGLMAKECURRENT)(HDC, HGLRC);
typedef BOOL(WINAPI* PFNWGLDELETECONTEXT)(HGLRC);

typedef HGLRC(WINAPI* PFNWGLCREATECONTEXTATTRIBSARBPROC) (HDC hDC, HGLRC hShareContext, const int* attribList);

#define WGL_CONTEXT_MAJOR_VERSION_ARB             0x2091
#define WGL_CONTEXT_MINOR_VERSION_ARB             0x2092  
#define WGL_CONTEXT_FLAGS_ARB                     0x2094 
#define WGL_CONTEXT_PROFILE_MASK_ARB              0x9126  
#define WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB    0x00000002 
#define WGL_CONTEXT_CORE_PROFILE_BIT_ARB          0x00000001
#define WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB 0x00000002

class LDL_Window
{
public:
	LDL_Window(LDL_Result* result, const LDL_Vec2i& pos, const LDL_Vec2i& size, const char* title, int mode = LDL_WindowMode::Resized) :
		_Result(result),
		_HGLRC(NULL),
		_Window(result, pos, size, title, mode)
	{
		PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB = NULL;

		int attribs[] =
		{
			WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
			WGL_CONTEXT_MINOR_VERSION_ARB, 3,
			WGL_CONTEXT_FLAGS_ARB,         WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
			WGL_CONTEXT_PROFILE_MASK_ARB,  WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
			0
		};

		PIXELFORMATDESCRIPTOR pfd;

		ZeroMemory(&pfd, sizeof(PIXELFORMATDESCRIPTOR));

		_Window._HDC = GetDC(_Window._HWND);

		if (_Window._HDC == NULL)
		{
			_Result->Message("GetDC failed");
			return;
		}

		pfd.nSize = sizeof(pfd);
		pfd.nVersion = 1;
		pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
		pfd.iPixelType = PFD_TYPE_RGBA;
		pfd.cColorBits = 32;
		pfd.cDepthBits = 24;

		int format = ChoosePixelFormat(_Window._HDC, &pfd);

		if (format == 0)
		{
			_Result->Message("ChoosePixelFormat failed");
			return;
		}

		if (!SetPixelFormat(_Window._HDC, format, &pfd))
		{
			_Result->Message("SetPixelFormat failed");
			return;
		}

		_HGLRC = wglCreateContext(_Window._HDC);

		if (!_HGLRC)
		{
			_Result->Message("wglCreateContext failed");
			return;
		}

		if (!wglMakeCurrent(_Window._HDC, _HGLRC))
		{
			_Result->Message("wglMakeCurrent failed");
			return;
		}

		wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC)wglGetProcAddress("wglCreateContextAttribsARB");

		if (!wglCreateContextAttribsARB)
		{
			_Result->Message("wglGetProcAddress failed");
			return;
		}

		if (!wglMakeCurrent(NULL, NULL))
		{
			_Result->Message("wglMakeCurrent failed");
			return;
		}

		if (!wglDeleteContext(_HGLRC))
		{
			_Result->Message("wglDeleteContext failed");
			return;
		}

		_HGLRC = wglCreateContextAttribsARB(_Window._HDC, 0, attribs);

		if (!_HGLRC)
		{
			_Result->Message("wglCreateContextAttribsARB failed");
			return;
		}

		if (!wglMakeCurrent(_Window._HDC, _HGLRC))
		{
			_Result->Message("wglMakeCurrent failed");
			return;
		}
	}

	~LDL_Window()
	{
		wglMakeCurrent(NULL, NULL);
		wglDeleteContext(_HGLRC);
		ReleaseDC(_Window._HWND, _Window._HDC);
	}

	bool Running()
	{
		return _Window.Running();
	}

	void Present()
	{
		if (!SwapBuffers(_Window._HDC))
		{
			_Result->Message("SwapBuffers failed");
		}

		Update();
	}

	void PollEvents()
	{
		_Window.PollEvents();
	}

	const LDL_Vec2i& Size()
	{
		return _Window.Size();
	}

	const LDL_Vec2i& Pos()
	{
		return _Window.Pos();
	}

	bool GetEvent(LDL_Event& event)
	{
		return _Window.GetEvent(event);
	}

	bool WaitEvent(LDL_Event& event)
	{
		return _Window.WaitEvent(event);
	}

	void StopEvent()
	{
		_Window.StopEvent();
	}

	const char* Title()
	{
		return _Window.Title();
	}

	void Title(const char* title)
	{
		_Window.Title(title);
	}

	void* NativeHandle()
	{
		return _Window._HWND;
	}

	void Update()
	{
		_Window.Update();
	}
private:
	LDL_Result* _Result;
	HGLRC _HGLRC;
	LDL_MainWindow _Window;
};
#endif
/********************************************************************************************************************************
													LDL_MainWindow - Software
********************************************************************************************************************************/
#if defined(_WIN32) && defined(LDL_RENDER_SOFTWARE)
class LDL_Window
{
public:
	LDL_Window(LDL_Result* result, const LDL_Vec2i& pos, const LDL_Vec2i& size, const char* title, int mode = LDL_WindowMode::Resized) :
		_Result(result),
		_Window(result, pos, size, title, mode)
	{
	}

	~LDL_Window()
	{
		ReleaseDC(_Window._HWND, _Window._HDC);
	}

	bool Running()
	{
		return _Window.Running();
	}

	void Present()
	{
		Update();
	}

	void PollEvents()
	{
		_Window.PollEvents();
	}

	const LDL_Vec2i& Size()
	{
		return _Window.Size();
	}

	const LDL_Vec2i& Pos()
	{
		return _Window.Pos();
	}

	bool GetEvent(LDL_Event& event)
	{
		return _Window.GetEvent(event);
	}

	bool WaitEvent(LDL_Event& event)
	{
		return _Window.WaitEvent(event);
	}

	void StopEvent()
	{
		_Window.StopEvent();
	}

	const char* Title()
	{
		return _Window.Title();
	}

	void Title(const char* title)
	{
		_Window.Title(title);
	}

	void* NativeHandle()
	{
		return _Window._HWND;
	}

	void Update()
	{
		_Window.Update();
	}
private:
	LDL_Result* _Result;
	LDL_MainWindow _Window;
};
#elif defined(__unix__)
#endif

#endif
