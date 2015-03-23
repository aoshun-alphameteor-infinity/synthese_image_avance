#include <leaf.hpp>

Leaf::Leaf(Object3D* O, Shader* s)
{
    this -> obj = O;
    this -> shader = s;
}

Leaf::~Leaf()
{
    delete this->obj;
}

void Leaf::draw(Camera cam)
{
    Matrix mt = cam.get_transformation();
    //Matrix Mn = Matrix();
    this->sub_draw(mt);
}

void Leaf::sub_draw(Matrix mt)
{
    int i;
    Matrix transfo, mat_d;

    mat_d = mt * this->Mt;
    if(this->obj != NULL)
    {
        transfo = mat_d * this->obj->get_Mt();

        this->shader->upload_textures();

        this->shader->active_textures();

        float* t = (float*)transfo;
        /* Upload Uniform data */
        glUniformMatrix4fv(glGetUniformLocation(this -> shader -> get_id(), "modelviewProjection"), 1, GL_FALSE, t);

        this->obj->draw();
    }
}
