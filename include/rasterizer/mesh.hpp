#pragma once
#include <rasterizer/attribute.hpp>
#include <rasterizer/vector.hpp>

namespace rasterizer {
struct mesh {
  attribute<vector3f> positions = {};
  attribute<vector4f> colors = {};
  std::uint32_t const* indices = nullptr;
  std::uint32_t count = 0;
};
}  // namespace rasterizer