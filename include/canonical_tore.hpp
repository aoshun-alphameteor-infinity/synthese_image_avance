#ifndef __CANONICAL_TORE_HPP__
#define __CANONICAL_TORE_HPP__

    #include <object3D.hpp>
    #include <iostream>

    
    class Tore : public Object3D
    {
        private:
            static float *tore_vertex;
            static float *tore_normal;
            static float *tore_texcoord;
            static unsigned int *tore_index;
            static GLuint tore_vao;
            static GLuint tore_vbo[4];

            void init_canonical_tore(void);
            void init_vao(void);
        
        public:
            Tore(glm::vec4 col);

            inline GLuint get_VAO()
            {
                return tore_vao;
            }
            
            inline GLuint* get_VBO()
            {
                GLuint* tmp = new GLuint[4];
                memcpy(tmp, tore_vbo, 4 * sizeof(GLuint));
                return tmp;
            }
            
            inline static void tore_delete()
            {
                if(tore_vertex != NULL)
                {
                    delete tore_vertex;
                    delete tore_normal;
                    delete tore_texcoord;
                    delete tore_index;
                }
            }
    };
    
#endif
