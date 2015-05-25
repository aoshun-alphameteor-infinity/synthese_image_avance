#ifndef __ONAGRE_HPP__
#define __ONAGRE_HPP__

    #include <iostream>
    #include <canonical_tore.hpp>
    #include <canonical_cube.hpp>
    #include <canonical_cylinder.hpp>
    #include <canonical_horn.hpp>
    #include <canonical_sphere.hpp>
    #include <tree.hpp>
    #include <node.hpp>
    #include <anim_node.hpp>
    #include <object3D.hpp>

    class Onagre {
        private :
            static Tree* create_onagre_main_body(glm::vec4 color);
            static Tree* create_onagre_spoon(glm::vec4 color);
            static Tree* create_onagre_wheel(glm::vec4 color);
        public :
            static Tree* create_onagre(glm::vec4 color);
    };


#endif
