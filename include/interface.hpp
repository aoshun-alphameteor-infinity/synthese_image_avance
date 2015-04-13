#ifndef __INTERFACE_HPP__
#define __INTERFACE_HPP__

    #include <scene.hpp>
    #include <tree.hpp>
    #include <castle.hpp>
    #include <onagre.hpp>
    #include <camera.hpp>
    #include <light.hpp>

    class Interface
    {
        private:
            int width;
            int height;
            unsigned int display_mode;
            Camera camera;

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
