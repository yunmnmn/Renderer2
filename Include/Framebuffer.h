#pragma once

#include <inttypes.h>
#include <stdbool.h>

#include <vulkan/vulkan.h>

#include <Memory/AllocatorClass.h>

#include <ResourceReference.h>
#include <RendererTypes.h>

using namespace Foundation;

namespace Render
{

class VulkanDevice;
class RenderPass;
class ImageView;

struct FrameBufferDescriptor
{
   ResourceRef<VulkanDevice> m_vulkanDeviceRef;
   ResourceRef<RenderPass> m_renderPassRef;
   Std::vector<ResourceRef<ImageView>> m_attachmentRefs;

   FrameBufferCreateFlags m_frameBufferCreateFlags;
};

// ShaderSet is used bind shader resources (image view, buffer view, UAV)
class Framebuffer : public RenderResource<Framebuffer>
{
   friend class Shader;

 public:
   static constexpr size_t PageCount = 12u;
   CLASS_ALLOCATOR_PAGECOUNT_PAGESIZE(Framebuffer, PageCount);

   Framebuffer() = delete;
   Framebuffer(FrameBufferDescriptor&& p_desc);
   ~Framebuffer();

   VkFramebuffer GetFrameBufferNative() const;

 private:
   ResourceRef<VulkanDevice> m_vulkanDeviceRef;
   ResourceRef<RenderPass> m_renderPassRef;
   Std::vector<ResourceRef<ImageView>> m_attachmentRefs;
   FrameBufferCreateFlags m_frameBufferCreateFlags;

   VkFramebuffer m_frameBufferNative = VK_NULL_HANDLE;
};
}; // namespace Render
