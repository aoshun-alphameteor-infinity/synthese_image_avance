#include <tree.hpp>
#include <iostream>

Tree::Tree()
{
    this->Mt = Matrix();
}

Tree::~Tree()
{
	delete &(this->Mt);
}

Matrix Tree::get_Mt()
{
    return this->Mt;
}

Matrix Tree::get_Mn()
{
    return this->Mn;
}

void Tree::apply_translation(float x, float y, float z)
{
    this->Mt *= Matrix::translation(x, y, z);
}

void Tree::apply_translation(glm::vec3 vector)
{
    apply_translation(vector.x, vector.y, vector.z);
}

void Tree::apply_homothety(float x, float y, float z)
{
    this->Mt *= Matrix::homothety(x, y , z);
    this->Mn *= Matrix::homothety(y * z, x * z, x * y);
}

void Tree::apply_homothety(glm::vec3 abc)
{
    apply_homothety(abc.x, abc.y, abc.z);
}

void Tree::apply_rotation_on_x(float angle) 
{
    if(!is_zero(angle))
    { 
        this->Mt *= Matrix::rotation_x(angle);
        this->Mn *= Matrix::rotation_x(angle);
    }
}

void Tree::apply_rotation_on_y(float angle)
{
    if(!is_zero(angle))
    {
        this->Mt *= Matrix::rotation_y(angle);
        this->Mn *= Matrix::rotation_y(angle);
    }
}

void Tree::apply_rotation_on_z(float angle)
{
    if(!is_zero(angle))
    {
        this->Mt *= Matrix::rotation_z(angle);
        this->Mn *= Matrix::rotation_z(angle);
    }
}

void Tree::apply_rotation_on_y_first(float angle)
{
    if(!is_zero(angle))
    { 
        this->Mt = Matrix::rotation_y(angle) * this->Mt;
        this->Mn = Matrix::rotation_y(angle) * this->Mn;
    }
}
