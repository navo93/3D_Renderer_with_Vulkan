#include"app.hpp"
#include<chrono>
#include<memory>
#include<iostream>


App::App(){
    std::cout<<"starring the application"<<std::endl;
    m_instance=std::make_unique<VulkanInstance>("Engine");
    

}


App::~App(){
    


}

void App::Run(){

    
    while(!m_window.shouldClose()){
        m_window.pollEvents();
    }

}


