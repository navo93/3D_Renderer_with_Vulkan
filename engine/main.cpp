#include<iostream>
#include<stdexcept>
#include<memory>


int main(){
    try{
        

    }
    catch(std::exception& e){
        std::cerr<<e.what()<<std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}