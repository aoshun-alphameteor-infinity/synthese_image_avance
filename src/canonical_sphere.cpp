#include <canonical_sphere.hpp>

float *Sphere::sphere_vertex = NULL;
float *Sphere::sphere_normal = NULL;
float *Sphere::sphere_text_coord = NULL;
unsigned int *Sphere::sphere_index = NULL;
GLuint Sphere::sphere_vao = 0;
GLuint Sphere::sphere_vbo[4];

void Sphere::init_canonical_sphere(void)
{
    int i, j, id;
    float alpha, phi, cosi, sini, cosj, sinj, tex_i, tex_j, tci;
    sphere_vertex = new float[((NMAX - 1) * PMAX + 2) * 3];
    sphere_normal = new float[((NMAX - 1) * PMAX + 2) * 3];
    sphere_text_coord = new float[((NMAX - 1) * PMAX + 2) * 2];
    sphere_index = new unsigned int[(NMAX - 1) * PMAX * 6];

    alpha = 2. * PI / PMAX;
    phi = PI / NMAX;

    tex_i = 1. / NMAX;
    tex_j = 1. / PMAX;
    
    sphere_vertex[0] = 0.;
    sphere_vertex[1] = 1.;
    sphere_vertex[2] = 0.;

    sphere_text_coord[0] = 0.;
    sphere_text_coord[1] = 0.;

    for(i = 0; i < NMAX - 1; i++)
    {
        cosi = cosf((i + 1) * phi);
        sini = sinf((i + 1) * phi);
        tci = (i + 1) * tex_i;
        for(j = 0; j < PMAX; j++)
        {
            cosj = cosf(j * alpha);
            sinj = sinf(j * alpha);
            sphere_vertex[(i * PMAX + j + 1) * 3    ] = cosj * sini;
            sphere_vertex[(i * PMAX + j + 1) * 3 + 1] = cosi;
            sphere_vertex[(i * PMAX + j + 1) * 3 + 2] = sinj * sini;

            sphere_text_coord[(i * PMAX + j + 1) * 2    ] = j * tex_j;
            sphere_text_coord[(i * PMAX + j + 1) * 2 + 1] = tci;

        }
    }

    sphere_vertex[((NMAX - 1) * PMAX + 1) * 3    ] =  0.;
    sphere_vertex[((NMAX - 1) * PMAX + 1) * 3 + 1] = -1.;
    sphere_vertex[((NMAX - 1) * PMAX + 1) * 3 + 2] =  0.;

    sphere_text_coord[((NMAX - 1) * PMAX + 1) * 2    ] = 1.;
    sphere_text_coord[((NMAX - 1) * PMAX + 1) * 2 + 1] = 1.;

    memcpy(sphere_normal, sphere_vertex, ((NMAX - 1) * PMAX + 2) * 3 * sizeof(float));

    id = 0;

    for(unsigned int v = 0; v < PMAX - 1; v++)
    {
        index[id    ] = 0;
        index[id + 1] = v + 1;
        index[id + 2] = v + 2;
        id += 3;
    }
    index[id    ] = 0;
    index[id + 1] = PMAX;
    index[id + 2] = 1;
    id +=3;

    for(unsigned int u = 0; u < NMAX - 2; u++)
    {
        for(unsigned int v = 0; v < PMAX - 1; v++)
        {
            index[id    ] = u * PMAX + v + 1;
            index[id + 1] = u * PMAX + v + 2;
            index[id + 2] = (u + 1) * PMAX + v + 1;

            index[id + 3] = (u + 1) * PMAX + v + 1;
            index[id + 4] = u * PMAX + v + 2;
            index[id + 5] = (u + 1) * PMAX + v + 2;
            id += 6;
        }
        index[id] = u * PMAX + PMAX;
        index[id + 1] = u * PMAX + 1;
        index[id + 2] = (u + 1) * PMAX + PMAX;

        index[id + 3] = (u + 1) * PMAX + PMAX;
        index[id + 4] = u * PMAX + 1;
        index[id + 5] = (u + 1) * PMAX + 1;
        id += 6;
    }

    for(unsigned int v = 0; v < PMAX - 1; v++)
    {
        index[id    ] = (NMAX - 1) * PMAX + 1;
        index[id + 1] = (NMAX - 2) * PMAX + v + 1;
        index[id + 2] = (NMAX - 2) * PMAX + v + 2;
        id += 3;
    }
    index[id    ] = (NMAX - 1) * PMAX + 1;
    index[id + 1] = (NMAX - 1) * PMAX;
    index[id + 2] = (NMAX - 2) * PMAX + 1;
    id +=3;
}

void Sphere::init_vao(void)
{
    // Create a Vertex Array Object
    glGenVertexArrays(1, &sphere_vao);
    // Create a VBO for each array
    glGenBuffers(4, sphere_vbo);
    // Bind the VAO
    glBindVertexArray(sphere_vao);

    // Bind indices and upload data
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, sphere_vbo[0]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(sphere_index), sphere_index, GL_STATIC_DRAW);

    // Bind vertices and upload data
    glBindBuffer(GL_ARRAY_BUFFER, sphere_vbo[1]);
    glEnableVertexAttribArray(0); 
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GL_FLOAT) * 3, (void*)0);
    glBufferData(GL_ARRAY_BUFFER, sizeof(sphere_vertex), sphere_vertex, GL_STATIC_DRAW);

    // Bind normals and upload data
    glBindBuffer(GL_ARRAY_BUFFER, sphere_vbo[2]);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GL_FLOAT) * 3, (void*)0);
    glBufferData(GL_ARRAY_BUFFER, sizeof(sphere_normal), sphere_normal, GL_STATIC_DRAW);

    // Bind uv coords and upload data
    glBindBuffer(GL_ARRAY_BUFFER, sphere_vbo[3]);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(GL_FLOAT) * 2, (void*)0);
    glBufferData(GL_ARRAY_BUFFER, sizeof(sphere_text_coord), sphere_text_coord, GL_STATIC_DRAW);

    // Unbind everything
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

Sphere::Sphere(glm::vec4 col) : Object3D(col)
{
    if(sphere_vertex == NULL) {
        init_canonical_sphere();
        init_vao();
    }
    vertex = sphere_vertex;
    normal = sphere_normal;
    index = sphere_index;
    text_coord = sphere_text_coord;
    nb_triangles = (NMAX - 1) * PMAX;
}