#pragma once

#include <inttypes.h>
#include <stdbool.h>

#include <Memory/AllocatorClass.h>
#include <ResourceReference.h>
#include <Util/HashName.h>

#include <glad/vulkan.h>

namespace Render
{
class ShaderModule;

struct ShaderStageDescriptor
{
   ResourceRef<ShaderModule> m_shaderModule;
   VkShaderStageFlagBits m_shaderStage;
   Foundation::Util::HashName m_entryPoint;
};

class ShaderStage : public RenderResource<ShaderStage>
{
 public:
   static constexpr size_t ShaderStagePageCount = 12u;
   CLASS_ALLOCATOR_PAGECOUNT_PAGESIZE(ShaderStage, ShaderStagePageCount);

   ShaderStage() = delete;
   ShaderStage(ShaderStageDescriptor&& p_desc);
   ~ShaderStage();

   VkPipelineShaderStageCreateInfo GetShaderStageCreateInfoNative() const;

 private:
   ResourceRef<ShaderModule> m_shaderModule;
   Foundation::Util::HashName m_entryPoint;

   VkPipelineShaderStageCreateInfo m_shaderStageCreateInfoNative = {};
};
} // namespace Render
