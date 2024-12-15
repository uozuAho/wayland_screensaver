#include <SDL2/SDL.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

const int SCREEN_WIDTH = 3840;
const int SCREEN_HEIGHT = 2160;

int main(int argc, char *argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow(
        "Screensaver",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        SDL_WINDOW_FULLSCREEN | SDL_WINDOW_SHOWN | SDL_WINDOW_INPUT_FOCUS | SDL_WINDOW_MOUSE_FOCUS | SDL_WINDOW_MOUSE_GRABBED
    );
    if (!window) {
        SDL_Log("Failed to create window: %s", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        SDL_Log("Failed to create renderer: %s", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    SDL_ShowCursor(SDL_DISABLE);
    SDL_SetWindowAlwaysOnTop(window, SDL_TRUE);
    SDL_WarpMouseInWindow(window, SCREEN_WIDTH, SCREEN_HEIGHT);

    int running = 1; //todo remove this?
    SDL_Event event;
    int last_mouse_x = -1, last_mouse_y = -1;
int count=0;
	SDL_Delay(500);

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_KEYDOWN
                || event.type == SDL_MOUSEBUTTONDOWN
                || event.type == SDL_QUIT)
            {
		SDL_Log("key mbtn quit");
                running = 0;
                break;
            }
            if (event.type == SDL_MOUSEMOTION) {
                int x = event.motion.x;
                int y = event.motion.y;
		SDL_Log("motion");
		SDL_Log("%d", last_mouse_x);
		SDL_Log("%d", last_mouse_y);
		SDL_Log("%d", x);
		SDL_Log("%d", y);
		// count is needed since the lounge keyboard sends mouse movement
		// after keypresses (?), making this hard to test
                if (last_mouse_x != -1 && last_mouse_y != -1 && count++ > 10 &&
                    (x != last_mouse_x || y != last_mouse_y)) {
                    running = 0;
                    break;
                }

                last_mouse_x = x;
                last_mouse_y = y;
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
        SDL_ShowCursor(SDL_DISABLE); // just in case the first time doesn't get it
        SDL_Delay(100);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
