#include "SnakeGame.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>

using namespace std;
struct SDLState
{
	SDL_Window* window;
	SDL_Renderer* render;
};
void cleanup(SDLState& state);



int main(int argc, char *argv[])
{
	SDLState state;
	if (!SDL_Init(SDL_INIT_VIDEO))
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "ERROR", "ERROR INITIALIZING SDL3",nullptr);
		return 1;
	}
	int width = 800;
	int height = 400;
	state.window = SDL_CreateWindow("Game Window", width, height, 0);

	if (!state.window)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "ERROR", "Window not created", state.window);
		cleanup(state);
		return 1;
	}
	
	//rendering

	state.render = SDL_CreateRenderer(state.window, nullptr);
	if (!state.render)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "ERROR", "Error creating render", state.window);
		cleanup(state);
		return 1;
	}


	//Main loop
	bool running = true;
	while (running)
	{
		SDL_Event event{ 0 };
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_EVENT_QUIT) {
				running = false;
			}
		}

		SDL_SetRenderDrawColor(state.render, 255, 2, 255,255);
		SDL_RenderClear(state.render);

		SDL_RenderPresent(state.render);
	}


	cleanup(state);
	
	return 0;
}
void cleanup(SDLState &state) 
{
	SDL_DestroyRenderer(state.render);
	SDL_DestroyWindow(state.window);
	SDL_Quit();
}
