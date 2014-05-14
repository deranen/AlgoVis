#pragma once

#define GLVis_main \
	SecondaryMain(); \
	int main(int argc, char** argv) { \
		GLVis::InitGLVis(); \
		SecondaryMain(); \
	} \
	int SecondaryMain

namespace GLVis {

bool InitGLVis();

}
