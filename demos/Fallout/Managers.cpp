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

#include "Managers.hpp"
#include <assert.h>
#include <string.h>

SpriteManager::SpriteManager(SpriteLoader* spriteLoader) :
	_SpriteLoader(spriteLoader),
	_Table(HashTable::Large)
{
}

Sprite* SpriteManager::GetSprite(const char* name)
{
	Sprite* result = (Sprite*)_Table.Contains(name);

	if (result == NULL)
	{
		result = _SpriteLoader->GetSprite(name);
		_Table.Add((HashItem*)result, name);
	}

	return result;
}

PathManager::PathManager(const char* path)
{
	assert(strlen(path) < PathManager::ShortMax);

	memset(_ShortPath, 0, sizeof(_ShortPath));
	memset(_FullPath, 0, sizeof(_FullPath));

	strcpy(_ShortPath, path);
}

const char* PathManager::Path(const char* dir, const char* file)
{
	assert(strlen(_ShortPath) + strlen(dir) + strlen(file) < PathManager::FullMax);

	memset(_FullPath, 0, sizeof(_FullPath));

	strcpy(_FullPath, _ShortPath);
	strcat(_FullPath, dir);
	strcat(_FullPath, file);

	return _FullPath;
}
