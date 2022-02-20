#include "Graphics/Graphics.h"
#include "Core/Core.h"

void Graphics::create()
{
#if DEBUG_BUILD
	initDebug();
#endif
}

void Graphics::destroy()
{
}

void debugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length,
	GLchar const* message, void const* userParam)
{
	const auto srcString = [source]()
	{
		switch (source)
		{
		case GL_DEBUG_SOURCE_API: return "API";
		case GL_DEBUG_SOURCE_WINDOW_SYSTEM: return "WINDOW SYSTEM";
		case GL_DEBUG_SOURCE_SHADER_COMPILER: return "SHADER COMPILER";
		case GL_DEBUG_SOURCE_THIRD_PARTY: return "THIRD PARTY";
		case GL_DEBUG_SOURCE_APPLICATION: return "APPLICATION";
		case GL_DEBUG_SOURCE_OTHER: return "OTHER";
		}

		return "";
	};

	const auto typeString = [type]()
	{
		switch (type)
		{
		case GL_DEBUG_TYPE_ERROR: return "ERROR";
		case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: return "DEPRECATED_BEHAVIOR";
		case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR: return "UNDEFINED_BEHAVIOR";
		case GL_DEBUG_TYPE_PORTABILITY: return "PORTABILITY";
		case GL_DEBUG_TYPE_PERFORMANCE: return "PERFORMANCE";
		case GL_DEBUG_TYPE_MARKER: return "MARKER";
		case GL_DEBUG_TYPE_OTHER: return "OTHER";
		}

		return "";
	};

	const auto severityString = [severity]()
	{
		switch (severity)
		{
		case GL_DEBUG_SEVERITY_NOTIFICATION: return "NOTIFICATION";
		case GL_DEBUG_SEVERITY_LOW: return "LOW";
		case GL_DEBUG_SEVERITY_MEDIUM: return "MEDIUM";
		case GL_DEBUG_SEVERITY_HIGH: return "HIGH";
		}

		return "";
	};

	LOGDEBUG("[%s, %s, %s][%d] - %s", srcString, typeString, severityString, id, message);
}

void Graphics::setClearColor(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
}

void Graphics::setDepth(float depth)
{
	glClearDepth(depth);
}

void Graphics::setStencil(int32_t stencil)
{
	glClearStencil(stencil);
}

void Graphics::setViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
{
	glViewport(x, y, width, height);
}

void Graphics::clear(uint32_t flags)
{
	glClear(flags);
}

void Graphics::setBlendState(const BlendState& state)
{
	if (mCurrBlendState.enabled != state.enabled)
	{
		if (state.enabled)
		{
			glEnable(GL_BLEND);
		}
		else
		{
			glDisable(GL_BLEND);
		}
	}

	if (mCurrBlendState.colorMask != state.colorMask)
	{
		glColorMask(state.colorMask & ColorMask::Red,
			state.colorMask & ColorMask::Green,
			state.colorMask & ColorMask::Blue,
			state.colorMask & ColorMask::Alpha);

		mCurrBlendState.colorMask = state.colorMask;
	}

	if (state.enabled)
	{
		if (!mCurrBlendState.enabled)
		{
			glBlendColor(state.blendColor[0], state.blendColor[1],
				state.blendColor[2], state.blendColor[3]);

			glBlendEquationSeparate(state.colorBlendEquation, state.alphaBlendEquation);
			glBlendFuncSeparate(state.srcColorBlend, state.dstColorBlend,
				state.srcAlphaBlend, state.dstAlphaBlend);

			memcpy(mCurrBlendState.blendColor, state.blendColor,
				sizeof(float) * 4);

			mCurrBlendState.srcColorBlend = state.srcColorBlend;
			mCurrBlendState.dstColorBlend = state.dstColorBlend;
			mCurrBlendState.srcAlphaBlend = state.srcAlphaBlend;
			mCurrBlendState.dstAlphaBlend = state.dstAlphaBlend;
		}
		else
		{
			if (mCurrBlendState.blendColor[0] != state.blendColor[0] ||
				mCurrBlendState.blendColor[1] != state.blendColor[1] ||
				mCurrBlendState.blendColor[2] != state.blendColor[2] ||
				mCurrBlendState.blendColor[3] != state.blendColor[3])
			{
				glBlendColor(state.blendColor[0], state.blendColor[1],
					state.blendColor[2], state.blendColor[3]);

				memcpy(mCurrBlendState.blendColor, state.blendColor,
					sizeof(float) * 4);
			}

			if (mCurrBlendState.colorBlendEquation != state.colorBlendEquation ||
				mCurrBlendState.alphaBlendEquation != state.alphaBlendEquation)
			{
				glBlendEquationSeparate(state.colorBlendEquation, state.alphaBlendEquation);
			}

			if (mCurrBlendState.srcColorBlend != state.srcColorBlend ||
				mCurrBlendState.dstColorBlend != state.dstColorBlend ||
				mCurrBlendState.srcAlphaBlend != state.srcAlphaBlend ||
				mCurrBlendState.dstAlphaBlend != state.dstAlphaBlend)
			{
				glBlendFuncSeparate(state.srcColorBlend, state.dstColorBlend,
					state.srcAlphaBlend, state.dstAlphaBlend);

				mCurrBlendState.srcColorBlend = state.srcColorBlend;
				mCurrBlendState.dstColorBlend = state.dstColorBlend;
				mCurrBlendState.srcAlphaBlend = state.srcAlphaBlend;
				mCurrBlendState.dstAlphaBlend = state.dstAlphaBlend;
			}
		}
	}

	mCurrBlendState.enabled = state.enabled;
}

void Graphics::setRasterizationState(const RasterizationState& state)
{
	if (mCurrRasterizationState.rasterizerDiscardEnable != state.rasterizerDiscardEnable)
	{
		if (state.rasterizerDiscardEnable)
		{
			glEnable(GL_RASTERIZER_DISCARD);
		}
		else
		{
			glDisable(GL_RASTERIZER_DISCARD);
		}

		mCurrRasterizationState.rasterizerDiscardEnable = state.rasterizerDiscardEnable;
	}

	if (mCurrRasterizationState.depthClampEnable != state.depthClampEnable)
	{
		if (state.depthClampEnable)
		{
			glEnable(GL_DEPTH_CLAMP);
		}
		else
		{
			glDisable(GL_DEPTH_CLAMP);
		}

		mCurrRasterizationState.depthClampEnable = state.depthClampEnable;
	}

	if (mCurrRasterizationState.cullMode != state.cullMode)
	{
		if (state.cullMode != GL_NONE)
		{
			if (mCurrRasterizationState.cullMode == GL_NONE)
			{
				glEnable(GL_CULL_FACE);
			}

			glCullFace(mCurrRasterizationState.cullMode);
		}
	}

	if (state.cullMode != GL_NONE)
	{
		if (mCurrRasterizationState.cullMode == GL_NONE ||
			mCurrRasterizationState.frontFace != state.frontFace)
		{
			glFrontFace(state.frontFace);
			mCurrRasterizationState.frontFace = state.frontFace;
		}
	}

	if (mCurrRasterizationState.polygonMode != state.polygonMode)
	{
		glPolygonMode(GL_FRONT_AND_BACK, state.polygonMode);
		mCurrRasterizationState.polygonMode = state.polygonMode;
	}

	if (mCurrRasterizationState.polygonOffsetFillEnable != state.polygonOffsetFillEnable)
	{
		if (state.polygonOffsetFillEnable)
		{
			glEnable(GL_POLYGON_OFFSET_FILL);
		}
		else
		{
			glDisable(GL_POLYGON_OFFSET_FILL);
		}

		mCurrRasterizationState.polygonOffsetFillEnable = state.polygonOffsetFillEnable;
	}

	if (mCurrRasterizationState.polygonOffsetLineEnable != state.polygonOffsetLineEnable)
	{
		if (state.polygonOffsetLineEnable)
		{
			glEnable(GL_POLYGON_OFFSET_LINE);
		}
		else
		{
			glDisable(GL_POLYGON_OFFSET_LINE);
		}

		mCurrRasterizationState.polygonOffsetLineEnable = state.polygonOffsetLineEnable;
	}

	if (mCurrRasterizationState.polygonOffsetPointEnable != state.polygonOffsetPointEnable)
	{
		if (state.polygonOffsetPointEnable)
		{
			glEnable(GL_POLYGON_OFFSET_POINT);
		}
		else
		{
			glDisable(GL_POLYGON_OFFSET_POINT);
		}

		mCurrRasterizationState.polygonOffsetPointEnable = state.polygonOffsetPointEnable;
	}

	if (mCurrRasterizationState.polygonOffsetFactor != state.polygonOffsetFactor ||
		mCurrRasterizationState.polygonOffsetUnits != state.polygonOffsetUnits)
	{
		glPolygonOffset(state.polygonOffsetFactor, state.polygonOffsetUnits);

		mCurrRasterizationState.polygonOffsetFactor = state.polygonOffsetFactor;
		mCurrRasterizationState.polygonOffsetUnits = state.polygonOffsetUnits;
	}

	if (mCurrRasterizationState.lineWidth != state.lineWidth)
	{
		glLineWidth(state.lineWidth);
		mCurrRasterizationState.lineWidth = state.lineWidth;
	}

	mCurrRasterizationState.cullMode = state.cullMode;
}

void Graphics::setDepthStencilState(const DepthStencilState& state)
{
	if (mCurrDepthStencilState.depthTestEnable != state.depthTestEnable)
	{
		if (state.depthTestEnable)
		{
			glEnable(GL_DEPTH_TEST);
		}
		else
		{
			glDisable(GL_DEPTH_TEST);
		}
	}

	if (state.depthTestEnable)
	{
		if (!mCurrDepthStencilState.depthBoundsTestEnable ||
			mCurrDepthStencilState.depthCompareFunction != state.depthCompareFunction)
		{
			glDepthFunc(state.depthCompareFunction);
			mCurrDepthStencilState.depthCompareFunction = state.depthCompareFunction;
		}
	}

	if (mCurrDepthStencilState.depthWriteEnable != state.depthWriteEnable)
	{
		glDepthMask(state.depthWriteEnable);
		mCurrDepthStencilState.depthWriteEnable = state.depthWriteEnable;
	}

	if (mCurrDepthStencilState.stencilTestEnable != state.stencilTestEnable)
	{
		if (state.stencilTestEnable)
		{
			glEnable(GL_STENCIL_TEST);
		}
		else
		{
			glDisable(GL_STENCIL_TEST);
		}
	}

	if (state.stencilTestEnable)
	{
		setStencilState(GL_FRONT, state.frontStencil, mCurrDepthStencilState.frontStencil);
		setStencilState(GL_BACK, state.backStencil, mCurrDepthStencilState.backStencil);
	}

	mCurrDepthStencilState.depthTestEnable = state.depthTestEnable;
	mCurrDepthStencilState.stencilTestEnable = state.stencilTestEnable;
}

void Graphics::setStencilState(GLenum face, const StencilState& state,
	StencilState& currStencilState)
{
	if (currStencilState.onPass != state.onPass ||
		currStencilState.onFail != state.onFail ||
		currStencilState.onDepthFail != state.onDepthFail)
	{
		glStencilOpSeparate(face, state.onFail, state.onDepthFail, state.onPass);

		currStencilState.onPass = state.onPass;
		currStencilState.onFail = state.onFail;
		currStencilState.onDepthFail = state.onDepthFail;
	}

	if (currStencilState.compareFunction != state.compareFunction ||
		currStencilState.compareMask != state.compareMask ||
		currStencilState.reference != state.reference)
	{
		glStencilFuncSeparate(face, state.compareFunction, state.reference, state.compareMask);

		currStencilState.compareFunction = state.compareFunction;
		currStencilState.compareMask = state.compareMask;
		currStencilState.reference = state.reference;
	}

	if (currStencilState.writeMask != state.writeMask)
	{
		glStencilMaskSeparate(face, state.writeMask);
		currStencilState.writeMask = state.writeMask;
	}
}

void Graphics::initDebug()
{
	glDebugMessageCallback(debugCallback, nullptr);
	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, nullptr, GL_FALSE);
}