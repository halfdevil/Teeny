#pragma once

#include "Math/GpuVec4.h"

using glm::mat4;

struct PACKED_STRUCT GpuMat4
{
  float data[16];

  GpuMat4() = default;

  explicit GpuMat4(const mat4& m)
  {
    memcpy(data, glm::value_ptr(m), 16 * sizeof(float));
  }
};