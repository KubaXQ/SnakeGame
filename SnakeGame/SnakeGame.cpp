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
	int snakeX = 5;
	int snakeY = 5;
	uint64_t prevTime = SDL_GetTicks();
	int angle = 0;
	float dirX = 0;
	float dirY = 0;
	float moveTimer = 0.0f;
	float moveDelay = 0.15f;
	const int TILE_SIZE = 32;
	//Main loop
	bool running = true;
	while (running)
	{

		uint64_t nowTime = SDL_GetTicks();
		float deltaTime = (nowTime - prevTime) / 1000.f; //converting to seconds

		moveTimer += deltaTime;

		if (moveTimer >= moveDelay) {
			moveTimer = 0;

			snakeX += dirX;
			snakeY += dirY;
		}

		SDL_FRect Snake{
			.x = 0,
			.y = 0,
			.w = 32,
			.h = 32
		};

		SDL_FRect dst{
		snakeX* TILE_SIZE,
		snakeY* TILE_SIZE,
		TILE_SIZE,
		TILE_SIZE
		};
		SDL_FRect snakeTail = { 100.0f, 100.0f, 32.0f, 32.0f };

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
			
			dirX = 1;
			dirY = 0;
			angle = 90;
			
		}
		else if (keys[SDL_SCANCODE_A] || keys[SDL_SCANCODE_LEFT]) {
			dirX = -1;
			dirY = 0;
			angle = 270;
			
		}
		else if (keys[SDL_SCANCODE_W] || keys[SDL_SCANCODE_UP]) {
			
			dirX = 0;
			dirY = -1;
			angle = 0;
		}
		else if (keys[SDL_SCANCODE_S] || keys[SDL_SCANCODE_DOWN]) {
			
			dirX = 0;
			dirY = 1;
			angle = 180;
		}

		SDL_SetRenderDrawColor(state.render, 79, 168, 51, 255);
		SDL_RenderClear(state.render);

		

		//rysownie ogona
		//SDL_SetRenderDrawColor(state.render, 102, 102, 102, 255);
		//SDL_RenderFillRect(state.render, &snakeTail);
		SDL_RenderTextureRotated(state.render, idleTex, &Snake, &dst, angle, nullptr, SDL_FLIP_NONE);
		
		
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
