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

#ifndef LDL_Events_hpp
#define LDL_Events_hpp

#include <LDL/Enums.hpp>

class LDL_EventQuit
{
public:
	uint8_t Type;
};

class LDL_EventMouse
{
public:
	uint8_t Type;
	size_t  PosX;
	size_t  PosY;
	uint8_t State;
	uint8_t Button;
	size_t  Scroll;
	size_t  Delta;
};

class LDL_EventResize
{
public:
	uint8_t Type;
	size_t Width;
	size_t Height;
};

class LDL_EventKeyboard
{
public:
	uint8_t Type;
	uint8_t State;
	uint8_t Key;
};

class LDL_EventGainedFocus
{
public:
	uint8_t Type;
};

class LDL_EventLostFocus
{
public:
	uint8_t Type;
};

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
		uint8_t Type;
		LDL_EventQuit        Quit;
		LDL_EventMouse       Mouse;
		LDL_EventResize      Resize;
		LDL_EventKeyboard    Keyboard;
		LDL_EventGainedFocus GainedFocus;
		LDL_EventLostFocus   LostFocus;
	};

	bool IsKeyPressed(uint8_t key)
	{
		return (Type == IsKeyboard && Keyboard.Key == key && Keyboard.State == LDL_ButtonState::Pressed);
	}

	bool IsKeyReleased(uint8_t key)
	{
		return (Type == IsKeyboard && Keyboard.Key == key && Keyboard.State == LDL_ButtonState::Released);
	}

	bool IsMousePressed(uint8_t key)
	{
		return (Type == IsMouseClick && Mouse.Button == key && Mouse.State == LDL_ButtonState::Pressed);
	}

	bool IsMouseReleased(uint8_t key)
	{
		return (Type == IsMouseClick && Mouse.Button == key && Mouse.State == LDL_ButtonState::Released);
	}
private:
};

class LDL_EventQueue
{
public:
	enum
	{
		Max = 256
	};

	LDL_EventQueue();
	bool IsEmpty();
	bool IsFull();
	size_t NextPosition(size_t position);
	bool Dequeue(LDL_Event& element);
	void Enqueue(const LDL_Event& element);
private:
	LDL_Event _Content[Max];
	size_t _Head;
	size_t _Tail;
	size_t _Length;
	size_t _Capacity;
};

class LDL_Eventer
{
public:
	LDL_Eventer();
	void Push(LDL_Event& event);
	bool Pop(LDL_Event& event);
	bool Running();
	void Stop();
	bool Empty();
private:
	bool _Running;
	LDL_EventQueue _Queue;
};

#endif