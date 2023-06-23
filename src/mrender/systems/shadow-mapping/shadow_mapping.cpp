#include "mrender/systems/shadow-mapping/shadow_mapping.hpp"
#include "mrender/core/file_ops.hpp"


#include "mrender/handler/shader.hpp" // @temp
#include "mrender/handler/render_context.hpp"
#include "mrender/handler/texture.hpp"
#include "mrender/handler/framebuffer.hpp"

#include <bgfx/bgfx.h>
#include <bx/math.h>

#define RENDER_SHADOW_PASS_ID 0

namespace mrender {

// @todo make options
static constexpr bool useShadowSampler = true;
static constexpr uint32_t shadowSize = 512;

ShadowMapping::ShadowMapping()
    : RenderSystem("Shadow Mapping")
{
}

ShadowMapping::~ShadowMapping()
{
}

bool ShadowMapping::init(mrender::RenderContext& context)
{ 
	// Shader
	context.loadShader("shadow", "C:/Users/marcu/Dev/mengine/mrender/shaders/shadow");

	// Camera
    CameraSettings cameraSettings;
	cameraSettings.projectionType = ProjectionType::Orthographic;
    cameraSettings.width = 30.0f;
    cameraSettings.height = 30.0f;
    cameraSettings.postion[2] = -5.0f;
    mCamera = context.createCamera(cameraSettings);

	// Framebuffer
	mFramebuffer = context.createFramebuffer({ "ShadowMap" });

	// Render State
	mState[0] = RenderState();
	mState[0].m_state = (0
		| BGFX_STATE_WRITE_Z
		| BGFX_STATE_DEPTH_TEST_LESS
		| BGFX_STATE_CULL_CCW
		| BGFX_STATE_MSAA);
	mState[0].m_viewId = RENDER_SHADOW_PASS_ID;
    
    return true;
}

void ShadowMapping::render(RenderContext& context)
{
	// Clear render pass
    bgfx::setViewRect(mState[0].m_viewId, 0, 0, shadowSize, shadowSize);
    bgfx::setViewFrameBuffer(mState[0].m_viewId, std::static_pointer_cast<FramebufferImplementation>(mFramebuffer)->mHandle);
    bgfx::setViewClear(mState[0].m_viewId
        , BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH
        , 0xff00ffff, 1.0f, 0);
    
	// Set current render pass id
	RenderContextImplementation& contextCasted = static_cast<RenderContextImplementation&>(context);
	contextCasted.mCurrentRenderPass = mState[0].m_viewId;

	// Set state
	bgfx::setState(mState[0].m_state);

	// Submit scene
	auto renderables = context.getRenderables();
	context.submit(renderables, mCamera);
}

std::unordered_map<std::string, std::shared_ptr<Texture>> ShadowMapping::getBuffers(RenderContext& context)
{
	std::unordered_map<std::string, std::shared_ptr<Texture>> buffers;
	buffers.emplace("ShadowMap", context.createTexture(TextureFormat::D16, BGFX_TEXTURE_RT | BGFX_SAMPLER_COMPARE_LEQUAL, shadowSize, shadowSize));
	return buffers;
}

}   // namespace mrender