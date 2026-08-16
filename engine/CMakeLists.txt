
set(SOURCES
    "./main.cpp"
    "./src/core/app.cpp"
    "./src/window/window.cpp"
    "./src/scene/camera.cpp"
    "./src/instance/vulkanInstance.cpp"
    "./src/device/windowsurface.cpp"
    "./src/swapchain/swapchainSupport.cpp"
    "./src/device/vulkanPhysicalDevice.cpp"
    "./src/device/logicalDevice.cpp"
    "./src/swapchain/swapchain.cpp"
    "./src/swapchain/swapchainImageViews.cpp"
    "./src/pipeline/DepthResources.cpp"
    "./src/pipeline/RenderPass.cpp"
    "./src/pipeline/Framebuffers.cpp"
    "./src/commands/CommandPool.cpp"
)

link_directories(
    "C:/VulkanSDK/1.4.335.0/Lib"
    
)

add_subdirectory("./third_party/glfw/glfw-3.4")

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME}  PRIVATE

    "C:/VulkanSDK/1.4.335.0/Include" #glm and vulkan.h 
    "./third_party/glfw/glfw-3.4/include"
    #later tiny_gltf.h and stb_image.h header only
    "./src/core/"
    "./src/window"
    "./src/scene"
    "./src/model"
    "./src/instance"
    "./src/device"
    "./src/swapchain"
    "./src/device"
    "./src/pipeline"
    "./src/commands"
    
    
)

target_link_libraries(${PROJECT_NAME} INTERFACE
glfw
vulkan-1.lib

)

