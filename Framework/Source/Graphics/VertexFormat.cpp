#include "Graphics/VertexFormat.h"

VertexFormat::VertexFormat(std::vector<VertexElement> elements)
	: mElements(std::move(elements))
{
	for (const auto& element : mElements)
	{
		mSize += element.size;
	}
}