#include "mrender/gfx/geometry.hpp"

namespace mrender {

GeometryImplementation::GeometryImplementation(const BufferLayout& layout, void* vertexData, uint32_t vertexSize, std::vector<uint16_t> indices)
	: mIndexData(indices), mVertexData(static_cast<uint8_t*>(vertexData))
{
	bgfx::VertexLayout bgfxLayout;
	bgfxLayout.begin();
	for (auto& element : layout)
	{
		bgfxLayout.add(attribToBgfx(element.mAttrib), element.mNum,
			attribTypeToBgfx(element.mAttribType), element.mAttribType == BufferElement::AttribType::Uint8 || element.mAttribType == BufferElement::AttribType::Int16, element.mAttribType == BufferElement::AttribType::Int16);
					// @todo Need a better solution to "normalized" param
	}
	bgfxLayout.end();

    mVertexBufferHandle = bgfx::createVertexBuffer(
        bgfx::makeRef(mVertexData, vertexSize),
		bgfxLayout);
    mIndexBufferHandle = bgfx::createIndexBuffer(
        bgfx::makeRef(mIndexData.data(), static_cast<uint32_t>(mIndexData.size() * sizeof(uint16_t))));
}

bgfx::Attrib::Enum GeometryImplementation::attribToBgfx(const BufferElement::Attrib& attrib)
{
	switch (attrib)
	{
	case BufferElement::Attrib::Position:
		return bgfx::Attrib::Position;

	case BufferElement::Attrib::Normal:
		return bgfx::Attrib::Normal;

	case BufferElement::Attrib::Tangent:
		return bgfx::Attrib::Tangent;

	case BufferElement::Attrib::Bitangent:
		return bgfx::Attrib::Bitangent;

	case BufferElement::Attrib::Color0:
		return bgfx::Attrib::Color0;

	case BufferElement::Attrib::Color1:
		return bgfx::Attrib::Color1;

	case BufferElement::Attrib::Color2:
		return bgfx::Attrib::Color2;

	case BufferElement::Attrib::Color3:
		return bgfx::Attrib::Color3;

	case BufferElement::Attrib::Indices:
		return bgfx::Attrib::Indices;

	case BufferElement::Attrib::Weight:
		return bgfx::Attrib::Weight;

	case BufferElement::Attrib::TexCoord0:
		return bgfx::Attrib::TexCoord0;

	case BufferElement::Attrib::TexCoord1:
		return bgfx::Attrib::TexCoord1;

	case BufferElement::Attrib::TexCoord2:
		return bgfx::Attrib::TexCoord2;

	case BufferElement::Attrib::TexCoord3:
		return bgfx::Attrib::TexCoord3;

	case BufferElement::Attrib::TexCoord4:
		return bgfx::Attrib::TexCoord4;

	case BufferElement::Attrib::TexCoord5:
		return bgfx::Attrib::TexCoord5;

	case BufferElement::Attrib::TexCoord6:
		return bgfx::Attrib::TexCoord6;

	case BufferElement::Attrib::TexCoord7:
		return bgfx::Attrib::TexCoord7;

	default:
		return bgfx::Attrib::Position;
	}
}

bgfx::AttribType::Enum GeometryImplementation::attribTypeToBgfx(const BufferElement::AttribType& attribType)
{
	switch (attribType)
	{
	case BufferElement::AttribType::Uint8:
		return bgfx::AttribType::Uint8;

	case BufferElement::AttribType::Uint10:
		return bgfx::AttribType::Uint10;

	case BufferElement::AttribType::Int16:
		return bgfx::AttribType::Int16;

	case BufferElement::AttribType::Half:
		return bgfx::AttribType::Half;

	case BufferElement::AttribType::Float:
		return bgfx::AttribType::Float;

	default:
		return bgfx::AttribType::Float;
	}
}

}	// namespace mrender