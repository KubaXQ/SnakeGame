#include "SnakeGame.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
using namespace std;

void cleanup(SDL_Window* window);

int main(int argc, char *argv[])
{
	
	if (!SDL_Init(SDL_INIT_VIDEO))
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "ERROR", "ERROR INITIALIZING SDL3",nullptr);
		return 1;
	}
	int width = 800;
	int height = 400;
	SDL_Window* window = SDL_CreateWindow("Game Window", width, height, 0);

	if (!window)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "ERROR", "Window not created", window);
		cleanup(window);
		return 1;
	}

	cleanup(window);
	
	return 0;
}
void cleanup(SDL_Window* window) {
	SDL_DestroyWindow(window);
	SDL_Quit();
}
