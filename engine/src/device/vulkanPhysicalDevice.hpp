#pragma once
#include<vulkan/vulkan.h>

class PhysicalDevice {
public:
  PhysicalDevice(VkInstance instance, VkSurfaceKHR surface);
  ~PhysicalDevice() = default;

  // Rule of 5: Prevent accidental copying of the device reference
  PhysicalDevice(const PhysicalDevice &) = delete;
  PhysicalDevice &operator=(const PhysicalDevice &) = delete;

  VkPhysicalDevice get() const { return m_physicalDevice; }

private:
  void pickPhysicalDevice(VkInstance instance, VkSurfaceKHR surface);
  bool isDeviceSuitable(VkPhysicalDevice device, VkSurfaceKHR surface);

  VkPhysicalDevice m_physicalDevice{VK_NULL_HANDLE};
};