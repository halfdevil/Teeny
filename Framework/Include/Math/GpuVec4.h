#pragma once

#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <string.h>

using glm::vec4;

#ifdef __GNUC__
#define PACKED_STRUCT __attribute__((packed, aligned(1)))
#else
#define PACKED_STRUCT
#endif

struct PACKED_STRUCT GpuVec4
{
	float x;
	float y;
	float z;
	float w;

	GpuVec4() = default;

	explicit GpuVec4(float f)
		: x(f), y(f), z(f), w(f)
	{
	}

	GpuVec4(float a, float b, float c, float d)
		: x(a), y(b), z(c), w(d)
	{
	}

	explicit GpuVec4(const vec4& v)
		: x(v.x), y(v.y), z(v.z), w(v.w)
	{
	}
};
