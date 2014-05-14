#pragma once

#include "OpenGL/gl3.h"

#define BUFFER_OFFSET(x) ((const void*) (x))

typedef struct {
	GLenum       type;
	const char*  filename;
	GLuint       shader;
} ShaderInfo;

GLuint LoadShaders( ShaderInfo* );
