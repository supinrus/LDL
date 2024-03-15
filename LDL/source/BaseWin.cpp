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

#include <LDL/BaseWin.hpp>
#include <string.h>

LDL_BaseWindow::LDL_BaseWindow(const LDL_Vec2i& pos, const LDL_Vec2i& size, const char* title, int mode) :
	_Pos(pos),
	_Size(size),
	_WindowMode(mode)
{
	Title(title);
}

LDL_BaseWindow::~LDL_BaseWindow()
{
}

const char* LDL_BaseWindow::Title()
{
	return _Title;
}

void LDL_BaseWindow::Title(const char* title)
{
	memset(_Title, 0, Max);
	strcpy(_Title, title);
}

const LDL_Vec2i& LDL_BaseWindow::Pos()
{
	return _Pos;
}

void LDL_BaseWindow::Pos(const LDL_Vec2i& pos)
{
	_Pos = pos;
}

const LDL_Vec2i& LDL_BaseWindow::Size()
{
	return _Size;
}

void LDL_BaseWindow::Size(const LDL_Vec2i& size)
{
	_Size = size;
}

int LDL_BaseWindow::Mode()
{
	return _WindowMode;
}