#include"app.hpp"
#include<chrono>
#include<memory>
#include<iostream>


App::App(){
    std::cout<<"starring the application"<<std::endl;
    m_Instance=std::make_unique<VulkanInstance>("Engine");
    m_surface=std::make_unique<WindowSurface>(m_Instance->get(),m_window.return_handle());


}


App::~App(){


}

void App::Run(){

    
    while(!m_window.shouldClose()){
        m_window.pollEvents();
    }

}


