#pragma once

#include "Graphics/Shader.h"
#include "Graphics/Program.h"
#include "Graphics/Texture.h"
#include "Graphics/Buffer.h"
#include "Graphics/VertexArray.h"
#include "Graphics/Framebuffer.h"

enum ColorMask
{
	None = 0x0,
	Red = 0x1,
	Green = 0x2,
	Blue = 0x4,
	Alpha = 0x8,
	All = 0xF
};

struct BlendState
{
	bool enabled{ false };
	GLenum srcColorBlend{ GL_ONE };
	GLenum dstColorBlend{ GL_ZERO };
	GLenum srcAlphaBlend{ GL_ONE };
	GLenum dstAlphaBlend{ GL_ZERO };
	GLenum colorBlendEquation{ GL_FUNC_ADD };
	GLenum alphaBlendEquation{ GL_FUNC_ADD };
	uint32_t colorMask{ ColorMask::All };
	float blendColor[4]{ .0f, .0f, .0f, 1.0f };
};

struct RasterizationState
{
	bool depthClampEnable{ false };
	bool rasterizerDiscardEnable{ false };
	GLenum cullMode{ GL_CCW };
	GLenum frontFace{ GL_BACK };
	GLenum polygonMode{ GL_FILL };
	bool polygonOffsetLineEnable{ false };
	bool polygonOffsetPointEnable{ false };
	bool polygonOffsetFillEnable{ false };
	float polygonOffsetFactor{ 0.0f };
	float polygonOffsetUnits{ 0.0f };
	float lineWidth{ 1.0f };
};

struct StencilState
{
	GLenum onFail{ GL_KEEP };
	GLenum onPass{ GL_KEEP };
	GLenum onDepthFail{ GL_KEEP };
	GLenum compareFunction{ GL_NEVER };
	uint32_t compareMask{ 0 };
	uint32_t writeMask{ 0 };
	uint32_t reference{ 0 };
};

struct DepthStencilState
{
	bool depthTestEnable{ false };
	bool depthWriteEnable{ true };
	GLenum depthCompareFunction{ GL_LESS };
	bool depthBoundsTestEnable{ false };
	bool stencilTestEnable{ false };
	StencilState backStencil;
	StencilState frontStencil;
	float minDepthBounds{ 0.0f };
	float maxDepthBounds{ 1.0f };
};

class Graphics
{
public:

	Graphics() = default;
	~Graphics()
	{
		destroy();
	}

	void create();
	void destroy();

	void setClearColor(float r, float g, float b, float a = 1.0f);
	void setDepth(float depth);
	void setStencil(int32_t stencil);
	void setViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height);
	void clear(uint32_t flags);

	void setBlendState(const BlendState& state);
	void setRasterizationState(const RasterizationState& state);
	void setDepthStencilState(const DepthStencilState& state);

private:

	void initDebug();
	void setStencilState(GLenum face, const StencilState& state,
		StencilState& currStencilState);

private:

	BlendState mCurrBlendState;
	RasterizationState mCurrRasterizationState;
	DepthStencilState mCurrDepthStencilState;
};