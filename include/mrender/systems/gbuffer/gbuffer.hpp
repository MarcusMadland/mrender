#pragma once

#include "mrender/mrender.hpp"

namespace mrender {

class GBuffer : public RenderSystem
{
public:
    GBuffer();
    ~GBuffer();

    bool init(GfxContext* context) override;
    void render(GfxContext* context) override;

    BufferList getBuffers(GfxContext* context) override;
    UniformDataList getUniformData(GfxContext* context) override;

private:
    RenderStateHandle mGeometryState;
    FramebufferHandle mGeometryFramebuffer;
    BufferList mGeometryBuffers;

    RenderStateHandle mLightState;
    FramebufferHandle mLightFramebuffer;
    BufferList mLightBuffers;
    ShaderHandle mLightShader;

    GeometryHandle mScreenQuad;
    struct VertexData
    {
        float x;
        float y;
        float z;
        float texX;
        float texY;
    };
    std::vector<VertexData> mQuadVertices =
    {
        { -1.0f,  1.0f, 0.0f,  0.0f,0.0f },
        {  1.0f,  1.0f, 0.0f,  1.0f,0.0f },
        { -1.0f, -1.0f, 0.0f,  0.0f,1.0f },
        {  1.0f, -1.0f, 0.0f,  1.0f,1.0f },
    };
    const std::vector<uint16_t> mQuadIndices =
    {
        0, 1, 2, 1, 3, 2,
    };
};

}   // namespace mrender
