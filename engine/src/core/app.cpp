#include"app.hpp"
#include<chrono>
#include<memory>
#include<iostream>
#include"CubeTextureSet.hpp"
#include<string>
#include<stdexcept>
#include"stb_image.h"

namespace {
    //these functions are to be only used ny this file->App.cpp
    //**function to load the cubetextures */
    CubeTextureSet LoadTexturesCube(){
        try{
            
            return CubeTextureSet::loadFromDirectory("./src/third_party/Resources/cube_textures");
        }
        catch(std::exception& e){
            std::cout<<e.what()<<std::endl;
            return CubeTextureSet::loadFromDirectory("./third_party/Resources/cube_textures");

        }

    }


}


App::App(){
    std::cout<<"starring the application"<<std::endl;
    m_Instance=std::make_unique<VulkanInstance>("Engine");
    m_surface=std::make_unique<WindowSurface>(m_Instance->get(),m_window.return_handle());
    m_physicalDevice=std::make_unique<PhysicalDevice>(m_Instance->get(),m_surface->get());
    m_logicalDevice = std::make_unique<LogicalDevice>(m_physicalDevice->get(),m_surface->get());
    m_swapchain=std::make_unique<Swapchain>(m_logicalDevice->get(),m_physicalDevice->get(),m_surface->get(),m_window.return_handle());
    m_swapchain_image_views=std::make_unique<SwapchainImageViews>(m_logicalDevice->get(),m_swapchain->get(),m_swapchain->getFormat());
    m_depth_resource=std::make_unique<DepthResources>(m_logicalDevice->get(),m_physicalDevice->get(),m_swapchain->getExtent());
    m_renderpass=std::make_unique<RenderPass>(m_logicalDevice->get(),m_swapchain->getFormat(),m_depth_resource->getFormat());
    m_framebuffers=std::make_unique<Framebuffers>(m_logicalDevice->get(),m_renderpass->get(),m_swapchain_image_views->get(),m_depth_resource->getImageView(),m_swapchain->getExtent());
    m_command_pool=std::make_unique<CommandPool>(m_logicalDevice->get(),m_logicalDevice->getGraphicsQueueIndex());
    //loading all the textures for the cube
    
    CubeTextureSet m_cube_textures=LoadTexturesCube();//this is possible beacuse we enables the move operator


    
}


App::~App(){


}

void App::Run(){

    
    while(!m_window.shouldClose()){
        m_window.pollEvents();
    }

}


