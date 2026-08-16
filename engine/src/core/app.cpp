#include"app.hpp"
#include<chrono>
#include<memory>
#include<iostream>
#include"CubeTextureSet.hpp"
#include<string>
#include<stdexcept>
#include"stb_image.h"

namespace {
    //these functions are to be only used by this file->App.cpp
    //**function to load the cubetextures */
    CubeTextureSet LoadTexturesCube(){
        try{
            
            return CubeTextureSet::loadFromDirectory("/src/third_party/Resources/cube_textures");
        }
        catch(std::exception& e){
            std::cout<<e.what()<<std::endl;
            return CubeTextureSet::loadFromDirectory("../../../engine/src/third_party/Resources/cube_textures");

        }

    }

    //function to load the hdr skybox image to the cpu ram
    LoadedFloatImage LoadSkyboxImage(){
        try{
            LoadedFloatImage skybox_image=ImageLoader::loadFloat("./src/third_party/Resources/cubemap");
            return skybox_image;
        }
        catch(std::exception& e){
            std::cout<<e.what()<<std::endl;
            LoadedFloatImage skybox_image=ImageLoader::loadFloat("../../../engine/src/third_party/Resources/cubemap");
            return skybox_image;
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
    //m_cube_textures.pixels now holds the pointer to the cubes's textures in the cpu ram
    //information about the textures loaded
    std::cout<<"no of tetures loaded: "<<m_cube_textures.images.size()<<std::endl;
    std::cout<<"the extent of these images are:"<<"width->"<<m_cube_textures.width<<" height->"<<m_cube_textures.height<<std::endl;

    //now i will load the skybox image into the renderer->cpu ram
    //the LoadFloatImage struct returns a single pointer,handle to the loaded 2d hdr image

    LoadedFloatImage skybox_image=LoadSkyboxImage();
    //skybox_image.pixels now hold the pointer to the ram loaded skybox image
    std::cout<<"cubemap image's width:"<<skybox_image.width<<" height->"<<skybox_image.height<<std::endl;

}


App::~App(){


}

void App::Run(){

    
    while(!m_window.shouldClose()){
        m_window.pollEvents();
    }

}


