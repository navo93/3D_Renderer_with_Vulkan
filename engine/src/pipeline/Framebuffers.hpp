/*

now during the renderpass or subpass the graphics pipeline needs the images during the rasterization process to actually 
write the depth value of each framgment to the depth image and the color value to each color image of the swapchain
for that it calls the framebuffer of that frame .the framebuffer of that frame contains both the color_image[frame_count] and the depth image
*/
#pragma once
#include <vulkan/vulkan.h>
#include <vector>

class Framebuffers {
public:
  Framebuffers(VkDevice device, VkRenderPass renderPass,
               const std::vector<VkImageView> &imageViews,
               VkImageView depthImageView, VkExtent2D extent);
  ~Framebuffers();

  Framebuffers(const Framebuffers &) = delete;
  Framebuffers &operator=(const Framebuffers &) = delete;

  const std::vector<VkFramebuffer> &get() const { return m_framebuffers; }

private:
  void createFramebuffers(VkRenderPass renderPass,
                          const std::vector<VkImageView> &imageViews,
                          VkImageView depthImageView, VkExtent2D extent);

  VkDevice m_device;
  std::vector<VkFramebuffer> m_framebuffers;
};
