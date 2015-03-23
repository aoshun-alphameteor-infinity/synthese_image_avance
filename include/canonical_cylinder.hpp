#ifndef __CANONICAL_CYLINDER_HPP__
#define __CANONICAL_CYLINDER_HPP__

    #include <object3D.hpp>
    #include <cstring>

    class Cylinder : public Object3D
    {
        private:
            static float *cylinder_vertex;
            static float *cylinder_normal;
            static float *cylinder_texcoord;
            static unsigned int *cylinder_index;
            static GLuint cylinder_vao;
            static GLuint cylinder_vbo[4];
            
            void init_canonical_cylinder(void);
            
        public:
            Cylinder(glm::vec4 col);
            
            inline GLuint get_VAO()
            {
                return cylinder_vao;
            }
            
            inline GLuint* get_VBO()
            {
                GLuint* tmp = new GLuint[4];
                memcpy(tmp, cylinder_vbo, 4 * sizeof(GLuint));
                return tmp;
            }
            
            inline static void cylinder_delete()
            {
                if(cylinder_vertex != NULL)
                {
                    delete cylinder_vertex;
                    delete cylinder_normal;
                    delete cylinder_texcoord;
                    delete cylinder_index;
                }
            }
    };

    
#endif
