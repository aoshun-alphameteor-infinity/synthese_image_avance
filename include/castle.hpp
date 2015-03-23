#ifndef __CASTLE_H__
#define __CASTLE_H__

    #include <canonical_tore.hpp>
    #include <canonical_cube.hpp>
    #include <canonical_cylinder.hpp>
    #include <canonical_cone.hpp>
    #include <tree.hpp>
    #include <node.hpp>
    #include <object3D.hpp>
    #include <shader.hpp>

    static glm::vec4 red(0.50, 0.12, 0.12, 1.00);
    static glm::vec4 yellow(0.25, 0.25, 0.12, 1.00);

    class Castle{
        private:
            static Shader* s;
            static Tree* create_tower_top(void);
            static Tree* create_tower(void);
            static Tree* create_wall(void);
            static Tree* create_wall_with_gate(void);
        public:
            static Tree* create_castle(void);
    };

#endif
