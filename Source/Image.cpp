#include <Image.h>

#include <std/unordered_map_bootstrap.h>

#include <Util/Util.h>

#include <Renderer.h>
#include <VulkanDevice.h>
#include <Swapchain.h>

namespace Render
{
Image::Image([[maybe_unused]] ImageDescriptor&& p_desc)
{
   m_vulkanDeviceRef = p_desc.m_vulkanDeviceRef;
}

Image::Image(ImageDescriptor2&& p_desc)
{
   m_vulkanDeviceRef = p_desc.m_vulkanDeviceRef;
   m_swapchainRef = p_desc.m_swapchainRef;
   m_swapchainIndex = p_desc.m_swapchainIndex;

   VkExtent2D extend = m_swapchainRef->GetExtend();

   m_image = m_swapchainRef->GetSwapchainImageNative(m_swapchainIndex);
   m_extend = VkExtent3D{.width = extend.width, .height = extend.height, .depth = 1u};
   m_colorFormat = m_swapchainRef->GetFormat();
}

Image::~Image()
{
}

bool Image::IsSwapchainImage() const
{
   return m_swapchainRef.IsInitialized();
}

VkImage Image::GetImageNative() const
{
   return m_image;
}

VkFormat Image::GetImageFormatNative() const
{
   return m_colorFormat;
}

VkExtent3D Image::GetImageExtendNative() const
{
   return m_extend;
}

VkImageCreateFlagBits Image::ImageCreationFlagsToNative(ImageCreationFlags p_flags)
{
   static const Foundation::Std::unordered_map_bootstrap<ImageCreationFlags, VkImageCreateFlagBits> ImageCreationFlagsToNativeMap =
       {
           {ImageCreationFlags::Alias, VK_IMAGE_CREATE_ALIAS_BIT},
           {ImageCreationFlags::Cube_Or_CubeArray, VK_IMAGE_CREATE_CUBE_COMPATIBLE_BIT},
           {ImageCreationFlags::Array2D, VK_IMAGE_CREATE_2D_ARRAY_COMPATIBLE_BIT},
       };

   return Foundation::Util::FlagsToNativeHelper<VkImageCreateFlagBits>(ImageCreationFlagsToNativeMap, p_flags);
}

VkImageUsageFlagBits Image::ImageUsageFlagsToNative(ImageUsageFlags p_flags)
{
   static const Foundation::Std::unordered_map_bootstrap<ImageUsageFlags, VkImageUsageFlagBits> ImageUsageFlagsToNativeMap = {
       {ImageUsageFlags::TransferSource, VK_IMAGE_USAGE_TRANSFER_SRC_BIT},
       {ImageUsageFlags::TransferDestination, VK_IMAGE_USAGE_TRANSFER_DST_BIT},
       {ImageUsageFlags::Sampled, VK_IMAGE_USAGE_SAMPLED_BIT},
       {ImageUsageFlags::Storage, VK_IMAGE_USAGE_STORAGE_BIT},
       {ImageUsageFlags::ColorAttachment, VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT},
       {ImageUsageFlags::DepthStencilAttachment, VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT},
       {ImageUsageFlags::TransientAttachment, VK_IMAGE_USAGE_TRANSIENT_ATTACHMENT_BIT},
       {ImageUsageFlags::InputAttachment, VK_IMAGE_USAGE_INPUT_ATTACHMENT_BIT},
   };

   return Foundation::Util::FlagsToNativeHelper<VkImageUsageFlagBits>(ImageUsageFlagsToNativeMap, p_flags);
}

} // namespace Render
