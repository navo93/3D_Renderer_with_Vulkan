//creating a depth image for storing the depth of each fragment 
//this step is necessary for overlaying one image over the other
//in case if two images overlap the gpu could decide which image to renderand which not to by looking at the depth value of the fragment stored in the 
//depth image

#pragma once
#include <vulkan/vulkan.h>

class DepthResources {
public:
  DepthResources(VkDevice device, VkPhysicalDevice physical_device,
                 VkExtent2D extent);
  ~DepthResources();

  DepthResources(const DepthResources &) = delete;
  DepthResources &operator=(const DepthResources &) = delete;

  VkImageView getImageView() const { return m_depth_image_view; }
  VkFormat getFormat() const { return m_depth_format; }

private:
  uint32_t findMemoryType(VkPhysicalDevice physical_device,
                          uint32_t type_filter,
                          VkMemoryPropertyFlags properties) const;
  void createDepthImage(VkPhysicalDevice physical_device, VkExtent2D extent);
  void createDepthImageView();

  VkDevice m_device{VK_NULL_HANDLE};
  VkImage m_depth_image{VK_NULL_HANDLE};
  VkDeviceMemory m_depth_memory{VK_NULL_HANDLE};
  VkImageView m_depth_image_view{VK_NULL_HANDLE};
  VkFormat m_depth_format{VK_FORMAT_D32_SFLOAT}; // i am using this format for the depth image
};