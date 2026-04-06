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
	//SDL3 ERROR HANDLE
	if (!SDL_Init(SDL_INIT_VIDEO))
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "ERROR", "ERROR INITIALIZING SDL3",nullptr);
		return 1;
	}
	int width = 800;
	int height = 600;
	state.window = SDL_CreateWindow("Game Window", width, height, SDL_WINDOW_RESIZABLE);

	//Window ERROR HANDLE
	if (!state.window)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "ERROR", "Window not created", state.window);
		cleanup(state);
		return 1;
	}
	
	//Rendering ERROR HANDLE

	state.render = SDL_CreateRenderer(state.window, nullptr);
	if (!state.render)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "ERROR", "Error creating render", state.window);
		cleanup(state);
		return 1;
	}
	int logW =640;
	int logH=320;
	SDL_SetRenderLogicalPresentation(state.render,logW,logH,SDL_LOGICAL_PRESENTATION_LETTERBOX);

	//load game assets
	SDL_Texture* idleTex = IMG_LoadTexture(state.render, "data/SNAKE.png");
	SDL_SetTextureScaleMode(idleTex, SDL_SCALEMODE_NEAREST);


	//Main loop
	bool running = true;
	while (running)
	{
		SDL_Event event{ 0 };
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_EVENT_QUIT:
				running = false;
				break;
			
			default:
				break;
			}
		
			
		}

		SDL_SetRenderDrawColor(state.render, 255, 255, 255,255);
		SDL_RenderClear(state.render);

		SDL_FRect Snake{
			.x = 0,
			.y = 0,
			.w = 32,
			.h = 32
		};
		SDL_FRect dst{
			.x = 0,
			.y = 0,
			.w = 32,
			.h = 32
		};

		SDL_RenderTexture(state.render, idleTex, &Snake, &dst);

		SDL_RenderPresent(state.render);
	}


	SDL_DestroyTexture(idleTex);
	cleanup(state);
	
	return 0;
}
void cleanup(SDLState &state) 
{
	SDL_DestroyRenderer(state.render);
	SDL_DestroyWindow(state.window);
	SDL_Quit();
}
