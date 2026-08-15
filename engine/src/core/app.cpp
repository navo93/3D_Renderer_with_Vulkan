#include"app.hpp"
#include<chrono>
#include<memory>
#include<iostream>


App::App(){
    std::cout<<"starring the application"<<std::endl;
    m_Instance=std::make_unique<VulkanInstance>("Engine");
    m_surface=std::make_unique<WindowSurface>(m_Instance->get(),m_window.return_handle());
    m_physicalDevice=std::make_unique<PhysicalDevice>(m_Instance->get(),m_surface->get());
    m_logicalDevice = std::make_unique<LogicalDevice>(m_physicalDevice->get(),m_surface->get());
    m_swapchain=std::make_unique<Swapchain>(m_logicalDevice->get(),m_physicalDevice->get(),m_surface->get(),m_window.return_handle());
    m_swapchain_image_views=std::make_unique<SwapchainImageViews>(m_logicalDevice->get(),m_swapchain->get(),m_swapchain->getFormat());
    

}


App::~App(){


}

void App::Run(){

    
    while(!m_window.shouldClose()){
        m_window.pollEvents();
    }

}


