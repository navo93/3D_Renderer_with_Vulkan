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
#include"logicalDevice.hpp"
#include"swapchain.hpp"
#include"swapchainImageVIews.hpp"
#include"DepthResources.hpp"
#include"RenderPass.hpp"
#include"Framebuffers.hpp"
#include"CommandPool.hpp"



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
        std::unique_ptr<LogicalDevice>m_logicalDevice;
        std::unique_ptr<Swapchain>m_swapchain;
        std::unique_ptr<SwapchainImageViews>m_swapchain_image_views;
        std::unique_ptr<DepthResources>m_depth_resource;//creating only one beacuse i can reuse the same image again after each frame
        std::unique_ptr<RenderPass>m_renderpass;
        std::unique_ptr<Framebuffers>m_framebuffers;
        std::unique_ptr<CommandPool>m_command_pool;
        //load all the textures to be applied to the cube under one structure
        

};