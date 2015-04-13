#ifndef __LIGHT_HPP__
#define __LIGHT_HPP__


    #define GLM_FORCE_RADIANS
    #include <glm/glm.hpp>
    #include <glm/vec3.hpp>

    typedef struct _spotlight{
        glm::vec3 position;
        float angle;
        glm::vec3 direction;
        float penumbraAngle;
        glm::vec3 color;
        float intensity;
    } Spotlight;

    typedef struct _pointlight{
        glm::vec3 position;
        glm::vec3 color;
        float intensity;
    } Pointlight;

#endif
