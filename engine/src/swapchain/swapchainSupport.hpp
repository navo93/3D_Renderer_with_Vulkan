#pragma once
#include <vulkan/vulkan.h>
#include <vector>

struct SwapchainSupportDetails { //the object of this struct shall represent all the available capabilities of the swapchain images
  VkSurfaceCapabilitiesKHR capabilities;
  std::vector<VkSurfaceFormatKHR> formats;
  std::vector<VkPresentModeKHR> presentModes;
};

class SwapchainSupport {
public:
  static SwapchainSupportDetails query(VkPhysicalDevice device, VkSurfaceKHR surface);
};