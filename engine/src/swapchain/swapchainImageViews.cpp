#include "swapchainImageViews.hpp"
#include <stdexcept>

SwapchainImageViews::SwapchainImageViews(VkDevice device, VkSwapchainKHR swapchain, VkFormat format)
    : m_device(device) {
  retrieveImages(swapchain);
  createImageViews(format);
}

SwapchainImageViews::~SwapchainImageViews() {
  for (auto imageView : m_imageViews) {
    vkDestroyImageView(m_device, imageView, nullptr);
  }
}

void SwapchainImageViews::retrieveImages(VkSwapchainKHR swapchain) {
  uint32_t imageCount;
  vkGetSwapchainImagesKHR(m_device, swapchain, &imageCount, nullptr);
  m_images.resize(imageCount);
  vkGetSwapchainImagesKHR(m_device, swapchain, &imageCount, m_images.data());
}

void SwapchainImageViews::createImageViews(VkFormat format) {
  m_imageViews.resize(m_images.size());
  for (size_t i = 0; i < m_images.size(); i++) {
    VkImageViewCreateInfo createInfo{VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO};
    createInfo.image = m_images[i];
    createInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
    createInfo.format = format;
    createInfo.components = {VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY,
                             VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY};
    createInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    createInfo.subresourceRange.baseMipLevel = 0;
    createInfo.subresourceRange.levelCount = 1;
    createInfo.subresourceRange.baseArrayLayer = 0;
    createInfo.subresourceRange.layerCount = 1;

    if (vkCreateImageView(m_device, &createInfo, nullptr, &m_imageViews[i]) != VK_SUCCESS) {
      throw std::runtime_error("Failed to create image views");
    }
  }
}
