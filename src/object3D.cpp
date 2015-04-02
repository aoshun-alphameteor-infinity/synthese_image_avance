#include <object3D.hpp>
#include <iostream>

Object3D::Object3D(glm::vec4 col)
{
    this->color = col;
}

void Object3D::apply_translation(float x, float y, float z)
{
    this->Mt *= Matrix::translation(x, y, z);
}

void Object3D::apply_translation(glm::vec3 vector)
{
    apply_translation(vector.x, vector.y, vector.z);
}

void Object3D::apply_homothety(float x, float y, float z)
{
    this->Mt *= Matrix::homothety(x, y, z);
    //this->Mn *= Matrix::homothety(y * z, x * z, x * y);
}

void Object3D::apply_homothety(glm::vec3 abc)
{
    apply_homothety(abc.x, abc.y, abc.z);
}

void Object3D::apply_rotation_on_x(float angle)
{

    if((-1.E-8 > angle) && (angle > 1.E-8))
    {
        this->Mt *= Matrix::rotation_x(angle);
    }
}

void Object3D::apply_rotation_on_y(float angle)
{
    if((-1.E-8 > angle) && (angle > 1.E-8))
    {
        this->Mt *= Matrix::rotation_y(angle);
    }
}

void Object3D::apply_rotation_on_z(float angle)
{
    if((-1.E-8 > angle) && (angle > 1.E-8))
    {
        this->Mt *= Matrix::rotation_z(angle);
    }
}

Matrix Object3D::get_Mt(){
    return this->Mt;
}

void Object3D::set_Mt(Matrix m){
    this->Mt = m;
}

void Object3D::draw()
{
    glVertexAttrib4fv(3, glm::value_ptr(color));

    glBindVertexArray(this->get_VAO());
    glDrawElements(GL_TRIANGLES, nb_triangles * 3, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}
