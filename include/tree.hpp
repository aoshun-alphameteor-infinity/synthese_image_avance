#ifndef __TREE_HPP__
#define __TREE_HPP__

    #include <matrix.hpp>
    #define GLM_FORCE_RADIANS
    #include <glm/glm.hpp>
    #include <glm/vec3.hpp>
    #include <camera.hpp>


    class Tree
    {
        protected:
            Matrix Mt;
          //Matrix Mn;

        public:
            Tree();
            ~Tree();
            Matrix get_Mt();
            void apply_translation(float x, float y, float z);
            void apply_translation(glm::vec3 vector);
            void apply_homothety(float x, float y, float z);
            void apply_homothety(glm::vec3 abc);
            void apply_rotation_on_x(float angle);
            void apply_rotation_on_y(float angle);
            void apply_rotation_on_z(float angle);
            void apply_rotation_on_y_first(float angle);
            virtual void animation() = 0;
            virtual void draw(Camera cam) = 0;
            virtual void sub_draw(Matrix mt) = 0;
    };

#endif
