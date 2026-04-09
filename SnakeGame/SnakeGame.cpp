#include "SnakeGame.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>

using namespace std;
struct SDLState
{
	SDL_Window* window;
	SDL_Renderer* render;
	int width, height, logW, logH;
};
bool initialization(SDLState& state);
void cleanup(SDLState& state);



int main(int argc, char *argv[])
{
	
	SDLState state;

	state.width = 1600;
	state.height = 800;
	state.logW = 640;
	state.logH = 320;

	if (!initialization(state)) {
		return 1;
	}

	//load game assets
	SDL_Texture* idleTex = IMG_LoadTexture(state.render, "data/SNAKE.png");
	SDL_SetTextureScaleMode(idleTex, SDL_SCALEMODE_NEAREST);

	//setup game data

	const bool* keys = SDL_GetKeyboardState(nullptr);
	float snakeX = 0;
	float snakeY = 0;
	uint64_t prevTime = SDL_GetTicks();
	
	//Main loop
	bool running = true;
	while (running)
	{
		uint64_t nowTime = SDL_GetTicks();
		float deltaTime = (nowTime - prevTime) / 1000.f; //converting to seconds

		SDL_Event event{ 0 };
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_EVENT_QUIT:
				running = false;
				break;
			case SDL_EVENT_WINDOW_RESIZED:
				state.width = event.window.data1;
				state.height = event.window.data2;
				break;
			default:
				break;
			}
		
			
		}
		//handle movement
		if (keys[SDL_SCANCODE_D] || keys[SDL_SCANCODE_RIGHT]) {
			snakeX += 100.f * deltaTime;
		}
		else if (keys[SDL_SCANCODE_A] || keys[SDL_SCANCODE_LEFT]) {
			snakeX += -100.f * deltaTime;
		}
		else if (keys[SDL_SCANCODE_W] || keys[SDL_SCANCODE_UP]) {
			snakeY += -100.f * deltaTime;
		}
		else if (keys[SDL_SCANCODE_S] || keys[SDL_SCANCODE_DOWN]) {
			snakeY += 100.f * deltaTime;
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
			.x = snakeX,
			.y = snakeY,
			.w = 32,
			.h = 32
		};

		SDL_RenderTexture(state.render, idleTex, &Snake, &dst);

		SDL_RenderPresent(state.render);
		prevTime = nowTime;
	}


	SDL_DestroyTexture(idleTex);
	cleanup(state);
	
	return 0;
}

bool initialization(SDLState &state) {
	bool initSucces = true;
	if (!SDL_Init(SDL_INIT_VIDEO))
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "ERROR", "ERROR INITIALIZING SDL3", nullptr);
		initSucces = false;
	}
	state.window = SDL_CreateWindow("Game Window", state.width, state.height, SDL_WINDOW_RESIZABLE);

	//Window ERROR HANDLE
	if (!state.window)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "ERROR", "Window not created", state.window);
		cleanup(state);
		initSucces = false;
	}

	//Rendering ERROR HANDLE

	state.render = SDL_CreateRenderer(state.window, nullptr);
	if (!state.render)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "ERROR", "Error creating render", state.window);
		cleanup(state);
		initSucces = false;
	}
	//configure Presentation
	SDL_SetRenderLogicalPresentation(state.render, state.logW, state.logH, SDL_LOGICAL_PRESENTATION_LETTERBOX);
	return initSucces;
}
void cleanup(SDLState &state) 
{
	SDL_DestroyRenderer(state.render);
	SDL_DestroyWindow(state.window);
	SDL_Quit();
}
