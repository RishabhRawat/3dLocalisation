#ifndef GLUTIL_H
#define GLUTIL_H
#include "Common.h"
void utilCheckGLError(const char* id);
void utilCheckFBOError(GLenum target, const char* id);

#endif // GLUTIL_H
