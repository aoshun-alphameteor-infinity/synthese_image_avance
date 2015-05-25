#include <canonical_cube.hpp>

std::vector<float> *Cube::cube_vertex = NULL;
std::vector<float> *Cube::cube_normal = NULL;
std::vector<float> *Cube::cube_text_coord = NULL;
std::vector<unsigned int> *Cube::cube_index = NULL;
GLuint Cube::cube_vao = 0;
GLuint Cube::cube_vbo[4];

void Cube::init_canonical_cube(void)
{
    float coord[3 * 24] = {
        // Face front (z = 1) (A,B,C,D)
        -1.0f,-1.0f,1.0f,         // A
        1.0f,-1.0f,1.0f,          // B
        1.0f,1.0f,1.0f,           // C
        -1.0f,1.0f,1.0f,          // D
        // Face back (z = -1) (E,F,G,H)
        -1.0f,-1.0f,-1.0f,        // E
        -1.0f,1.0f,-1.0f,         // H
        1.0f,1.0f,-1.0f,          // G
        1.0f,-1.0f,-1.0f,         // F
        // Face left (x = -1) (E,A,D,H)
        -1.0f,-1.0f,-1.0f,        // E
        -1.0f,-1.0f,1.0f,         // A
        -1.0f,1.0f,1.0f,          // D
        -1.0f,1.0f,-1.0f,         // H
        // Face right (x = +1) (B,F,G,C)
        1.0f,-1.0f,1.0f,          // B
        1.0f,-1.0f,-1.0f,         // F
        1.0f,1.0f,-1.0f,            // G
        1.0f,1.0f,1.0f,         // C
        // Face top (y = +1) (D,C,G,H)
        -1.0f,1.0f,1.0f,          // D
        1.0f,1.0f,1.0f,           // C
        1.0f,1.0f,-1.0f,          // G
        -1.0f,1.0f,-1.0f,         // H
        // Face down (y = -1) (A,B,F,E)
        -1.0f,-1.0f,1.0f,         // A
        -1.0f,-1.0f,-1.0f,        // E
        1.0f,-1.0f,-1.0f,         // F
        1.0f,-1.0f,1.0f           // B
    };
    float normals[3*24] = {
        // Face front (z = 1) (A,B,C,D)
        0.0f,0.0f,1.0f,     0.0f,0.0f,1.0f,     0.0f,0.0f,1.0f,     0.0f,0.0f,1.0f,
        // Face back (z = -1) (E,H,G,F)
        0.0f,0.0f,-1.0f,    0.0f,0.0f,-1.0f,    0.0f,0.0f,-1.0f,    0.0f,0.0f,-1.0f,
        // Face left (x = -1) (E,A,D,H)
        -1.0,0.0,0.0,       -1.0,0.0,0.0,       -1.0,0.0,0.0,       -1.0,0.0,0.0,
        // Face right (x = +1) (B,F,G,C)
        1.0,0.0,0.0,        1.0,0.0,0.0,        1.0,0.0,0.0,        1.0,0.0,0.0,
        // Face top (y = +1) (D,C,G,H)
        0.0,1.0,0.0,        0.0,1.0,0.0,        0.0,1.0,0.0,        0.0,1.0,0.0,
        // Face down (y = -1) (A,B,F,E)
        0.0,-1.0,0.0,       0.0,-1.0,0.0,       0.0,-1.0,0.0,       0.0,-1.0,0.0
    };
    float text_coord[24 * 2] = {
        0, 1,   1, 1,   1, 0,   0, 0,
        1, 1,   1, 0,   0, 0,   0, 1,
        0, 1,   1, 1,   1, 0,   0, 0,
        0, 1,   1, 1,   1, 0,   0, 0,
        0, 1,   1, 1,   1, 0,   0, 0,
        0, 1,   1, 1,   1, 0,   0, 0,
    };
    unsigned int index[ 12 * 3 ] = {
        // Face front (z = 1) (A,B,C,D)
        0,1,2,      0,2,3,
        // Face back (z = -1) (E,F,G,H)
        4,5,6,      4,6,7,
        // Face left (x = -1) (E,A,D,H)
        8,9,10,     8,10,11,
        // Face right (x = +1) (B,F,G,C)
        12,13,14,       12,14,15,
        // Face top (y = +1) (D,C,G,H)
        16,17,18,       16,18,19,
        // Face down (y = -1) (A,E,F,B)
        20,21,22,       20,22,23
    };
    cube_vertex = new std::vector<float>(24 * 3);
    cube_normal = new std::vector<float>(24 * 3);
    cube_text_coord = new std::vector<float>(24 * 2);
    cube_index = new std::vector<unsigned int>(12 * 3);

    memcpy(cube_vertex->data(), coord, sizeof(float) * cube_vertex->size());
    memcpy(cube_normal->data(), normals, sizeof(float) * cube_normal->size());
    memcpy(cube_text_coord->data(), text_coord, sizeof(float) * cube_text_coord->size());
    memcpy(cube_index->data(), index, sizeof(unsigned int) * cube_index->size());
}

void Cube::init_vao(void)
{
    // Create a Vertex Array Object
    glGenVertexArrays(1, &cube_vao);
    // Create a VBO for each array
    glGenBuffers(4, cube_vbo);
    // Bind the VAO
    glBindVertexArray(cube_vao);

    // Bind indices and upload data
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cube_vbo[0]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * cube_index->size(), cube_index->data(), GL_STATIC_DRAW);

    // Bind vertices and upload data
    glBindBuffer(GL_ARRAY_BUFFER, cube_vbo[1]);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GL_FLOAT)*3, (void*)0);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * cube_vertex->size(), cube_vertex->data(), GL_STATIC_DRAW);

    // Bind normals and upload data
    glBindBuffer(GL_ARRAY_BUFFER, cube_vbo[2]);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GL_FLOAT)*3, (void*)0);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * cube_normal->size(), cube_normal->data(), GL_STATIC_DRAW);

    // Bind uv coords and upload data
    glBindBuffer(GL_ARRAY_BUFFER, cube_vbo[3]);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(GL_FLOAT)*2, (void*)0);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * cube_text_coord->size(), cube_text_coord->data(), GL_STATIC_DRAW);

    // Unbind everything
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

Cube::Cube(glm::vec4 color) : Object3D(color)
{
    if(cube_vertex == NULL)
    {
        init_canonical_cube();
        init_vao();
    }
    vertex = cube_vertex;
    normal = cube_normal;
    text_coord = cube_text_coord;
    index = cube_index;
    nb_triangles = 12;
}
