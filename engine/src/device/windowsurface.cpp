#include "WindowSurface.hpp"
#include <GLFW/glfw3.h>
#include <stdexcept>

WindowSurface::WindowSurface(VkInstance instance, GLFWwindow *window)
    : m_instance(instance) {
  if (glfwCreateWindowSurface(instance, window, nullptr, &m_surface) != VK_SUCCESS) {
    throw std::runtime_error("Failed to create window surface");
  }
}

WindowSurface::~WindowSurface() {
  if (m_surface != VK_NULL_HANDLE) {
    vkDestroySurfaceKHR(m_instance, m_surface, nullptr);
  }
}
