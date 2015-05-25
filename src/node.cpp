#include <node.hpp>

Node::Node()
{
    this->children = vector<Tree*>();
}

Node::~Node()
{
    unsigned int i;
    for(i = 0; i < this->children.size(); i++)
    {
        delete this->children[i];
    }
    delete &(this->children);
}

vector<Tree*> Node::get_children()
{
    return this->children;
}

int Node::add_child(Object3D* O, Shader* shader)
{
    Tree* node = new Leaf(O, shader);
    return add_children(node);
}

int Node::add_children(Tree* T)
{
    if( T != NULL)
    {
        this->children.push_back(T);
        return 0;
    }
    else
    {
        return -1;
    }
}

void Node::draw(Camera cam)
{
    Matrix mt = cam.get_projection() * cam.get_transformation();
    Matrix mn;
    this->sub_draw(mt, mn, cam.get_position());
}

void Node::sub_draw(Matrix mt, Matrix mn, glm::vec3 cam_position)
{
    unsigned int i;
    Matrix mat_d, mat_n;

    mat_d = mt * this->Mt;
    mat_n = mn * this->Mn;

    for(i = 0; i < this->children.size(); i++)
        this->children[i]->sub_draw(mat_d, mat_n, cam_position);
}

void Node::animation(int elapsed_time)
{
    unsigned int i;
    for(i = 0; i < this->children.size(); i++)
        this->children[i]->animation(elapsed_time);
}
