#pragma once
#include <vulkan/vulkan.h>
#include <vector>
#include "swapchainSupport.hpp"
#include"GLFW/glfw3.h"



class Swapchain {
public:
  Swapchain(VkDevice device, VkPhysicalDevice physicalDevice, VkSurfaceKHR surface, GLFWwindow *window);
  ~Swapchain();

  Swapchain(const Swapchain &) = delete;
  Swapchain &operator=(const Swapchain &) = delete;

  VkSwapchainKHR get() const { return m_swapchain; }
  VkFormat getFormat() const { return m_format; }
  VkExtent2D getExtent() const { return m_extent; }

private:
  void createSwapchain(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface, GLFWwindow *window);
  VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR> &availableFormats);
  VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR> &availablePresentModes);
  VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR &capabilities, GLFWwindow *window);

  VkDevice m_device;
  VkSwapchainKHR m_swapchain{VK_NULL_HANDLE};
  VkFormat m_format;
  VkExtent2D m_extent;
};