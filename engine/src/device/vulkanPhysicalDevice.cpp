#include"vulkanPhysicalDevice.hpp"
#include"swapchainSupport.hpp"
#include<stdexcept>
#include<vulkan/vulkan.h>
#include<vector>

PhysicalDevice::PhysicalDevice(VkInstance instance, VkSurfaceKHR surface) {
  pickPhysicalDevice(instance, surface);
}

void PhysicalDevice::pickPhysicalDevice(VkInstance instance, VkSurfaceKHR surface) {
  uint32_t deviceCount = 0;
  vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);

  if (deviceCount == 0) {
    throw std::runtime_error("Failed to find GPUs with Vulkan support!");
  }

  std::vector<VkPhysicalDevice> devices(deviceCount);
  vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());

  for (const auto &device : devices) {
    if (isDeviceSuitable(device, surface)) {
      m_physicalDevice = device;
      break;
    }
  }

  if (m_physicalDevice == VK_NULL_HANDLE) {
    throw std::runtime_error("Failed to find a suitable GPU!");
  }
}

bool PhysicalDevice::isDeviceSuitable(VkPhysicalDevice device, VkSurfaceKHR surface) {
  // Query if the swapchain is adequate (has formats and present modes)
  SwapchainSupportDetails swapChainSupport = SwapchainSupport::query(device, surface);
  bool swapChainAdequate = !swapChainSupport.formats.empty() && !swapChainSupport.presentModes.empty();

  return swapChainAdequate;
}
