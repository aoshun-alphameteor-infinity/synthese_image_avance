#ifndef __CANONICAL_HORN_HPP__
#define __CANONICAL_HORN_HPP__

    #include <object3D.hpp>
    #include <iostream>


    class Horn : public Object3D
    {
        private :
            static std::vector<float> *horn_vertex;
            static std::vector<float> *horn_normal;
            static std::vector<float> * horn_text_coord;
            static std::vector<unsigned int> * horn_index;
            static GLuint horn_vao;
            static GLuint horn_vbo[4];


            void init_canonical_horn(void);
            void init_vao(void);

        public:
            Horn(glm::vec4 col);

            inline GLuint get_VAO()
            {
                return horn_vao;
            }

            inline GLuint* get_VBO()
            {
                GLuint* tmp = new GLuint[4];
                memcpy(tmp, horn_vbo, 4 * sizeof(GLuint));
                return tmp;
            }

            inline static void horn_delete()
            {
                if(horn_vertex != NULL)
                {
                    delete horn_vertex;
                    delete horn_normal;
                    delete horn_text_coord;
                    delete horn_index;
                }
            }
    };

#endif
