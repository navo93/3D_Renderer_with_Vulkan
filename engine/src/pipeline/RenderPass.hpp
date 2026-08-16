/*
encapsulates the entire subpasses->graphics pipeline
binds the graphics pipeline with the imageviews
*/
#pragma once
#include <vulkan/vulkan.h>

class RenderPass {
public:
  RenderPass(VkDevice device, VkFormat color_format, VkFormat depth_format);
  ~RenderPass();

  RenderPass(const RenderPass &) = delete;
  RenderPass &operator=(const RenderPass &) = delete;

  VkRenderPass get() const { return m_renderPass; }

private:
  void createRenderPass(VkFormat color_format, VkFormat depth_format);

  VkDevice m_device;
  VkRenderPass m_renderPass{VK_NULL_HANDLE};
};
