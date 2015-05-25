#ifndef __INTERFACE_HPP__
#define __INTERFACE_HPP__

    #include <scene.hpp>
    #include <tree.hpp>
    #include <camera.hpp>
    #include <timer.hpp>

    class Interface
    {
        private:
            int width;
            int height;
            unsigned int display_mode;
            Camera camera;
            Timer timer;

            void canonical_delete()
            {
                Cone::cone_delete();
                Cube::cube_delete();
                Cylinder::cylinder_delete();
                Horn::horn_delete();
                Sphere::sphere_delete();
                Tore::tore_delete();
            };

        public:
            Interface(int width, int height);
            ~Interface();
            void keyboard_function(unsigned char c, int x, int y);
            void keyboard_special_function(int c, int x, int y);
            void mouse_function(int button, int state, int x, int y);
            void idle_function();
            void reshape(int width, int height);
            void change_animation();
            void init(void);
            void reset(void);
            void draw(void);
            int get_width(){return width;};
            int get_height(){return height;};
    };

#endif
