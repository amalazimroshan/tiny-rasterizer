#include <SDL2/SDL.h>

#include <chrono>
#include <iostream>
#include <rasterizer/color.hpp>
#include <rasterizer/renderer.hpp>
using namespace rasterizer;

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

  using clock = std::chrono::high_resolution_clock;
  auto last_frame_start = clock::now();
  float time = 0.f;

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
        case SDL_KEYDOWN:
          if (event.key.keysym.sym == SDLK_ESCAPE) running = false;
        default:
          break;
      }
    if (!running) break;
    if (!draw_surface) {
      draw_surface = SDL_CreateRGBSurfaceWithFormat(0, width, height, 32,
                                                    SDL_PIXELFORMAT_RGBA32);
      SDL_SetSurfaceBlendMode(draw_surface, SDL_BLENDMODE_NONE);
    }

    auto now = clock::now();
    float dt = std::chrono::duration_cast<std::chrono::duration<float>>(
                   now - last_frame_start)
                   .count();
    last_frame_start = now;
    std::cout << dt << std::endl;

    image_view color_buffer{
        .pixels = (color4ub*)draw_surface->pixels,
        .width = (std::uint32_t)width,
        .height = (std::uint32_t)height,
    };

    viewport viewport{.xmin = 0,
                      .ymin = 0,
                      .xmax = (std::int32_t)color_buffer.width,
                      .ymax = (std::int32_t)color_buffer.height};
    clear(color_buffer, {0.8f, 0.9f, 1.f, 1.f});

    vector3f positions[]{
        {-0.5f, -0.5f, 0.f},
        {-0.5f, 0.5f, 0.f},
        {0.5f, -0.5f, 0.f},
        {0.5f, 0.5f, 0.f},
    };

    vector4f colors[]{
        {1.f, 0.f, 0.f},
        {0.f, 1.f, 0.f},
        {0.f, 0.f, 1.f},
        {1.f, 1.f, 1.f},
    };

    std::uint32_t indices[]{
        0, 1, 2,  //
        2, 1, 3,  //
    };

    time += dt;
    matrix4x4f transform = matrix4x4f::rotateZX(time);

    draw(color_buffer, viewport,
         draw_command{
             .mesh =
                 {
                     .positions = {positions},
                     .colors = {colors},
                     .indices = indices,
                     .count = 6,
                 },
             .transform = transform,
         });

    SDL_Rect rect{.x = 0, .y = 0, .w = width, .h = height};
    SDL_BlitSurface(draw_surface, &rect, SDL_GetWindowSurface(window), &rect);
    SDL_UpdateWindowSurface(window);
  }
}