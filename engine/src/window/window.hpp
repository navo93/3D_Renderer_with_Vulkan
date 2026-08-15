#pragma once
#include<glfw/glfw3.h>
#include<string>
#include<functional>

class Window{
    public:
        Window(const uint32_t width,const uint32_t height,const std::string& title);
        ~Window();

        Window(const Window& )=delete;
        Window& operator=(const Window& )=delete;

        GLFWwindow* return_handle(){return m_window;}
        void pollEvents();
        bool shouldClose();

    private:

        GLFWwindow* m_window;
        uint32_t m_width;
        uint32_t m_height;
        const std::string& m_title;

        void initWindow();

};