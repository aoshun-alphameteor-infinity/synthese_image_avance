#ifndef __LEAF_HP__
#define __LEAF_HP__

    #include <shader.hpp>
    #include <tree.hpp>
    #include <object3D.hpp>

    class Anim_Node;

    class Leaf : public Tree
    {
        friend class Anim_Node;

        private:
            Object3D *obj;
            Shader *shader;

        protected:

        public:
            Leaf(Object3D* O, Shader* shader);
            ~Leaf();
            virtual void animation(){};
            virtual void sub_draw(Matrix mt, Matrix mn);
            virtual void draw(Camera cam);
    };

#endif
