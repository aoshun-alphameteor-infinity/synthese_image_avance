#ifndef __SCENE_HPP__
#define __SCENE_HPP__

    #include <tree.hpp>
    #include <object3D.hpp>
    #include <canonical_cube.hpp>
    #include <onagre.hpp>
    #include <castle.hpp>
    #include <shader.hpp>
    #include <light.hpp>

    class Scene
    {
        private:
            static const int pointlightCount = 5;
            static const int spotlightCount =  8;
            static Tree* onagre_ring(void);
            static Tree* create_diorama(void);
            static Tree* create_banner(void);
        public:
            static Tree* create_scene(void);
            static void update_lights(Camera cam);
    };
#endif
