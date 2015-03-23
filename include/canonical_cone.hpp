#ifndef __CANONICAL_CONE_HPP__
#define __CANONICAL_CONE_HPP__

    #include <object3D.hpp>
    #include <cstring>
    
    class Cone : public Object3D
    {
        private:
            static float *cone_vertex;
            static float *cone_normal;
            static float *cone_texcoord;
            static unsigned int *cone_index;
            static GLuint cone_vao;
            static GLuint cone_vbo[4];
            
            void init_canonical_cone(void);
        
        public:
            Cone(glm::vec4 col);
            
            inline GLuint get_VAO()
            {
                return cone_vao;
            }
            
            inline GLuint* get_VBO()
            {
                GLuint* tmp = new GLuint[4];
                memcpy(tmp, cone_vbo, 4 * sizeof(GLuint));
                return tmp;
            }
            
            inline static void cone_delete()
            {
                if(cone_vertex != NULL)
                {
                    delete cone_vertex;
                    delete cone_normal;
                    delete cone_texcoord;
                    delete cone_index;
                }
            }
    };
    
    
#endif
