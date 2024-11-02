#include <SDL2/SDL.h>

int main() {
  SDL_Init(SDL_INIT_VIDEO);

  int width = 800;
  int height = 600;

  SDL_Window* window = SDL_CreateWindow(
      "tiny rasterizer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
      width, height, SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN);

  int mouse_x = 0;
  int mouse_y = 0;

  bool running = true;
  while (running) {
    for (SDL_Event event; SDL_PollEvent(&event);) switch (event.type) {
        case SDL_WINDOWEVENT:
          switch (event.window.event) {
            case SDL_WINDOWEVENT_RESIZED:
              width = event.window.data1;
              height = event.window.data2;
              break;

            default:
              break;
          }
          break;
        case SDL_QUIT:
          running = false;
          break;
        case SDL_MOUSEMOTION:
          mouse_x = event.motion.x;
          mouse_y = event.motion.y;
          break;
        default:
          break;
      }
    if (!running) break;
  }
}