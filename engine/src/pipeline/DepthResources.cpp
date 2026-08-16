#include "DepthResources.hpp"
#include <stdexcept>


/*

this depth image shall be attached with each of the framebuffer thus recording the depth value of each fragment per subpass

*/
DepthResources::DepthResources(VkDevice device,
                               VkPhysicalDevice physical_device,
                               VkExtent2D extent)
    : m_device(device) {
  createDepthImage(physical_device, extent);
  createDepthImageView();
}

DepthResources::~DepthResources() {
  if (m_depth_image_view != VK_NULL_HANDLE) {
    vkDestroyImageView(m_device, m_depth_image_view, nullptr);
  }
  if (m_depth_image != VK_NULL_HANDLE) {
    vkDestroyImage(m_device, m_depth_image, nullptr);
  }
  if (m_depth_memory != VK_NULL_HANDLE) {
    vkFreeMemory(m_device, m_depth_memory, nullptr);
  }
}

uint32_t DepthResources::findMemoryType(VkPhysicalDevice physical_device,
                                        uint32_t type_filter,
                                        VkMemoryPropertyFlags properties) const {
  VkPhysicalDeviceMemoryProperties memory_properties{};
  vkGetPhysicalDeviceMemoryProperties(physical_device, &memory_properties);
  for (uint32_t i = 0; i < memory_properties.memoryTypeCount; ++i) {
    bool type_matches = type_filter & (1 << i);
    bool flags_match =
        (memory_properties.memoryTypes[i].propertyFlags & properties) == properties;
    if (type_matches && flags_match) {
      return i;
    }
  }
  throw std::runtime_error("Failed to find suitable depth memory type");
}

void DepthResources::createDepthImage(VkPhysicalDevice physical_device,
                                      VkExtent2D extent) {
  VkImageCreateInfo image_info{VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO};
  image_info.imageType = VK_IMAGE_TYPE_2D;
  image_info.extent = {extent.width, extent.height, 1};
  image_info.mipLevels = 1;
  image_info.arrayLayers = 1;
  image_info.format = m_depth_format;
  image_info.tiling = VK_IMAGE_TILING_OPTIMAL;
  image_info.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
  image_info.usage = VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT;
  image_info.samples = VK_SAMPLE_COUNT_1_BIT;
  image_info.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
  if (vkCreateImage(m_device, &image_info, nullptr, &m_depth_image) != VK_SUCCESS) {
    throw std::runtime_error("Failed to create depth image");
  }

  VkMemoryRequirements requirements{};
  vkGetImageMemoryRequirements(m_device, m_depth_image, &requirements);
  VkMemoryAllocateInfo allocate_info{VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO};
  allocate_info.allocationSize = requirements.size;
  allocate_info.memoryTypeIndex = findMemoryType(
      physical_device, requirements.memoryTypeBits,
      VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
  if (vkAllocateMemory(m_device, &allocate_info, nullptr, &m_depth_memory) != VK_SUCCESS) {
    throw std::runtime_error("Failed to allocate depth image memory");
  }
  vkBindImageMemory(m_device, m_depth_image, m_depth_memory, 0); //bond the info with the memeory
}

void DepthResources::createDepthImageView() {
  VkImageViewCreateInfo view_info{VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO};
  view_info.image = m_depth_image;
  view_info.viewType = VK_IMAGE_VIEW_TYPE_2D;
  view_info.format = m_depth_format;
  view_info.subresourceRange.aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT;
  view_info.subresourceRange.baseMipLevel = 0;//miplevel for this layer(sub-image)
  view_info.subresourceRange.levelCount = 1; //how many miplevels included
  view_info.subresourceRange.baseArrayLayer = 0; //starting index of the sub-image
  view_info.subresourceRange.layerCount = 1;//how many sub-images to incude
  if (vkCreateImageView(m_device, &view_info, nullptr, &m_depth_image_view) != VK_SUCCESS) {
    throw std::runtime_error("Failed to create depth image view");
  }
}