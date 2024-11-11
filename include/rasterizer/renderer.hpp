#pragma once

#include <rasterizer/draw_command.hpp>
#include <rasterizer/image_view.hpp>
#include <rasterizer/vector.hpp>
#include <rasterizer/viewport.hpp>

namespace rasterizer {
void clear(image_view const& color_buffer, vector4f const& color);
void draw(image_view const& color_buffer, viewport const& viewport,
          draw_command const& command);
}  // namespace rasterizer