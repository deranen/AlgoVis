#include <OpenGL/gl3.h>
#include <OpenGL/gl3ext.h>

#include <SDL.h>

#include <iostream>
#include <cstdlib>

#include "GLVis.h"
#include "GLUtils.h"

void init();

enum VAO_IDs { Triangles, NumVAOs };
enum VBO_IDs { ArrayBuffer, NumVBOs };
enum Attrib_IDs { vPosition = 0 };

GLuint VAOs[NumVAOs];
GLuint VBOs[NumVBOs];

const GLuint NumVertices = 6;

int GLVis_main()
{
	for(float f = 0.0f; f <= 1.0f; f += 0.1)
	{
		std::cout << f << std::endl;
	}

	if( SDL_Init(SDL_INIT_VIDEO) )
	{
		std::cerr << "SDL_Init Error: "
				  << SDL_GetError() << std::endl;
		return 1;
	}

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	SDL_Window* window =
			SDL_CreateWindow( "Hello World!", 100, 100, 640, 480, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN );

	if( window == nullptr ) {
		std::cout << "SDL_CreateWindow Error: "
				  << SDL_GetError() << std::endl;
		return 1;
	}

	SDL_GLContext glContext = SDL_GL_CreateContext(window);
	if( glContext == nullptr ) {
		std::cout << "SDL_GL_CreateContext Error: "
				  << SDL_GetError() << std::endl;
		return 1;
	}

	init();

	bool bQuit = false;
	while( !bQuit )
	{
		SDL_Event e;
		while( SDL_PollEvent(&e) )
		{
			switch(e.type)
			{
			case SDL_QUIT: { bQuit = true; break; }
			}
		}

		glClearColor(1.0, 0.0, 0.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);

		glBindVertexArray(VAOs[Triangles]);
		glDrawArrays(GL_TRIANGLES, 0, NumVertices);

		SDL_GL_SwapWindow(window);
	}

	SDL_DestroyWindow(window);

	atexit( SDL_Quit );
    return 0;
}

void init()
{
	glGenVertexArrays(NumVAOs, VAOs);
	glBindVertexArray(VAOs[Triangles]);

	GLfloat vertices[NumVertices][2] = {
		{ -0.90, -0.90 },  // Triangle 1
		{  0.85, -0.90 },
		{ -0.90,  0.85 },
		{  0.90, -0.85 },  // Triangle 2
		{  0.90,  0.90 },
		{ -0.85,  0.90 }
	};

	glGenBuffers(NumVBOs, VBOs);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[ArrayBuffer]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	ShaderInfo shaders[] = {
		{ GL_VERTEX_SHADER, "triangles.vert" },
		{ GL_FRAGMENT_SHADER, "triangles.frag" },
		{ GL_NONE, nullptr }
	};

	GLuint program = LoadShaders(shaders);
	glUseProgram(program);

	glVertexAttribPointer(vPosition, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	glEnableVertexAttribArray(vPosition);
}
