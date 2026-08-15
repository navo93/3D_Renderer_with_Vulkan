#pragma once
#include <vulkan/vulkan.h>
#include"GLFW/glfw3.h"


class WindowSurface {
public:
  WindowSurface(VkInstance instance, GLFWwindow *window);
  ~WindowSurface();

  // Rule of 5: Prevent accidental copying
  WindowSurface(const WindowSurface &) = delete;
  WindowSurface &operator=(const WindowSurface &) = delete;

  VkSurfaceKHR get() const { return m_surface; }

private:
  VkInstance m_instance;
  VkSurfaceKHR m_surface{VK_NULL_HANDLE};
};