#pragma once
#include<memory>
#include<chrono>
#include<functional>
#include"window.hpp"
#include"camera.hpp"
#include"ModelMesh.hpp"
#include"vulkanInstance.hpp"
#include"windowsurface.hpp"
#include"vulkanPhysicalDevice.hpp"



class App{
    public:
    static constexpr uint32_t WIDTH=900;
    static constexpr uint32_t HEIGHT=900;
    static constexpr int MAX_FRAMES_IN_FLIGHT=3;

    App();
    ~App();

     App(const App& )=delete;
     App& operator=(const App& other) = delete;

    void Run();

    private:
        
        Window m_window{WIDTH,HEIGHT,"project_engine"};
        Camera m_camera;
        LoadedModel m_generator_model;
        std::unique_ptr<VulkanInstance> m_Instance;
        std::unique_ptr<WindowSurface>m_surface;
        std::unique_ptr<PhysicalDevice>m_physicalDevice;

};