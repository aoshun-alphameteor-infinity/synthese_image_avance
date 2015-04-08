#include <scene.hpp>

Shader *Scene::s = NULL;

Tree* Scene::create_scene(void) {
    Object3D* obj;
    Node* tree;
    Tree* node;
    glm::vec3 point, vector;
    s = new Shader("base");

    glm::vec4 brown(.57, .43, .15, 1.);
    glm::vec4 blue(.12, .5, .5, 1.);
    glm::vec4 yellow(.75, .75, 0., 1.);

    tree = new Node();

    node = onagre_ring();
    tree -> add_children(node);

    node = Castle::create_castle();
    node -> apply_rotation_on_y(-3*PI/4);
    tree -> add_children(node);

    point.x = point.z = 0.;
    point.y = -.1;
    vector.x = vector.z = 4.5;
    vector.y = .1;
    obj = new Cube(yellow);
    obj -> apply_translation(point);
    obj -> apply_homothety(vector);
    tree -> add_child(obj, s);

    point.x = -4.6;
    point.y = 1.3;
    vector.x = .1;
    vector.y = 1.5;
    obj = new Cube(blue);
    obj -> apply_translation(point);
    obj -> apply_homothety(vector);
    tree -> add_child(obj, s);

    point.x = -.1;
    point.z = -4.6;
    vector.x = 4.6;
    vector.z = .1;
    obj = new Cube(blue);
    obj -> apply_translation(point);
    obj -> apply_homothety(vector);
    tree -> add_child(obj, s);

    point.x = point.z = 0.;
    point.y = -2.35;
    vector.x = vector.z = 5.;
    vector.y = .4;
    obj = new Cube(brown);
    obj -> apply_translation(point);
    obj -> apply_homothety(vector);
    tree -> add_child(obj, s);

    point.y = -1.2;
    vector.x = vector.z = 4.;
    vector.y = 1.;
    obj = new Cylinder(brown);
    obj -> apply_translation(point);
    obj -> apply_homothety(vector);
    tree -> add_child(obj, s);


    vector.x = vector.z = vector.y = .5;
    tree -> apply_homothety(vector);
    return tree;
}

Tree* Scene::onagre_ring(void) {
    int i, n;
    double alpha;
    Node* tree;
    Tree* node;
    glm::vec4 color(0.57, 0.43, 0.15, 1.);
    glm::vec3 point(15., 0., 0.);

    n = 15;
    alpha = 2*PI/n;
    tree = new Node();

    for(i = 0; i < n; i++) {
        node = Onagre::create_onagre(color);
        node -> apply_rotation_on_y(i*alpha);
        node -> apply_translation(point);
        tree -> add_children(node);
    }
    return tree;
}
