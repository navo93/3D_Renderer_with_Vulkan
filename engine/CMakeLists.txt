
set(SOURCES

    "./src/core"
)

link_directories(
    "C:/VulkanSDK/1.4.335.0/Lib"
    
)

add_subdirectory("./third_party/glfw/glfw-3.4")

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME}  PRIVATE

    "C:/VulkanSDK/1.4.335.0/Include" #glm and vulkan.h 

)

target_link_libraries(${PROJECT_NAME} INTERFACE
glfw
vulkan-1.lib

)



