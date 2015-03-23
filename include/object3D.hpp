#ifndef __OBJECT3D_HPP__
#define __OBJECT3D_HPP__

    #include <matrix.hpp>
    #include <glm/gtc/type_ptr.hpp>
    #include <GL/glew.h>
    #include <GL/gl.h>
    #include <GL/glext.h>

    #define NMAX 50
    #define PMAX 50
    #define PI 3.141592653589793238462

    using namespace std;

    class Object3D
    {
        private:
            glm::vec4 color;
            Matrix Mt;

        protected:
            float * vertex;
            float * normal;
            float * text_coord;
            unsigned int *index;
            int nb_triangles;

        public:
            Object3D(glm::vec4 color);

            Matrix get_Mt();
            void set_Mt(Matrix m);

            void apply_translation(float x, float y, float z);
            void apply_translation(glm::vec3 vector);
            void apply_homothety(float x, float y, float z);
            void apply_homothety(glm::vec3 abc);
            void apply_rotation_on_x(float angle);
            void apply_rotation_on_y(float angle);
            void apply_rotation_on_z(float angle);

            void draw();

            virtual GLuint get_VAO() = 0;
            virtual GLuint* get_VBO() = 0;
    };

#endif
