// main.cpp : Defines the entry point for the application.
//

#include "main.hpp"
#include <SDL.h>

#if defined(_WIN32)
int wmain(int argc, char* argv[])
{
	main(argc, argv);
}
#endif

int main(int argc, char* argv[])
{
	SDL_Log("Hello CMake.");

	return 0;
}
