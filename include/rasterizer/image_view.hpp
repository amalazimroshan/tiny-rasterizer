#pragma once
#include <cstdint>
#include <rasterizer/types.hpp>

namespace rasterizer {
struct image_view {
  color4ub* pixels = nullptr;
  std::uint32_t width = 0;
  std::uint32_t height = 0;
};
}  // namespace rasterizer