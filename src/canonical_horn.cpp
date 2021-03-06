#include <canonical_horn.hpp>

std::vector<float> *Horn::horn_vertex = NULL;
std::vector<float> *Horn::horn_normal = NULL;
std::vector<float> * Horn::horn_text_coord = NULL;
std::vector<unsigned int> * Horn::horn_index = NULL;
GLuint Horn::horn_vao = 0;
GLuint Horn::horn_vbo[4];

void Horn::init_canonical_horn (void)
{
    int i, j, id;
    float alpha, beta, h, r, ipmax, inmax;
    unsigned int u, v;
    horn_vertex = new std::vector<float>((NMAX * PMAX + 2) * 3);
    horn_normal = new std::vector<float>((NMAX * PMAX + 2) * 3);
    horn_text_coord = new std::vector<float>((NMAX * PMAX  + 2) * 3);
    horn_index = new std::vector<unsigned int>(NMAX * PMAX * 6);

    alpha = 2. * PI / NMAX;
    ipmax = 1. / PMAX;
    inmax = 1. / NMAX;
    for(i = 0; i < PMAX; i++)
    {
        h = -1. + 2. * i * ipmax;
        r = (1. - h) / 2.;
        for(j = 0; j < NMAX; j++)
        {
            (*horn_vertex)[(i * NMAX + j) * 3    ] = r * cosf(j * alpha);
            (*horn_vertex)[(i * NMAX + j) * 3 + 1] = h + sinf((1. + h) * PI / 3.);
            (*horn_vertex)[(i * NMAX + j) * 3 + 2] = r * sinf(j * alpha) + cosf((1. + h) * PI / 3.);

            (*horn_normal)[(i * NMAX + j) * 3    ] = cosf(j * alpha);
            (*horn_normal)[(i * NMAX + j) * 3 + 1] = 1.;
            (*horn_normal)[(i * NMAX + j) * 3 + 2] = sinf(j * alpha);

            (*horn_text_coord)[(i * NMAX + j) * 2    ] = i * ipmax;
            (*horn_text_coord)[(i * NMAX + j) * 2 + 1] = j * inmax;
        }
    }
    (*horn_vertex)[(PMAX * NMAX) * 3 + 0] = 0.;
    (*horn_vertex)[(PMAX * NMAX) * 3 + 1] = -1.;
    (*horn_vertex)[(PMAX * NMAX) * 3 + 2] = 1.;

    (*horn_normal)[(PMAX * NMAX) * 3 + 0] = 0.;
    (*horn_normal)[(PMAX * NMAX) * 3 + 1] = -1.;
    (*horn_normal)[(PMAX * NMAX) * 3 + 2] = 0.;

    (*horn_text_coord)[(PMAX * NMAX) * 2    ] = 1.;
    (*horn_text_coord)[(PMAX * NMAX) * 2 + 1] = 1.;

    (*horn_vertex)[(PMAX * NMAX + 1) * 3 + 0] = 0.;
    (*horn_vertex)[(PMAX * NMAX + 1) * 3 + 1] = 1. + sinf(2. * PI / 3.);
    (*horn_vertex)[(PMAX * NMAX + 1) * 3 + 2] = cosf(2. * PI / 3.);

    (*horn_normal)[(PMAX * NMAX + 1) * 3 + 0] = 0.;
    (*horn_normal)[(PMAX * NMAX + 1) * 3 + 1] = 1. + sinf(2. * PI / 3.);
    (*horn_normal)[(PMAX * NMAX + 1) * 3 + 2] = cosf(2. * PI / 3.);

    (*horn_text_coord)[(PMAX * NMAX + 1) * 2    ] = 1.;
    (*horn_text_coord)[(PMAX * NMAX + 1) * 2 + 1] = 1.;

    id = 0;
    for(u = 1; u < PMAX; u++)
    {
        for(v = 0; v < NMAX - 1; v++)
        {
            (*horn_index)[id] = (u - 1) * NMAX + v;
            (*horn_index)[id + 1] = u * NMAX + v + 1;
            (*horn_index)[id + 2] = u * NMAX + v;

            (*horn_index)[id + 3] = (u - 1) * NMAX + v;
            (*horn_index)[id + 4] = (u - 1) * NMAX + v + 1;
            (*horn_index)[id + 5] = u * PMAX + v + 1;

            id += 6;
        }
        (*horn_index)[id] = u * NMAX - 1;
        (*horn_index)[id + 1] = u * NMAX;
        (*horn_index)[id + 2] = (u + 1) * NMAX - 1;

        (*horn_index)[id + 3] = u * NMAX - 1;
        (*horn_index)[id + 4] = (u - 1) * NMAX;
        (*horn_index)[id + 5] = u * NMAX;

        id += 6;
    }
    for(v = 0; v < NMAX - 1; v++)
    {
        (*horn_index)[id] = v;
        (*horn_index)[id + 1] = v + 1;
        (*horn_index)[id + 2] = NMAX * PMAX;
        id += 3;

        (*horn_index)[id] = (NMAX - 1) * PMAX + v + 1;
        (*horn_index)[id + 1] = (NMAX - 1) * PMAX + v;
        (*horn_index)[id + 2] = NMAX * PMAX + 1;
        id += 3;
    }
    (*horn_index)[id] = NMAX - 1;
    (*horn_index)[id + 1] = 0;
    (*horn_index)[id + 2] = NMAX * PMAX;
    id += 3;

    (*horn_index)[id] = (NMAX - 1) * PMAX;
    (*horn_index)[id + 1] = NMAX * PMAX - 1;
    (*horn_index)[id + 2] = NMAX * PMAX;
}

void Horn::init_vao(void)
{
    // Create a Vertex Array Object
    glGenVertexArrays(1, &horn_vao);
    // Create a VBO for each array
    glGenBuffers(4, horn_vbo);
    // Bind the VAO
    glBindVertexArray(horn_vao);

    // Bind indices and upload data
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, horn_vbo[0]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * horn_index->size(), horn_index->data(), GL_STATIC_DRAW);

    // Bind vertices and upload data
    glBindBuffer(GL_ARRAY_BUFFER, horn_vbo[1]);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GL_FLOAT)*3, (void*)0);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * horn_vertex->size(), horn_vertex->data(), GL_STATIC_DRAW);

    // Bind normals and upload data
    glBindBuffer(GL_ARRAY_BUFFER, horn_vbo[2]);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GL_FLOAT)*3, (void*)0);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * horn_normal->size(), horn_normal->data(), GL_STATIC_DRAW);

    // Bind uv coords and upload data
    glBindBuffer(GL_ARRAY_BUFFER, horn_vbo[3]);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(GL_FLOAT)*2, (void*)0);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * horn_text_coord->size(), horn_text_coord->data(), GL_STATIC_DRAW);

    // Unbind everything
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

Horn::Horn(glm::vec4 col) : Object3D(col)
{
    if(horn_vertex == NULL)
    {
        init_canonical_horn();
        init_vao();
    }
    vertex = horn_vertex;
    normal = horn_normal;
    index = horn_index;
    text_coord = horn_text_coord;
    nb_triangles = NMAX * PMAX * 6;
}
