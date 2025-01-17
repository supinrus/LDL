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

#include <LDL/Conv.hpp>
#include "Conv.hpp"
#include <string.h>

LDL_NumberToStringImpl::LDL_NumberToStringImpl() :
	_Result(0)
{
	memset(&_Buffer, 0, sizeof(_Buffer));
}

const char* LDL_NumberToStringImpl::Convert(int num, uint8_t base)
{
	int i = 0;
	bool isNegative = false;

	if (num == 0)
	{
		_Buffer[i++] = '0';
		_Buffer[i] = '\0';
	}

	if (num < 0 && base == 10)
	{
		isNegative = true;
		num = -num;
	}

	while (num != 0)
	{
		int rem = num % base;
		_Buffer[i++] = (rem > 9) ? (rem - 10) + 'a' : rem + '0';
		num = num / base;
	}

	if (isNegative)
		_Buffer[i++] = '-';

	_Buffer[i] = '\0';

	Reverse(_Buffer, i);

	return _Buffer;
}

const char* LDL_NumberToStringImpl::Convert(size_t num)
{
	return Convert((int)num, 10);
}


void LDL_NumberToStringImpl::Swap(char& t1, char& t2)
{
	char tmp = t1;
	t1 = t2;
	t2 = tmp;
}

void LDL_NumberToStringImpl::Reverse(char* str, size_t length)
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

LDL_NumberToString::LDL_NumberToString() :
	_Impl(new(&_ImplData[0]) LDL_NumberToStringImpl)
{
}

LDL_NumberToString::~LDL_NumberToString()
{
}

const char* LDL_NumberToString::Convert(int num, uint8_t base)
{
	return _Impl->Convert(num, base);
}

const char* LDL_NumberToString::Convert(size_t num)
{
	return _Impl->Convert((int)num, 10);
}
