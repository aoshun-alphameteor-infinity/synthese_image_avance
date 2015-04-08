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
    Matrix mn = Matrix();
    this->sub_draw(mt, mn);
}

void Leaf::sub_draw(Matrix mt, Matrix mn)
{
    int i;
    Matrix transfo, mat_d, mat_n;

    mat_d = mt * this->Mt;
    if(this->obj != NULL)
    {
        transfo = mat_d * this->obj->get_Mt();
        mat_n = mn * this->Mn * this->obj->get_Mn();

        glUseProgram(this -> shader -> get_id());

        this->shader->upload_textures();

        this->shader->active_textures();

        float* t = (float*)transfo;
        /* Upload Uniform data */
        glUniformMatrix4fv(glGetUniformLocation(this -> shader -> get_id(), "modelviewProjection"), 1, GL_TRUE, t);
        glUniformMatrix4fv(glGetUniformLocation(this -> shader -> get_id(), "normalTransformation"), 1, GL_TRUE, (float*)mat_n);

        this->obj->draw();

        glUseProgram(0);
    }
}
