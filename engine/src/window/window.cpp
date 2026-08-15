#include"window.hpp"
#include<stdexcept>

Window::Window(const uint32_t width,const uint32_t height,const std::string& title):m_width(width),m_height(height),m_title(title){
    initWindow();
}

Window::~Window(){
    if(m_window!=nullptr){
        delete[] m_window;
        m_window=nullptr;
        glfwDestroyWindow(m_window);
        glfwTerminate();
    }
}

void Window::initWindow(){
    if (!glfwInit()) {
        throw std::runtime_error("Failed to initialize GLFW");
    }

  // Inform GLFW we are not using OpenGL context
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);  // Disable window resizing for simplicity in this initial stage
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    m_window =
      glfwCreateWindow(m_width, m_height, m_title.c_str(), nullptr, nullptr);
    if (!m_window) {
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window");
    }

}

bool Window::shouldClose(){
    return glfwWindowShouldClose(m_window);


}

void Window::pollEvents(){

    glfwPollEvents();

}