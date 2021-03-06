#ifndef __CANONICAL_CUBE_HPP__
#define __CANONICAL_CUBE_HPP__

    #include <object3D.hpp>
    #include <iostream>
    #include <cstring>

    class Cube : public Object3D
    {
        private:
            static std::vector<float> *cube_vertex;
            static std::vector<float> *cube_normal;
            static std::vector<float> * cube_text_coord;
            static std::vector<unsigned int> * cube_index;
            static GLuint cube_vao;
            static GLuint cube_vbo[4];

            void init_canonical_cube(void);
            void init_vao(void);

        public:
            Cube(glm::vec4 color);

            inline GLuint get_VAO()
            {
                return cube_vao;
            }

            inline GLuint* get_VBO()
            {
                GLuint* tmp = new GLuint[4];
                memcpy(tmp, cube_vbo, 4 * sizeof(GLuint));
                return tmp;
            }

            inline static void cube_delete()
            {
                if(cube_vertex != NULL)
                {
                    delete cube_vertex;
                    delete cube_normal;
                    delete cube_text_coord;
                    delete cube_index;
                }
            }
    };


#endif
