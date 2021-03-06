#include <canonical_tore.hpp>

std::vector<float> *Tore::tore_vertex = NULL;
std::vector<float> *Tore::tore_normal = NULL;
std::vector<float> *Tore::tore_texcoord = NULL;
std::vector<unsigned int> *Tore::tore_index = NULL;
GLuint Tore::tore_vao = 0;
GLuint Tore::tore_vbo[4];

void Tore::init_canonical_tore(void)
{
    int i, j, id;
    float u, v, cosu, cosv, sinu, sinv, ti, tj;
    tore_vertex = new std::vector<float>(NMAX * PMAX * 3);
    tore_normal = new std::vector<float>(NMAX * PMAX * 3);
    tore_texcoord = new std::vector<float>(NMAX * PMAX * 2);
    tore_index = new std::vector<unsigned int>(NMAX * PMAX * 6);

    u = 2*PI/NMAX;
    v = 2*PI/PMAX;
    ti = 1. / (NMAX - 1.);
    tj = 1. / (PMAX - 1.);
    for(i = 0; i < NMAX; i++)
    {
        cosu = cos(i * u);
        sinu = sin(i * u);
        for(j = 0; j < PMAX; j++)
        {
            cosv = cos(j * v);
            sinv = sin(j * v);
            (*tore_vertex)[(i * PMAX + j) * 3 + 0] = (2 + cosu) * cosv;
            (*tore_vertex)[(i * PMAX + j) * 3 + 1] = sinu;
            (*tore_vertex)[(i * PMAX + j) * 3 + 2] = (2 + cosu) * sinv;

            (*tore_normal)[(i * PMAX + j) * 3 + 0] = cosu * cosv;
            (*tore_normal)[(i * PMAX + j) * 3 + 1] = sinu;
            (*tore_normal)[(i * PMAX + j) * 3 + 2] = cosu * sinv;

            (*tore_texcoord)[(i * PMAX + j) * 2] = j * tj;
            (*tore_texcoord)[(i * PMAX + j) * 2 + 1] = i * ti + 0.5;

        }
    }
    id = 0;
    unsigned int q = 0;
    for(unsigned int p = 1; p < NMAX; p++)
    {
        for(q = 0; q < PMAX - 1; q++)
        {
            (*tore_index)[id] = (p - 1) * PMAX + q;
            (*tore_index)[id + 1] = p * PMAX + q + 1;
            (*tore_index)[id + 2] = p * PMAX + q;

            (*tore_index)[id + 3] = (p - 1) * PMAX + q;
            (*tore_index)[id + 4] = (p - 1) * PMAX + q + 1;
            (*tore_index)[id + 5] = p * PMAX + q + 1;

            id += 6;
        }
        (*tore_index)[id] = (p - 1) * PMAX + q;
        (*tore_index)[id + 1] = p * PMAX;
        (*tore_index)[id + 2] = p * PMAX + q;

        (*tore_index)[id + 3] = (p - 1) * PMAX + q;
        (*tore_index)[id + 4] = (p - 1) * PMAX;
        (*tore_index)[id + 5] = p * PMAX;

        id += 6;
    }
    for(q = 0; q < PMAX - 1; q++)
    {
        (*tore_index)[id] = (NMAX - 1) * PMAX + q;
        (*tore_index)[id + 1] = q + 1;
        (*tore_index)[id + 2] = q;

        (*tore_index)[id + 3] = (NMAX - 1) * PMAX + q;
        (*tore_index)[id + 4] = (NMAX - 1) * PMAX + q + 1;
        (*tore_index)[id + 5] = q + 1;

        id += 6;
    }
    (*tore_index)[id] = (NMAX - 1) * PMAX + q;
    (*tore_index)[id + 1] = 0;
    (*tore_index)[id + 2] = q;

    (*tore_index)[id + 3] = (NMAX - 1) * PMAX + q;
    (*tore_index)[id + 4] = (NMAX - 1) * PMAX;
    (*tore_index)[id + 5] = 0;

}

void Tore::init_vao(void)
{
    // Create a Vertex Array Object
    glGenVertexArrays(1, &tore_vao);
    // Create a VBO for each array
    glGenBuffers(4, tore_vbo);
    // Bind the VAO
    glBindVertexArray(tore_vao);

    // Bind indices and upload data
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, tore_vbo[0]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * tore_index->size(), tore_index->data(), GL_STATIC_DRAW);

    // Bind vertices and upload data
    glBindBuffer(GL_ARRAY_BUFFER, tore_vbo[1]);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GL_FLOAT) * 3, (void*)0);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * tore_vertex->size(), tore_vertex->data(), GL_STATIC_DRAW);

    // Bind normals and upload data
    glBindBuffer(GL_ARRAY_BUFFER, tore_vbo[2]);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GL_FLOAT) * 3, (void*)0);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * tore_normal->size(), tore_normal->data(), GL_STATIC_DRAW);

    // Bind uv coords and upload data
    glBindBuffer(GL_ARRAY_BUFFER, tore_vbo[3]);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(GL_FLOAT) * 2, (void*)0);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * tore_texcoord->size(), tore_texcoord->data(), GL_STATIC_DRAW);

    // Unbind everything
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

Tore::Tore(glm::vec4 col) : Object3D(col)
{
    if(tore_vertex == NULL) {
        init_canonical_tore();
        init_vao();
    }
    vertex = tore_vertex;
    normal = tore_normal;
    index = tore_index;
    text_coord = tore_texcoord;
    nb_triangles = NMAX * PMAX * 6;
}
