#pragma once
#include<iostream>
#include<vector>
#include<string>
#include<vulkan/vulkan.h>



class VulkanInstance{
public:
  VulkanInstance(const std::string &appName);
  ~VulkanInstance();

  // Prevention of copying of the raw Vulkan handle
  VulkanInstance(const VulkanInstance &) = delete;
  VulkanInstance &operator=(const VulkanInstance &) = delete;

  inline VkInstance get() const { return m_instance; }

private:
  void createInstance(const std::string &appName);
  std::vector<const char *> getRequiredExtensions();

  VkInstance m_instance{VK_NULL_HANDLE};


};