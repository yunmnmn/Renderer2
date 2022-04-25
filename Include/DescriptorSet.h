#pragma once

#include <inttypes.h>
#include <stdbool.h>

#include <vulkan/vulkan.h>

#include <EASTL/unique_ptr.h>
#include <EASTL/shared_ptr.h>
#include <EASTL/weak_ptr.h>
#include <EASTL/span.h>

#include <Std/unordered_map.h>

#include <Memory/AllocatorClass.h>
#include <ResourceReference.h>

using namespace Foundation;

namespace Render
{

class VulkanDevice;
class DescriptorPool;
class BufferView;
class ImageView;
class DescriptorSetLayout;

struct DescriptorSetDescriptor
{
   ResourceRef<VulkanDevice> m_vulkanDeviceRef;
   ResourceRef<DescriptorPool> m_descriptorPoolRef;
};

class DescriptorSet : public RenderResource<DescriptorSet>
{
 public:
   static constexpr size_t DescriptorSetPageCount = 12u;
   CLASS_ALLOCATOR_PAGECOUNT_PAGESIZE(DescriptorSet, DescriptorSetPageCount);

   DescriptorSet() = delete;
   DescriptorSet(DescriptorSetDescriptor&& p_desc);
   ~DescriptorSet();

   void QueueResourceUpdate(uint32_t bindingIndex, uint32_t arrayOffset, eastl::span<const ResourceRef<BufferView>> p_bufferView);
   // void QueueResourceUpdate(uint32_t bindingIndex, uint32_t arrayOffset, const eastl::span<ResourceRef<ImageView>> p_imageViews);

   void SetDynamicOffset(uint32_t p_bindingIndex, uint32_t p_arrayOffset, eastl::span<uint32_t> p_dynamicOffsets);

   void GetDynamicOffsetsAsFlatArray(Std::vector<uint32_t>& dynamicOffsetArray) const;
   uint32_t GetDynamicOffsetCount() const;
   VkDescriptorSet GetDescriptorSetNative() const;

 private:
   // Vulkan Resource
   VkDescriptorSet m_descriptorSetNative = VK_NULL_HANDLE;

   // Members set by the descriptor
   ResourceRef<DescriptorPool> m_descriptorPool;
   ResourceRef<VulkanDevice> m_vulkanDevice;
   ResourceRef<DescriptorSetLayout> m_descriptorSetLayout;

   // Used for Dynamic Storage/Uniform Buffers
   Std::unordered_map<uint32_t, Std::vector<uint32_t>> m_dynamicOffsets;
};
}; // namespace Render
