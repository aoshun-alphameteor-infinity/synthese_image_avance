#ifndef __GL_TOOLS_HPP__
#define __GL_TOOLS_HPP__

    inline void checkGL(int line, const char *filename) {
        int err = glGetError();
        if(err != GL_NO_ERROR) {
            std::cerr << "ERROR GL : erreur dans le fichier " << filename << " à la ligne " ;
            std::cerr << line << " : " << gluErrorString(err) << std::endl;
            exit(0);
        }
    }

    #define CHECK_GL checkGL(__LINE__, __FILE__)

#endif
