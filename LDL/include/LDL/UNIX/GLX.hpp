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

#ifndef LDL_UNIX_GLX_hpp
#define LDL_UNIX_GLX_hpp

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/keysym.h>

extern "C" {
	
#define GLX_USE_GL		      1
#define GLX_BUFFER_SIZE		  2
#define GLX_LEVEL		      3
#define GLX_RGBA		      4
#define GLX_DOUBLEBUFFER	  5
#define GLX_STEREO		      6
#define GLX_AUX_BUFFERS		  7
#define GLX_RED_SIZE		  8
#define GLX_GREEN_SIZE		  9
#define GLX_BLUE_SIZE		  10
#define GLX_ALPHA_SIZE		  11
#define GLX_DEPTH_SIZE		  12
#define GLX_STENCIL_SIZE	  13
#define GLX_ACCUM_RED_SIZE	  14
#define GLX_ACCUM_GREEN_SIZE  15
#define GLX_ACCUM_BLUE_SIZE	  16
#define GLX_ACCUM_ALPHA_SIZE  17

typedef XID GLXDrawable;
typedef struct __GLXcontextRec* GLXContext;
typedef unsigned char	GLubyte;

#define GLX_SAMPLE_BUFFERS              0x186a0 /*100000*/
#define GLX_SAMPLES                     0x186a1 /*100001*/

extern Bool glXQueryVersion(Display* dpy, int* maj, int* min);
extern XVisualInfo* glXChooseVisual(Display* dpy, int screen, int* attribList);
extern GLXContext glXCreateContext(Display* dpy, XVisualInfo* vis, GLXContext shareList, Bool direct);
extern void glXDestroyContext(Display* dpy, GLXContext ctx);
extern Bool glXMakeCurrent(Display* dpy, GLXDrawable drawable, GLXContext ctx);
extern void glXSwapBuffers(Display* dpy, GLXDrawable drawable);
extern void (*glXGetProcAddress(const GLubyte* procname))(void);

}

#endif