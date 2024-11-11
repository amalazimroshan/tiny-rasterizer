#pragma once
#include <cmath>
#include <rasterizer/vector.hpp>
namespace rasterizer {
struct matrix4x4f {
  float values[16];
  static matrix4x4f identity() {
    return matrix4x4f{
        1.f, 0.f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f,
        0.f, 0.f, 1.f, 0.f, 0.f, 0.f, 0.f, 1.f,
    };
  }

  static matrix4x4f rotateXY(float angle) {
    float cos = std::cos(angle);
    float sin = std::sin(angle);

    return matrix4x4f{
        cos, -sin, 0.f, 0.f,  //
        sin, cos,  0.f, 0.f,  //
        0.f, 0.f,  1.f, 0.f,  //
        0.f, 0.f,  0.f, 1.f,  //
    };
  }
  static matrix4x4f rotateZX(float angle) {
    float cos = std::cos(angle);
    float sin = std::sin(angle);

    return matrix4x4f{
        cos,  0.f, sin, 0.f,  //
        0.f,  1.f, 0.f, 0.f,  //
        -sin, 0.f, cos, 0.f,  //
        0.f,  0.f, 0.f, 1.f,  //
    };
  }
};
inline vector4f operator*(matrix4x4f const& m, vector4f const& v) {
  vector4f result{0.f, 0.f, 0.f, 0.f};
  result.x = m.values[0] * v.x + m.values[1] * v.y + m.values[2] * v.z +
             m.values[3] * v.w;
  result.y = m.values[4] * v.x + m.values[5] * v.y + m.values[6] * v.z +
             m.values[7] * v.w;
  result.z = m.values[8] * v.x + m.values[9] * v.y + m.values[10] * v.z +
             m.values[11] * v.w;
  result.w = m.values[12] * v.x + m.values[13] * v.y + m.values[14] * v.z +
             m.values[15] * v.w;
  return result;
}

}  // namespace rasterizer