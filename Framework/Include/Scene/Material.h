#pragma once

#include <string>
#include <vector>
#include "Math/GpuMat4.h"

constexpr const uint64_t kInvalidTexture = 0xFFFFFFFF;

enum MaterialFlags
{
  CastShadows = 0x1,
  ReceiveShadows = 0x2,
  Transparent = 0x4
};

struct PACKED_STRUCT Material final
{
  GpuVec4 emmisiveColor{ 0.0f, 0.0f, 0.0f, 1.0f };
  GpuVec4 albedoColor{ 1.0f, 1.0f, 1.0f, 1.0f };
  GpuVec4 roughness{ 1.0f, 1.0f, 0.0f, 0.0f };

  float transparencyFactor{ 1.0f };
  float alphaTest{ 0.0f };
  float mettalicFactor{ 0.0f };
  uint32_t flags{ MaterialFlags::CastShadows | MaterialFlags::ReceiveShadows };

  uint64_t ambientOcclusionMap{ kInvalidTexture };
  uint64_t emissiveMap{ kInvalidTexture };
  uint64_t albedoMap{ kInvalidTexture };
  uint64_t metallicRoughnessMap{ kInvalidTexture };
  uint64_t normalMap{ kInvalidTexture };
  uint64_t opacityMap{ kInvalidTexture };
};