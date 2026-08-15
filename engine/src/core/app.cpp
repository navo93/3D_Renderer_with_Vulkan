#include"app.hpp"
#include<chrono>
#include<memory>
#include<iostream>


App::App(){
    std::cout<<"starring the application"<<std::endl;
    
}


App::~App(){
    


}

void App::Run(){

    
    while(!m_window.shouldClose()){
        m_window.pollEvents();
    }

}


