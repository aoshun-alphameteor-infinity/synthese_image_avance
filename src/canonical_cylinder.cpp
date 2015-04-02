/*modélisation d'un Cylindre*/
#include <canonical_cylinder.hpp>

std::vector<float> *Cylinder::cylinder_vertex = NULL;
std::vector<float> *Cylinder::cylinder_normal = NULL;
std::vector<float> *Cylinder::cylinder_texcoord = NULL;
std::vector<unsigned int> *Cylinder::cylinder_index = NULL;
GLuint Cylinder::cylinder_vao = 0;
GLuint Cylinder::cylinder_vbo[4];

void Cylinder::init_canonical_cylinder(void)
{
    unsigned int i;
    double alpha, cosi, sini;
    cylinder_vertex = new std::vector<float>(3 * (2 * NMAX + 2));
    cylinder_normal = new std::vector<float>(3 * (2 * NMAX + 2));
    cylinder_index = new std::vector<unsigned int>(12 * NMAX);
    cylinder_texcoord = new std::vector<float>(2 * (2 * NMAX + 2));

    alpha = 2 * PI / NMAX;

    memset(cylinder_vertex->data(), 0, 3 * (NMAX + 2) * sizeof(float));
    memset(cylinder_normal->data(), 0, 3 * (NMAX + 2) * sizeof(float));

    (*cylinder_normal)[1] = (*cylinder_vertex)[1] = -1;
    for(i = 1; i < NMAX + 1; i++)
    {
        cosi = cos(i * alpha);
        sini = sin(i * alpha);
        (*cylinder_vertex)[3 * (NMAX + i)] = (*cylinder_vertex)[3 * i] = cosi;
        (*cylinder_vertex)[3 * (NMAX + i) + 2] = (*cylinder_vertex)[3 * i + 2] = sini;
        (*cylinder_vertex)[3 * (NMAX + i) + 1] = 1;
        (*cylinder_vertex)[3 * i + 1] = -1;
        (*cylinder_normal)[3 * (NMAX + i)] = (*cylinder_normal)[3 * i] = cosi;
        (*cylinder_normal)[3 * (NMAX + i) + 2] = (*cylinder_normal)[3 * i + 2] = sini;
    }
    (*cylinder_normal)[3 * (2 * NMAX + 1) + 1] = (*cylinder_vertex)[3 * (2 * NMAX + 1) + 1] = 1;

    for(i = 1; i < NMAX + 1; i++)
    {
        (*cylinder_index)[3 * (i - 1)] = 0;
        (*cylinder_index)[3 * (i - 1) + 1] = i;
        (*cylinder_index)[3 * (i - 1) + 2] = i + 1;

        (*cylinder_index)[3 * ((i - 1) + NMAX)] = i;
        (*cylinder_index)[3 * ((i - 1) + NMAX) + 1] = NMAX + i;
        (*cylinder_index)[3 * ((i - 1) + NMAX) + 2] = i + 1;

        (*cylinder_index)[3 * ((i - 1) + 2 * NMAX)] = i;
        (*cylinder_index)[3 * ((i - 1) + 2 * NMAX) + 1] = NMAX + i - 1;
        (*cylinder_index)[3 * ((i - 1) + 2 * NMAX) + 2] = NMAX + i;

        (*cylinder_index)[3 * ((i - 1) + 3 * NMAX)] = NMAX + i;
        (*cylinder_index)[3 * ((i - 1) + 3 * NMAX) + 1] = 2 * NMAX + 1;
        (*cylinder_index)[3 * ((i - 1) + 3 * NMAX) + 2] = NMAX + i + 1;
    }
    (*cylinder_index)[3 * (NMAX - 1)] = 0;
    (*cylinder_index)[3 * (NMAX - 1) + 1] = NMAX;
    (*cylinder_index)[3 * (NMAX - 1) + 2] = 1;

    (*cylinder_index)[3 * (2 * NMAX - 1)] = NMAX;
    (*cylinder_index)[3 * (2 * NMAX - 1) + 1] = 2 * NMAX;
    (*cylinder_index)[3 * (2 * NMAX - 1) + 2] = 1;

    (*cylinder_index)[3 * (3 * NMAX - 1)] = NMAX;
    (*cylinder_index)[3 * (3 * NMAX - 1) + 1] = 2 * NMAX - 1;
    (*cylinder_index)[3 * (3 * NMAX - 1) + 2] = 2 * NMAX;

    (*cylinder_index)[3 * (4 * NMAX - 1)] = 2 * NMAX;
    (*cylinder_index)[3 * (4 * NMAX - 1) + 1] = 2 * NMAX + 1;
    (*cylinder_index)[3 * (4 * NMAX - 1) + 2] = NMAX + 1;

    double jmp = 1 / NMAX;
    (*cylinder_texcoord)[0] = (*cylinder_texcoord)[1] = 1;
    for(i = 1; i < NMAX + 1; i++)
    {
        (*cylinder_texcoord)[2 * i] = 0;
        (*cylinder_texcoord)[2 * i + 1] = i * jmp;
        (*cylinder_texcoord)[2 * (i + NMAX)] = 1;
        (*cylinder_texcoord)[2 * (i + NMAX) + 1] = i * jmp;
    }
    (*cylinder_texcoord)[4 * NMAX + 2] = (*cylinder_texcoord)[4 * NMAX + 3] = 0;
}

Cylinder::Cylinder(glm::vec4 col) : Object3D(col)
{
    if(cylinder_vertex == NULL)
    {
        init_canonical_cylinder();

        glGenVertexArrays(1, &cylinder_vao);
        glBindVertexArray(cylinder_vao);

        glGenBuffers(4, cylinder_vbo);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cylinder_vbo[0]);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * cylinder_index->size(), cylinder_index->data(), GL_STATIC_DRAW);

        glBindBuffer(GL_ARRAY_BUFFER, cylinder_vbo[1]);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GL_FLOAT)*3, (void*)0);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * cylinder_vertex->size(), cylinder_vertex->data(), GL_STATIC_DRAW);

        glBindBuffer(GL_ARRAY_BUFFER, cylinder_vbo[2]);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GL_FLOAT)*3, (void*)0);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * cylinder_normal->size(), cylinder_normal->data(), GL_STATIC_DRAW);

        glBindBuffer(GL_ARRAY_BUFFER, cylinder_vbo[3]);
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(GL_FLOAT)*2, (void*)0);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * cylinder_texcoord->size(), cylinder_texcoord->data(), GL_STATIC_DRAW);

        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
    this -> nb_triangles = 4 * NMAX;
    vertex = cylinder_vertex;
    normal = cylinder_normal;
    index = cylinder_index;
    text_coord = cylinder_texcoord;
}
