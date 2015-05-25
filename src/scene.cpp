#include <scene.hpp>

Tree* Scene::create_scene(void)
{
    Node* tree;
    Tree* node;
    glm::vec3 trans(0., 1.2, 0.);

    tree = new Node();

    node = onagre_ring();
    tree -> add_children(node);

    node = Castle::create_castle();
    node -> apply_rotation_on_y(3*PI/4);
    tree -> add_children(node);

    node = create_diorama();
    tree->add_children(node);

    node = create_banner();
    node -> apply_translation(trans);
    node -> apply_rotation_on_y(PI/4);
    tree -> add_children(node);

    tree -> apply_homothety(glm::vec3(.5, .5, .5));
    return tree;
}

Tree* Scene::onagre_ring(void)
{
    int i, n;
    double alpha;
    Node* tree;
    Tree* node;
    glm::vec4 color(1., 1., 1., 1.);
    glm::vec3 point(15., 0., 0.);

    n = 15;
    alpha = 2*PI/n;
    tree = new Node();

    for(i = 0; i < n; i++)
    {
        node = Onagre::create_onagre(color);
        node -> apply_rotation_on_y(i*alpha);
        node -> apply_translation(point);
        tree -> add_children(node);
    }
    return tree;
}

Tree* Scene::create_diorama(void)
{
    Object3D* obj;
    Shader* s;
    glm::vec3 point, vector;
    Node* tree = new Node();

    glm::vec4 brown(.57, .43, .15, 1.);
    glm::vec4 blue(.12, .5, .5, 1.);
    glm::vec4 yellow(.75, .75, 0., 1.);
    glm::vec4 white(1., 1., 1., 1.);


    point.x = point.z = 0.;
    point.y = -.1;
    vector.x = vector.z = 4.5;
    vector.y = .1;
    obj = new Cube(yellow);
    obj -> apply_translation(point);
    obj -> apply_homothety(vector);
    s = new Shader(shader_name);
    s -> attach_texture("textures/sand.jpg");
    s -> attach_texture("textures/pure_white.png");
    tree -> add_child(obj, s);

    point.x = -4.6;
    point.y = 1.3;
    vector.x = .1;
    vector.y = 1.5;
    obj = new Cube(white);
    obj -> apply_translation(point);
    obj -> apply_homothety(vector);
    s = new Shader(shader_name);
    s -> attach_texture("textures/ciel.jpg");
    s -> attach_texture("textures/pure_white.png");
    tree -> add_child(obj, s);

    point.x = -.1;
    point.z = -4.6;
    vector.x = 4.6;
    vector.z = .1;
    obj = new Cube(white);
    obj -> apply_translation(point);
    obj -> apply_homothety(vector);
    s = new Shader(shader_name);
    s -> attach_texture("textures/ciel.jpg");
    s -> attach_texture("textures/pure_white.png");
    tree -> add_child(obj, s);

    point.x = point.z = 0.;
    point.y = -2.35;
    vector.x = vector.z = 5.;
    vector.y = .4;
    obj = new Cube(brown);
    obj -> apply_translation(point);
    obj -> apply_homothety(vector);
    s = new Shader(shader_name);
    s -> attach_texture("textures/pure_white.png");
    s -> attach_texture("textures/pure_white.png");
    tree -> add_child(obj, s);

    point.y = -1.2;
    vector.x = vector.z = 4.;
    vector.y = 1.;
    obj = new Cylinder(brown);
    obj -> apply_translation(point);
    obj -> apply_homothety(vector);
    s = new Shader(shader_name);
    s -> attach_texture("textures/pure_white.png");
    s -> attach_texture("textures/pure_white.png");
    tree -> add_child(obj, s);

    return tree;
}

Tree* Scene::create_banner(void)
{
    Object3D* obj;
    Shader* s;
    glm::vec3 point, vector;
    Node* tree = new Node();

    glm::vec4 brown(0.28, 0.21, 0.08, 1.);
    glm::vec4 white(1., 1., 1., 1.);

    obj = new Cylinder(white);
    point.x = 0;
    point.z = -0.02;
    point.y = 0.2;
    obj -> apply_translation(point);
    vector.x = vector.z = 0.03;
    vector.y = 0.2;
    obj -> apply_homothety(vector);
    s = new Shader(shader_name);
    s -> attach_texture("textures/bois_1.jpg");
    s -> attach_texture("textures/pure_white.png");
    tree -> add_child(obj, s);

    obj = new Cube(white);
    point.x = point.z = 0;
    point.y = 0.5;
    obj -> apply_translation(point);
    vector.x = vector.y = 0.3;
    vector.z = 0.02;
    obj -> apply_homothety(vector);
    s = new Shader(shader_name);
    s -> attach_texture("textures/bois_1.jpg");
    s -> attach_texture("textures/pure_white.png");
    tree -> add_child(obj, s);

    obj = new Cube(white);
    point.x = 0;
    point.z = 0.02;
    point.y = 0.5;
    obj -> apply_translation(point);
    vector.x = vector.y = 0.3;
    vector.z = 0.001;
    obj -> apply_homothety(vector);
    s = new Shader(shader_name);
    s -> attach_texture("textures/flappy_bird.png");
    s -> attach_texture("textures/pure_white.png");
    tree -> add_child(obj, s);

    return tree;
}

void Scene::update_lights(Camera cam)
{
    GLuint ssbo[2];
    glGenBuffers(2, ssbo);
    double angular_factor = 2. * PI / spotlightCount;
    //Matrix m = cam.get_projection() * cam.get_transformation();
    Matrix m = cam.get_transformation();

    glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssbo[0]);
    glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(Spotlight) * spotlightCount + 4 * sizeof(int), NULL, GL_DYNAMIC_COPY);
    void * lightBuffer = glMapBuffer(GL_SHADER_STORAGE_BUFFER, GL_WRITE_ONLY);
    int * tmp = (int*) ((int*)lightBuffer + 4);
    ((int*) lightBuffer)[0] = spotlightCount;
    for (int i = 0; i < spotlightCount; ++i)
    {
        Spotlight spot = {
            glm::vec3(cos(i * angular_factor), 2., sin(i * angular_factor)),
            80,
            glm::vec3(cos(i * angular_factor), -1, sin(i * angular_factor)),
            100,
            glm::vec3(1, 1, 1),
            1.
        };
        ((Spotlight*) tmp)[i] = spot;
    }
    glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);
    angular_factor = 2. * PI / pointlightCount;
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssbo[1]);
    glBufferData(GL_SHADER_STORAGE_BUFFER, 3 * sizeof(Pointlight) * pointlightCount + 4 * sizeof(int), NULL, GL_DYNAMIC_COPY);
    lightBuffer = glMapBuffer(GL_SHADER_STORAGE_BUFFER, GL_WRITE_ONLY);
    ((int*) lightBuffer)[0] = 3*pointlightCount;
    tmp = (int*) ((int*)lightBuffer + 4);
    for (int i = 0; i < pointlightCount; ++i)
    {
        float intensity = 1.;
        glm::vec3 color(1., 1., 1.);
        Pointlight p = {
            glm::vec3(2.5*cos(i * angular_factor), .5, 2.5*sin(i * angular_factor)),
            intensity,
            color,
            0.
        };
        Pointlight q = {
            glm::vec3(5.*cos(i * angular_factor), .5, 5.*sin(i * angular_factor)),
            intensity,
            color,
            0.
        };
        Pointlight r = {
            glm::vec3(1.*cos(i * angular_factor), .5, 1.*sin(i * angular_factor)),
            intensity,
            color,
            0.
        };

        ((Pointlight*) tmp)[i*3] = p;
        ((Pointlight*) tmp)[i*3+1] = q;
        ((Pointlight*) tmp)[i*3+2] = r;
    }
    glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);

    glBindBufferRange(GL_SHADER_STORAGE_BUFFER, 0, ssbo[0], 0, sizeof(Spotlight) * spotlightCount + 4 * sizeof(int));
    glBindBufferRange(GL_SHADER_STORAGE_BUFFER, 1, ssbo[1], 0, 3 * sizeof(Pointlight) * pointlightCount + 4 * sizeof(int));
}
