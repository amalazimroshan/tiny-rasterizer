#include <SDL2/SDL.h>

int main() {
  SDL_Init(SDL_INIT_VIDEO);

  int width = 800;
  int height = 600;

  SDL_Window* window = SDL_CreateWindow(
      "tiny rasterizer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
      width, height, SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN);
  SDL_Surface* draw_surface = nullptr;
  int mouse_x = 0;
  int mouse_y = 0;

  bool running = true;
  while (running) {
    for (SDL_Event event; SDL_PollEvent(&event);) switch (event.type) {
        case SDL_WINDOWEVENT:
          switch (event.window.event) {
            case SDL_WINDOWEVENT_RESIZED:
              if (draw_surface) SDL_FreeSurface(draw_surface);
              draw_surface = nullptr;
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
    if (!draw_surface) {
      draw_surface = SDL_CreateRGBSurfaceWithFormat(0, width, height, 32,
                                                    SDL_PIXELFORMAT_RGBA32);
      SDL_SetSurfaceBlendMode(draw_surface, SDL_BLENDMODE_NONE);
    }

    SDL_Rect rect{.x = 0, .y = 0, .w = width, .h = height};
    SDL_BlitSurface(draw_surface, &rect, SDL_GetWindowSurface(window), &rect);
    uint32_t color = 0xffffdfdf;
    // for (int i = 0; i < width * height; ++i)
    //   ((uint32_t*)(draw_surface->pixels))[i] = color;
    std::fill_n((uint32_t*)draw_surface->pixels, width * height, color);
    SDL_UpdateWindowSurface(window);
  }
}