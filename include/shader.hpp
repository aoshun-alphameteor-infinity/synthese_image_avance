#ifndef __SHADER_HPP__
#define __SHADER_HPP__

    #include <iostream>
    #include <stdexcept>
    #include <string>
    #include <map>
    #include <cstring>
    #include <cstdlib>
    #include <GL/glew.h>
    #include <GL/gl.h>
    #include <GL/glut.h>
    #include <stb/stb_image.h>
    #include <gl_tools.hpp>

    static const int nb_max_texture = 3;
    extern const std::string shader_name;

    class Shader
    {
        private:
            static std::map<std::string, GLuint> compiled;
            static std::map<std::string, GLuint> charged;

            GLuint program;
            GLuint textures[nb_max_texture];
            int nb_texture;

            int check_link_error(GLuint program);
            GLuint compile_shader(GLenum shaderType, const char * sourceBuffer, int bufferSize);
            GLuint compile_shader_from_file(GLenum shaderType, const char * path);
            int check_compile_error(GLuint shader, const char ** sourceBuffer);

        public:
            Shader(std::string name);
            Shader(const Shader& s);
            GLuint get_id();
            void attach_texture(std::string texture);
            void active_textures();
            void upload_textures();

            GLuint operator[] (int index)
            {
                if(index < 0 || index >= nb_max_texture)
                {
                    throw std::out_of_range("an index must be within 0 and the size of the container\n");
                }
                return textures[index];
            };
    };

#endif
