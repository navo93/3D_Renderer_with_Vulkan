#include "Framebuffers.hpp"
#include <array>
#include <stdexcept>

Framebuffers::Framebuffers(VkDevice device, VkRenderPass renderPass,
                           const std::vector<VkImageView> &imageViews,
                           VkImageView depthImageView, VkExtent2D extent)
    : m_device(device) {
  createFramebuffers(renderPass, imageViews, depthImageView, extent);
}

Framebuffers::~Framebuffers() {
  for (auto framebuffer : m_framebuffers) {
    vkDestroyFramebuffer(m_device, framebuffer, nullptr);
  }
}

void Framebuffers::createFramebuffers(VkRenderPass renderPass,
                                      const std::vector<VkImageView> &imageViews,
                                      VkImageView depthImageView,
                                      VkExtent2D extent) {
  m_framebuffers.resize(imageViews.size());

  for (size_t i = 0; i < imageViews.size(); i++) {
    std::array<VkImageView, 2> attachments = {imageViews[i], depthImageView};

    VkFramebufferCreateInfo framebufferInfo{};
    framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
    framebufferInfo.renderPass = renderPass;
    framebufferInfo.attachmentCount = static_cast<uint32_t>(attachments.size());
    framebufferInfo.pAttachments = attachments.data();
    framebufferInfo.width = extent.width;
    framebufferInfo.height = extent.height;
    framebufferInfo.layers = 1;

    if (vkCreateFramebuffer(m_device, &framebufferInfo, nullptr, &m_framebuffers[i]) != VK_SUCCESS) {
      throw std::runtime_error("Failed to create framebuffer");
    }
  }
}
