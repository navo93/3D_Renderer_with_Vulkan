#pragma once
#include<vulkan/vulkan.h>

class LogicalDevice{
public:
  LogicalDevice(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface);
  ~LogicalDevice();

  LogicalDevice(const LogicalDevice &) = delete;
  LogicalDevice &operator=(const LogicalDevice &) = delete;

  VkDevice get() const { return m_device; }
  VkQueue getGraphicsQueue() const { return m_graphicsQueue; }
  uint32_t getGraphicsQueueIndex() const { return m_graphicsQueueIndex; }

private:
  void findQueueFamilies(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface);
  void createLogicalDevice(VkPhysicalDevice physicalDevice);

  VkDevice m_device{VK_NULL_HANDLE};
  VkQueue m_graphicsQueue{VK_NULL_HANDLE};
  uint32_t m_graphicsQueueIndex{0};
  bool m_hasGraphicsQueue{false};


};