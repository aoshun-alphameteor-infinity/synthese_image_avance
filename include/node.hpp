#ifndef __NODE_HPP__
#define __NODE_HPP__

    #include <tree.hpp>
    #include <leaf.hpp>
    #include <shader.hpp>
    #include <vector>
    #include <iostream>

    class Node : public Tree
    {
        private:
            vector<Tree*> children;

        public:
            Node();
            ~Node();
            vector<Tree*> get_children();
            int add_child(Object3D* O, Shader* shader);
            int add_children(Tree* T);
            void draw(Camera cam);
            void sub_draw(Matrix mt);
            virtual void animation();
    };

#endif
