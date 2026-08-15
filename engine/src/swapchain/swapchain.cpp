#include "swapchain.hpp"
#include <algorithm>
#include <stdexcept>


//here we will decide the purpose and the format for each of the swapchain images
Swapchain::Swapchain(VkDevice device, VkPhysicalDevice physicalDevice, VkSurfaceKHR surface, GLFWwindow *window)
    : m_device(device) {
  createSwapchain(physicalDevice, surface, window);
}
Swapchain::~Swapchain() { vkDestroySwapchainKHR(m_device, m_swapchain, nullptr); }

VkSurfaceFormatKHR Swapchain::chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR> &f) {
  for (const auto &fmt : f) if (fmt.format == VK_FORMAT_B8G8R8A8_SRGB && fmt.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) return fmt;
  return f[0];
}
VkPresentModeKHR Swapchain::chooseSwapPresentMode(const std::vector<VkPresentModeKHR> &m) {
  for (const auto &mode : m) if (mode == VK_PRESENT_MODE_MAILBOX_KHR) return mode;
  return VK_PRESENT_MODE_FIFO_KHR;
}
VkExtent2D Swapchain::chooseSwapExtent(const VkSurfaceCapabilitiesKHR &cap, GLFWwindow *w) {
  if (cap.currentExtent.width != UINT32_MAX) return cap.currentExtent;
  int width, height; glfwGetFramebufferSize(w, &width, &height);
  return { std::clamp(static_cast<uint32_t>(width), cap.minImageExtent.width, cap.maxImageExtent.width),
           std::clamp(static_cast<uint32_t>(height), cap.minImageExtent.height, cap.maxImageExtent.height) };
}
void Swapchain::createSwapchain(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface, GLFWwindow *window) {
  auto support = SwapchainSupport::query(physicalDevice, surface);
  auto format = chooseSwapSurfaceFormat(support.formats);
  auto mode = chooseSwapPresentMode(support.presentModes);
  auto extent = chooseSwapExtent(support.capabilities, window);
  uint32_t imageCount = support.capabilities.minImageCount + 1;
  if (support.capabilities.maxImageCount > 0 && imageCount > support.capabilities.maxImageCount)
    imageCount = support.capabilities.maxImageCount;

  VkSwapchainCreateInfoKHR createInfo{VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR};
  createInfo.surface = surface;
  createInfo.minImageCount = imageCount;
  createInfo.imageFormat = format.format;
  createInfo.imageColorSpace = format.colorSpace;
  createInfo.imageExtent = extent;
  createInfo.imageArrayLayers = 1;//for now i am only using one layer inside each swapchain
  createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
  createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
  createInfo.preTransform = support.capabilities.currentTransform;
  createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
  createInfo.presentMode = mode;
  createInfo.clipped = VK_TRUE;

  if (vkCreateSwapchainKHR(m_device, &createInfo, nullptr, &m_swapchain) != VK_SUCCESS)
    throw std::runtime_error("Failed to create swapchain");
  m_format = format.format; m_extent = extent;
}
