#pragma once
#include<glm/glm.hpp>

class Camera{

    public:

        Camera();
        ~Camera();

        Camera(const Camera&)=delete;
        Camera& operator =(const Camera&)=delete;

    private:
        glm::vec3 m_position{1.2f,1.3f,3.4f};
        glm::vec3 m_target{0.0f,0.0f,0.0f};
        glm::vec3 m_up{0.0f,1.0f,0.0f};


};