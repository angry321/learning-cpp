#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_scancode.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>
#include <iostream>

struct Player {
	float x, y;
	float speed;
	int size;

	Player() : x(400), y(300), speed(3.0f), size(32) {}

	void move(float dx, float dy) {
		x += dx * speed;
		y += dy * speed;
	}

	void draw(SDL_Renderer* renderer) {
		SDL_Rect rect = {(int)x, (int)y, size, size};
		SDL_SetRenderDrawColor(renderer, 255, 200, 0, 255);
		SDL_RenderFillRect(renderer, &rect);
	}
};

int main() {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cout << "Ошибка SDL: " << SDL_GetError() << "\n";
		return 1;
	}

	SDL_Window* window = SDL_CreateWindow(
		"Ферма",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		800, 600,
		SDL_WINDOW_SHOWN
	);

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	Player player;
	bool running = true;
	SDL_Event event;

	while (running) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) running = false;
		}

		int dx = 0, dy = 0;
		
		const Uint8* keys = SDL_GetKeyboardState(NULL);
		if (keys[SDL_SCANCODE_W]) dy -= 1;
		if (keys[SDL_SCANCODE_S]) dy += 1;
		if (keys[SDL_SCANCODE_A]) dx -= 1;
		if (keys[SDL_SCANCODE_D]) dx += 1;

		if (dx != 0 && dy != 0) {
			player.speed = 2.1f;
		} else {
			player.speed = 3.0f;
		}

		player.move(dx, dy);

		SDL_SetRenderDrawColor(renderer, 34, 139, 34, 255);
		SDL_RenderClear(renderer);

		player.draw(renderer);

		SDL_RenderPresent(renderer);
		SDL_Delay(16);


		for (int y = 0; y < 5; y++) {
			for (int x = 0; x < 5; x++) {
				SDL_Rect cell = {x * 64, y * 64, 64, 64};
				SDL_SetRenderDrawColor(renderer, 139, 90, 43, 255);
				SDL_RenderDrawRect(renderer, &cell);
			}
		}
	}
	
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
