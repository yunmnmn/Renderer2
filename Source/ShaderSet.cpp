#include <ShaderSet.h>

#include <VulkanInstanceInterface.h>
#include <VulkanDevice.h>

#include <DescriptorPoolManagerInterface.h>

namespace Render
{

ShaderSet::ShaderSet([[maybe_unused]] ShaderSetDescriptor&& p_desc)
{
   // m_descriptorSetLayoutRef = p_desc.m_descriptorSetLayoutRef;
   // m_shaderRef = p_desc.m_shaderRef;

   // Add resource dependencies
   {
      // AddDependency(m_descriptorSetLayoutRef);
      // AddDependency(m_shaderRef);
   }

   //// Allocate a DescriptorSet
   // m_descriptorSet = DescriptorPoolManagerInterface::Get()->AllocateDescriptorSet(m_descriptorSetLayoutRef);
}

ShaderSet::~ShaderSet()
{
}
} // namespace Render
