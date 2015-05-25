#include <canonical_cone.hpp>

std::vector<float>* Cone::cone_vertex = new std::vector<float>(3 * (NMAX + 2), 0);
std::vector<float>* Cone::cone_normal = new std::vector<float>(3 * (NMAX + 2), 0);
std::vector<float>* Cone::cone_texcoord = new std::vector<float>(2 * (NMAX + 2), 0);
std::vector<unsigned int>* Cone::cone_index = new std::vector<unsigned int>(6 * NMAX, 0u);
bool Cone::is_initialized = false;
GLuint Cone::cone_vao = 0;
GLuint Cone::cone_vbo[4] = {0u, 0u, 0u, 0u};

void Cone::init_canonical_cone (void)
{
    unsigned int i;
    double alpha, cosi, sini;

    alpha = 2 * PI / NMAX;

    (*cone_normal)[1] = -1;
    for(i = 1; i < NMAX + 1; i++)
    {
        cosi = cos(i * alpha);
        sini = sin(i * alpha);
        (*cone_vertex)[3 * i] = cosi;
        (*cone_vertex)[3 * i + 2] = sini;

        (*cone_normal)[3 * i] = cosi;
        (*cone_normal)[3 * i + 2] = sini;
    }
    (*cone_normal)[3 * (NMAX + 1) + 1] = (*cone_vertex)[3 * (NMAX + 1) + 1] = 1;


    for(i = 1; i < NMAX; i++)
    {
        //(*cone_index)[3 * (i - 1)] = 0;
        (*cone_index)[3 * (i - 1) + 1] = i;
        (*cone_index)[3 * (i - 1) + 2] = i + 1;
        (*cone_index)[3 * ((i - 1) + NMAX)] = i;
        (*cone_index)[3 * ((i - 1) + NMAX) + 1] = NMAX + 1;
        (*cone_index)[3 * ((i - 1) + NMAX) + 2] = i + 1;
    }
    (*cone_index)[3 * (NMAX - 1)] = 0;
    (*cone_index)[3 * (NMAX - 1) + 1] = NMAX;
    (*cone_index)[3 * (NMAX - 1) + 2] = 1;
    (*cone_index)[3 * (2 * NMAX - 1)] = NMAX;
    (*cone_index)[3 * (2 * NMAX - 1) + 1] = NMAX + 1;
    (*cone_index)[3 * (2 * NMAX - 1) + 2] = 1;

    double jmp = 1 / NMAX;
    (*cone_texcoord)[0] = (*cone_texcoord)[1] = 0.5;
    for(i = 1; i < NMAX + 1; i++)
    {
        (*cone_texcoord)[2 * i] = cos(i * alpha) / 2 + 0.5;
        (*cone_texcoord)[2 * i + 1] = sin(i * alpha) / 2 + 0.5;
    }
    (*cone_texcoord)[2 * NMAX + 2] = (*cone_texcoord)[2 * NMAX + 3] = 0.5;
}

Cone::Cone(glm::vec4 col) : Object3D(col)
{
    if(!is_initialized)
    {
        init_canonical_cone();

        glGenVertexArrays(1, &cone_vao);
        glBindVertexArray(cone_vao);

        glGenBuffers(4, cone_vbo);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cone_vbo[0]);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * cone_index->size(), cone_index->data(), GL_STATIC_DRAW);

        glBindBuffer(GL_ARRAY_BUFFER, cone_vbo[1]);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GL_FLOAT)*3, (void*)0);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * cone_vertex->size(), cone_vertex->data(), GL_STATIC_DRAW);

        glBindBuffer(GL_ARRAY_BUFFER, cone_vbo[2]);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GL_FLOAT)*3, (void*)0);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * cone_normal->size(), cone_normal->data(), GL_STATIC_DRAW);

        glBindBuffer(GL_ARRAY_BUFFER, cone_vbo[3]);
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(GL_FLOAT)*2, (void*)0);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * cone_texcoord->size(), cone_texcoord->data(), GL_STATIC_DRAW);

        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        is_initialized = true;
    }
    this -> nb_triangles = 2 * NMAX;
    vertex = cone_vertex;
    normal = cone_normal;
    index = cone_index;
    text_coord = cone_texcoord;
}
