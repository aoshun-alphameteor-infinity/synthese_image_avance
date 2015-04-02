#include <onagre.hpp>

Shader *Onagre::s = NULL;

Tree* Onagre::create_onagre_main_body(glm::vec4 color) {
    Node* body;
    Object3D* obj;
    glm::vec3 point;
    glm::vec3 vector;
    std::cerr << "onagre main body" << std::endl;

    body = new Node();

    point.x = -.5;
    point.y = point.z = 0.;
    vector.x = vector.y = .1;
    vector.z = 1.;
    obj = new Cube(color);
    obj->apply_translation(point);
    obj->apply_homothety(vector);
    body->add_child(obj, s);

    point.x = .5;
    obj = new Cube(color);
    obj->apply_translation(point);
    obj->apply_homothety(vector);
    body->add_child(obj, s);

    point.x = 0.;
    point.z = .85;
    vector.x = .5;
    vector.y = vector.z = .09;
    obj = new Cube(color);
    obj->apply_translation(point);
    obj->apply_homothety(vector);
    body->add_child(obj, s);

    point.y = 0.;
    point.z = -.6;
    obj = new Cube(color);
    obj->apply_translation(point);
    obj->apply_homothety(vector);
    body->add_child(obj, s);

    point.y = -.03;
    point.z = .65;
    vector.y = vector.z = .06;
    obj = new Cube(color);
    obj->apply_translation(point);
    obj->apply_homothety(vector);
    body->add_child(obj, s);

    point.z = -.4;
    obj = new Cube(color);
    obj->apply_translation(point);
    obj->apply_homothety(vector);
    body->add_child(obj, s);

    point.x = 0.;
    point.y = .6;
    point.z = .35;
    vector.x = .7;
    vector.y = vector.z = .09;
    obj = new Cube(color);
    obj->apply_translation(point);
    obj->apply_homothety(vector);
    body->add_child(obj, s);

    point.x = .8;
    point.z = .385;
    vector.x = vector.z = .07;
    vector.y = .1;
    obj = new Horn(color);
    obj->apply_translation(point);
    obj->apply_rotation_on_z(PI/2.);
    obj->apply_homothety(vector);
    body->add_child(obj, s);

    point.x = -.8;
    obj = new Horn(color);
    obj->apply_translation(point);
    obj->apply_rotation_on_z(-PI/2.);
    obj->apply_homothety(vector);
    body->add_child(obj, s);

    point.x = 0.;
    point.z = .45;
    vector.y = .7;
    obj = new Cylinder(color);
    obj->apply_translation(point);
    obj->apply_rotation_on_x(PI/2.);
    obj->apply_rotation_on_z(PI/2.);
    obj->apply_homothety(vector);
    body->add_child(obj, s);

    point.x = .5;
    point.y = .31;
    point.z = .35;
    vector.x = vector.z = .09;
    vector.y = .22;
    obj = new Cube(color);
    obj->apply_translation(point);
    obj->apply_homothety(vector);
    body->add_child(obj, s);

    point.x = -.5;
    obj = new Cube(color);
    obj->apply_translation(point);
    obj->apply_homothety(vector);
    body->add_child(obj, s);

    point.y = .25;
    point.z = .15;
    vector.y = .09;
    vector.z = .3;
    obj = new Cube(color);
    obj->apply_translation(point);
    obj->apply_rotation_on_x(PI/4.);
    obj->apply_homothety(vector);
    body->add_child(obj, s);

    point.x = .5;
    obj = new Cube(color);
    obj->apply_translation(point);
    obj->apply_rotation_on_x(PI/4.);
    obj->apply_homothety(vector);
    body->add_child(obj, s);

    point.y = .25;
    point.z = .55;
    obj = new Cube(color);
    obj->apply_translation(point);
    obj->apply_rotation_on_x(-PI/4.);
    obj->apply_homothety(vector);
    body->add_child(obj, s);

    point.x = -.5;
    point.z = -.92;
    obj = new Cube(color);
    obj->apply_translation(point);
    obj->apply_rotation_on_x(-PI/4.);
    obj->apply_homothety(vector);
    body->add_child(obj, s);

    point.x = point.y = 0.;
    point.z = -.9;
    vector.x = vector.z = .05;
    vector.y = .5;
    obj = new Cylinder(color);
    obj->apply_translation(point);
    obj->apply_rotation_on_x(-PI/2.);
    obj->apply_rotation_on_z(-PI/2.);
    obj->apply_homothety(vector);
    body->add_child(obj, s);

    point.x = .7;
    point.y = -.04;
    point.z = .65;
    vector.y = .12;
    obj = new Cylinder(color);
    obj->apply_translation(point);
    obj->apply_rotation_on_z(-PI/2.);
    obj->apply_homothety(vector);
    body->add_child(obj, s);

    point.x = -.7;
    obj = new Cylinder(color);
    obj->apply_translation(point);
    obj->apply_rotation_on_z(-PI/2.);
    obj->apply_homothety(vector);
    body->add_child(obj, s);

    point.z = -.4;
    obj = new Cylinder(color);
    obj->apply_translation(point);
    obj->apply_rotation_on_z(-PI/2.);
    obj->apply_homothety(vector);
    body->add_child(obj, s);

    point.x = .7;
    obj = new Cylinder(color);
    obj->apply_translation(point);
    obj->apply_rotation_on_z(-PI/2.);
    obj->apply_homothety(vector);
    body->add_child(obj, s);

    return body;
}


Tree* Onagre::create_onagre_spoon(glm::vec4 color) {
    Node* spoon;
    Object3D* obj;
    glm::vec3 point;
    glm::vec3 vector;
    std::cerr << "onagre spoon" << std::endl;

    spoon = new Node();

    point.x = point.y = 0.;
    point.z = .25;
    spoon->apply_translation(point);
    spoon->apply_rotation_on_x(-PI/2.);
    spoon->apply_rotation_on_z(-PI/2.);

    vector.x = vector.z = .07;
    vector.y = .61;
    obj = new Cylinder(color);
    obj->apply_homothety(vector);
    spoon->add_child(obj, s);

    point.y = .23;
    point.z = -0.38;
    vector.y = .45;
    obj = new Cylinder(color);
    obj->apply_rotation_on_z(PI/2.);
    obj->apply_rotation_on_x(PI/2.);
    obj->apply_translation(point);
    obj->apply_rotation_on_x(PI/3.);
    obj->apply_homothety(vector);
    spoon->add_child(obj, s);

    point.y = .53;
    point.z = -0.90;
    vector.y = .06;
    obj = new Tore(color);
    obj->apply_rotation_on_z(PI/2.);
    obj->apply_rotation_on_x(PI/2.);
    obj->apply_translation(point);
    obj->apply_rotation_on_x(PI/3. + PI/2.);
    obj->apply_homothety(vector);
    spoon->add_child(obj, s);

    point.y = .5;
    point.z = -.92;
    vector.x = vector.z = .14;
    vector.y = .02;
    obj = new Sphere(color);
    obj->apply_rotation_on_z(PI/2.);
    obj->apply_rotation_on_x(PI/2.);
    obj->apply_translation(point);
    obj->apply_rotation_on_x(PI/3. + PI/2.);
    obj->apply_homothety(vector);
    spoon->add_child(obj, s);

    return spoon;
}

Tree* Onagre::create_onagre_wheel(glm::vec4 color) {
    Node* wheel;
    Object3D* obj;
    glm::vec3 point;
    glm::vec3 vector;
    std::cerr << "onagre wheel" << std::endl;

    wheel = new Node();

    point.x = .7;
    point.y = -.04;
    point.z = .65;
    vector.x = vector.z = .2;
    vector.y = .1;
    obj = new Cylinder(color);
    obj->apply_translation(point);
    obj->apply_rotation_on_z(-PI/2.);
    obj->apply_homothety(vector);
    wheel->add_child(obj, s);

    point.x = -.7;
    obj = new Cylinder(color);
    obj->apply_translation(point);
    obj->apply_rotation_on_z(-PI/2.);
    obj->apply_homothety(vector);
    wheel->add_child(obj, s);

    point.x = .7;
    point.z = -.4;
    obj = new Cylinder(color);
    obj->apply_translation(point);
    obj->apply_rotation_on_z(-PI/2.);
    obj->apply_homothety(vector);
    wheel->add_child(obj, s);

    point.x = -.7;
    obj = new Cylinder(color);
    obj->apply_translation(point);
    obj->apply_rotation_on_z(-PI/2.);
    obj->apply_homothety(vector);
    wheel->add_child(obj, s);

    return wheel;
}

Tree* Onagre::create_onagre(glm::vec4 color) {
    Node* onagre;

    glm::vec3 point(0., 0.048, 0.);
    glm::vec3 vector(.2, .2, .2);
    if(s == NULL)
        s = new Shader("base");
    std::cerr << "create onagre" << std::endl;

    onagre = new Anim_Node();
    onagre->apply_translation(point);
    onagre->apply_homothety(vector);

    onagre->add_children(create_onagre_main_body(color));

    onagre->add_children(create_onagre_spoon(color));

    onagre->add_children(create_onagre_wheel(color));

    return onagre;
}
