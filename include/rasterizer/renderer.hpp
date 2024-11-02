#pragma once

#include <rasterizer/image_view.hpp>
#include <rasterizer/types.hpp>

namespace rasterizer {
void clear(image_view const& color_buffer, vector4f const& color);
}