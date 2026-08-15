#pragma once
#include <vulkan/vulkan.h>
#include <vector>

class SwapchainImageViews {
public:
  SwapchainImageViews(VkDevice device, VkSwapchainKHR swapchain, VkFormat format);
  ~SwapchainImageViews();

  SwapchainImageViews(const SwapchainImageViews &) = delete;
  SwapchainImageViews &operator=(const SwapchainImageViews &) = delete;

  const std::vector<VkImageView> &get() const { return m_imageViews; }

private:
  void retrieveImages(VkSwapchainKHR swapchain);
  void createImageViews(VkFormat format);

  VkDevice m_device;
  std::vector<VkImage> m_images;
  std::vector<VkImageView> m_imageViews;
};
