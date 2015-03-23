#include <canonical_cone.hpp>

float *Cone::cone_vertex = NULL;
float *Cone::cone_normal = NULL;
float *Cone::cone_texcoord = NULL;
unsigned int *Cone::cone_index = NULL;
GLuint Cone::cone_vao = 0;
GLuint Cone::cone_vbo[4];

void Cone::init_canonical_cone (void)
{
    unsigned int i;
    double alpha, cosi, sini;
    cone_vertex = new float[3 * (NMAX + 2)];
    cone_normal = new float[3 * (NMAX + 2)];
    cone_index = new unsigned int[6 * NMAX];
    cone_texcoord = new float[2 * (NMAX + 2)];

    alpha = 2 * PI / NMAX;
    
    memset(cone_vertex, 0, 3 * (NMAX + 2) * sizeof(float));
    memset(cone_normal, 0, 3 * (NMAX + 2) * sizeof(float));
    
    cone_normal[1] = -1;
    for(i = 1; i < NMAX + 1; i++)
    {
        cosi = cos(i * alpha);
        sini = sin(i * alpha);
        cone_vertex[3 * i] = cosi;
        cone_vertex[3 * i + 2] = sini;
        
        cone_normal[3 * (i + NMAX)] = cosi;
        cone_normal[3 * (i + NMAX) + 2] = sini;
    }
    cone_normal[3 * (NMAX + 1) + 2] = cone_vertex[3 * (NMAX + 2) + 1] = 1;
    
    
    for(i = 1; i < NMAX; i++)
    {
        cone_index[3 * (i - 1)] = 0;
        cone_index[3 * (i - 1) + 1] = i;
        cone_index[3 * (i - 1) + 2] = i + 1;
        cone_index[3 * ((i - 1) + NMAX)] = i;
        cone_index[3 * ((i - 1) + NMAX) + 1] = NMAX + 1;
        cone_index[3 * ((i - 1) + NMAX) + 2] = i + 1;
    }
    cone_index[3 * (NMAX - 1)] = 0;
    cone_index[3 * (NMAX - 1) + 1] = NMAX;
    cone_index[3 * (NMAX - 1) + 2] = 1;
    cone_index[3 * (2 * NMAX - 1)] = NMAX;
    cone_index[3 * (2 * NMAX - 1) + 1] = NMAX + 1;
    cone_index[3 * (2 * NMAX - 1) + 2] = 1;
    
    double jmp = 1 / NMAX;
    cone_texcoord[0] = cone_texcoord[1] = 1;
    for(i = 1; i < NMAX + 1; i++)
    {
        cone_texcoord[2 * i] = 0;
        cone_texcoord[2 * i + 1] = i * NMAX;
    }
    cone_texcoord[2 * NMAX + 2] = cone_texcoord[2 * NMAX + 3] = 1;
}

Cone::Cone(glm::vec4 col) : Object3D(col)
{
    if(cone_vertex == NULL)
    {
        init_canonical_cone();
        
        glGenVertexArrays(1, &cone_vao);
        glBindVertexArray(cone_vao);
        
        glGenBuffers(4, cone_vbo);
        
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cone_vbo[0]);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cone_index), cone_index, GL_STATIC_DRAW);
        
        glBindBuffer(GL_ARRAY_BUFFER, cone_vbo[1]);
        glEnableVertexAttribArray(0); 
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GL_FLOAT)*3, (void*)0);
        glBufferData(GL_ARRAY_BUFFER, sizeof(cone_vertex), cone_vertex, GL_STATIC_DRAW);
        
        glBindBuffer(GL_ARRAY_BUFFER, cone_vbo[2]);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GL_FLOAT)*3, (void*)0);
        glBufferData(GL_ARRAY_BUFFER, sizeof(cone_normal), cone_normal, GL_STATIC_DRAW);
    
        glBindBuffer(GL_ARRAY_BUFFER, cone_vbo[3]);
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(GL_FLOAT)*2, (void*)0);
        glBufferData(GL_ARRAY_BUFFER, sizeof(cone_texcoord), cone_texcoord, GL_STATIC_DRAW);
        
        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
    this -> nb_triangles = 2 * NMAX;
    vertex = cone_vertex;
    normal = cone_normal;
    index = cone_index;
    text_coord = cone_texcoord;
}