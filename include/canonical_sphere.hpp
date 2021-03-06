#ifndef __CANONICAL_SPHERE_HPP__
#define __CANONICAL_SPHERE_HPP__

    #include <object3D.hpp>
    #include <iostream>
    #include <cstdio>
    #include <cstring>

    class Sphere : public Object3D
    {
        private:
            static std::vector<float> *sphere_vertex;
            static std::vector<float> *sphere_normal;
            static std::vector<float> *sphere_text_coord;
            static std::vector<unsigned int> *sphere_index;
            static GLuint sphere_vao;
            static GLuint sphere_vbo[4];

            void init_canonical_sphere(void);
            void init_vao(void);

        public:
            Sphere(glm::vec4 col);

            inline GLuint get_VAO()
            {
                return sphere_vao;
            }

            inline GLuint* get_VBO()
            {
                GLuint* tmp = new GLuint[4];
                memcpy(tmp, sphere_vbo, 4 * sizeof(GLuint));
                return tmp;
            }

            inline static void sphere_delete()
            {
                if(sphere_vertex != NULL)
                {
                    delete sphere_vertex;
                    delete sphere_normal;
                    delete sphere_text_coord;
                    delete sphere_index;
                }
            }
    };

#endif
