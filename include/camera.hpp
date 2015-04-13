#ifndef __CAMERA_HPP__
#define __CAMERA_HPP__

    #include <matrix.hpp>
    #include <GL/glew.h>
    #include <GL/glu.h>

    #define DEFAULT_LEFT_RIGHT 0.1*0.577350269
    #define DEFAULT_TOP_BOTTOM 0.1*0.577350269
    #define DEFAULT_NEAR       0.1
    #define DEFAULT_FAR        100.0

    class Camera
    {
        private:
            glm::vec3 position;
            glm::vec3 view_direction;
            glm::vec3 direction_init;
            glm::vec3 top_direction;
            glm::vec3 top_init;
            glm::vec3 orientation;
            Matrix projection;

            void orientation_react();

        public:
            Camera();
            Camera(glm::vec3 pos_init, glm::vec3 dir_init = glm::vec3(0.0, 0.0, -1.0), glm::vec3 top_init = glm::vec3(0.0, 1.0, 0.0), glm::vec3 orient_init = glm::vec3());

            void move_front(float step);
            void move_back(float step);
            void move_left(float step);
            void move_right(float step);
            void move_up(float step);
            void move_down(float step);

            void look_up(float angle);
            void look_down(float angle);
            void look_left(float angle);
            void look_right(float angle);

            glm::vec3 get_position()
            {
                return position;
            };


            Matrix get_projection();

            void set_projection(Matrix new_projection);

            Matrix get_transformation();

            void set_transformation_GL();
    };

#endif
