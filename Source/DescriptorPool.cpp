#include <DescriptorPool.h>
#include <DescriptorSetLayout.h>
#include <DescriptorSet.h>

#include <Util/Assert.h>

namespace Render
{
eastl::unique_ptr<DescriptorPool> DescriptorPool::CreateInstance(Descriptor&& p_desc)
{
   return eastl::unique_ptr<DescriptorPool>(new DescriptorPool(eastl::move(p_desc)));
}

DescriptorPool::DescriptorPool(Descriptor&& p_desc)
{
   m_poolReference = eastl::shared_ptr<DescriptorPool*>(new DescriptorPool*(this));

   m_descriptorPoolSizes = eastl::move(p_desc.m_descriptorPoolSizes);

   // Create the DescriptorPool
   VkDescriptorPoolCreateInfo descriptorPoolInfo = {};
   descriptorPoolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
   descriptorPoolInfo.pNext = nullptr;
   descriptorPoolInfo.poolSizeCount = m_descriptorPoolSizes.size();
   descriptorPoolInfo.pPoolSizes = m_descriptorPoolSizes.data();
   // TODO: For now, don't limit the amount of descriptors that are able to allocate from this
   descriptorPoolInfo.maxSets = static_cast<uint32_t>(-1);

   VulkanDevice* vulkanDevice = VulkanInstanceInterface::Get()->GetSelectedPhysicalDevice();
   VkResult result = vkCreateDescriptorPool(vulkanDevice->GetLogicalDevice(), &descriptorPoolInfo, nullptr, &m_descriptorPool);
   ASSERT(result == VK_SUCCESS, "Failed to create the DescriptorPool");
}

DescriptorPool::~DescriptorPool()
{
}

eastl::tuple<eastl::unique_ptr<DescriptorSet>, bool> DescriptorPool::AllocateDescriptorSet(DescriptorSetLayout* p_descriptorLayout)
{
   ASSERT(p_descriptorLayout != nullptr, "Invalid DescriptorLayout");
   ASSERT(m_descriptorPool != VK_NULL_HANDLE, "DescriptorPool isn't created");

   VkDescriptorSetLayout descriptorSetLayout = p_descriptorLayout->GetDescriptorSetLayout();

   // Create the DescriptorSet
   DescriptorSet::Descriptor desc;
   desc.m_descriptorSetLayout = p_descriptorLayout;
   desc.m_poolReference = eastl::weak_ptr<DescriptorPool*>(m_poolReference);
   eastl::unique_ptr<DescriptorSet> descriptorSet = DescriptorSet::CreateInstance(DescriptorSet::Descriptor{});

   if (descriptorSet)
   {
      return eastl::make_tuple(descriptorSet, true);
   }

   return eastl::make_tuple(nullptr, false);
}

}; // namespace Render
