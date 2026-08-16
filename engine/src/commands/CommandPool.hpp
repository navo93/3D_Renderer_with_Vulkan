/*
the gpu executes the commands written in the command buffers,such as copying from thestagging buffer to the VRam and starting the 
graphics pipeleine,various instructions to follow while executing the fixed funstion stages of the graphics pipleine etc etc
now command buffers are to created from the command pool


here for continous rendering purpose by thr graphics pipeline we will allocate as many command buffers as the no of 
frames,ie one command buffer per frame
*/

#pragma once
#include <vulkan/vulkan.h>
#include <vector>

class CommandPool {
public:
  CommandPool(VkDevice device, uint32_t queueFamilyIndex); //we are getting the queufamily index 
  //beacuse this is where all the commands written in the command buffer shall be queued for 
  //the executin by the queue of that queue familly
  ~CommandPool();

  CommandPool(const CommandPool &) = delete;
  CommandPool &operator=(const CommandPool &) = delete;

  VkCommandPool get() const { return m_commandPool; }

  std::vector<VkCommandBuffer> allocateCommandBuffers(uint32_t count) const;
  //---------this is for making a command buffer and initiating the writing into that buffer for the gpu assited copying into the Vram 
  //from the stagging buffer-----------------------
  VkCommandBuffer beginSingleTimeCommands() const;
  void endSingleTimeCommands(VkQueue queue,
                             VkCommandBuffer commandBuffer) const;
//------------------------------------------------------------------------------------

private:
  void createCommandPool(uint32_t queueFamilyIndex);

  VkDevice m_device;
  VkCommandPool m_commandPool{VK_NULL_HANDLE};
};



