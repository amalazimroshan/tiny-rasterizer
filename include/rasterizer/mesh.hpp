#pragma once
#include <rasterizer/attribute.hpp>
#include <rasterizer/types.hpp>

namespace rasterizer {
struct mesh {
  attribute<vector3f> positions = {};
  attribute<vector4f> colors = {};
  std::uint32_t vertex_count = 0;
};
}  // namespace rasterizer