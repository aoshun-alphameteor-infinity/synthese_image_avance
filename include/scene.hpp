#ifndef __SCENE_HPP__
#define __SCENE_HPP__

    #include <tree.hpp>
    #include <object3D.hpp>
    #include <canonical_cube.hpp>
    #include <onagre.hpp>
    #include <castle.hpp>
    #include <shader.hpp>

    class Scene
    {
        private:
            static Shader* s;
            static Tree* onagre_ring(void);
        public:
            static Tree* create_scene(void);
    };
#endif
