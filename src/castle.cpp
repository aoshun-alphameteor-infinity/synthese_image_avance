#include <castle.hpp>

Shader *Castle::s = NULL;
glm::vec4 color(.5, 0., .7, 1.);

Tree* Castle::create_tower_top(void){
    Node* top = new Node();
    Object3D* objet;
    glm::vec3 point, vecteur;

    point.x = point.z = 0.0;

    objet = new Cone(red);
    point.y = 1.5;
    vecteur.x = vecteur.z = 0.5;
    vecteur.y = 1.0;
    objet -> apply_translation(point);
    objet -> apply_homothety(vecteur);
    top -> add_child(objet, s);

    objet = new Cone(red);
    point.y = 1.0;
    objet -> apply_translation(point);
    top -> add_child(objet, s);

    objet = new Tore(red);
    point.y = 1.0;
    objet -> apply_translation(point);
    vecteur.x = vecteur.y = 0.3;
    vecteur.z = 0.25;
    objet -> apply_homothety(vecteur);
    top -> add_child(objet, s);

    return top;
}

/* --------------------------------------------------------- */
/* --------------------------------------------------------- */
/* --------------------------------------------------------- */
Tree* Castle::create_tower(void){
    Node* tower = new Node();
    Tree* piece;
    Object3D* objet;
    glm::vec3 h(0.65, 1.2, 0.65);

    piece = create_tower_top();
    tower -> add_children(piece);

    objet = new Cylinder(yellow);
    objet -> apply_homothety(h);
    tower -> add_child(objet, s);

    return tower;
}

/* --------------------------------------------------------- */
/* --------------------------------------------------------- */
/* --------------------------------------------------------- */
Tree* Castle::create_wall(void){
    Node* wall = new Node();
    Object3D* objet;
    glm::vec3 point, vecteur;

    objet = new Cube(yellow);
    vecteur.x = 0.4;
    vecteur.z = 3.0;
    vecteur.y = 2.0;
    objet -> apply_homothety(vecteur);
    wall -> add_child(objet, s);

    objet = new Cube(yellow);
    point.x = -0.40;
    point.z = 0.0;
    point.y = 1.85;
    vecteur.x = 0.25;
    vecteur.z = 3.0;
    vecteur.y = 0.6;
    objet -> apply_translation(point);
    objet -> apply_homothety(vecteur);
    wall -> add_child(objet, s);

    return wall;
}

/* --------------------------------------------------------- */
/* --------------------------------------------------------- */
/* --------------------------------------------------------- */
Tree* Castle::create_wall_with_gate(void){
    Node* wall = new Node();
    Object3D* objet;
    glm::vec3 point, vecteur;

    objet = new Cube(red);
    vecteur.x = 0.15;
    vecteur.z = 0.8;
    vecteur.y = 1.5;
    objet -> apply_homothety(vecteur);
    wall -> add_child(objet, s);

    objet = new Cube(yellow);
    point.x = point.y = 0.0;
    point.z = 1.9;
    vecteur.x = 0.4;
    vecteur.z = 1.1;
    vecteur.y = 1.5;
    objet -> apply_translation(point);
    objet -> apply_homothety(vecteur);
    wall -> add_child(objet, s);

    objet = new Cube(yellow);
    point.x = point.y = 0.0;
    point.z = -1.9;
    vecteur.x = 0.4;
    vecteur.z = 1.1;
    vecteur.y = 1.5;
    objet -> apply_translation(point);
    objet -> apply_homothety(vecteur);
    wall -> add_child(objet, s);

    objet = new Cube(yellow);
    point.x = point.z = 0.0;
    point.y = 1.9;
    vecteur.x = 0.4;
    vecteur.z = 3.0;
    vecteur.y = 0.5;
    objet -> apply_translation(point);
    objet -> apply_homothety(vecteur);
    wall -> add_child(objet, s);

    objet = new Cube(yellow);
    point.x = -0.40;
    point.z = 0.0;
    point.y = 2.25;
    vecteur.x = 0.25;
    vecteur.z = 3.0;
    vecteur.y = 0.6;
    objet -> apply_translation(point);
    objet -> apply_homothety(vecteur);
    wall -> add_child(objet, s);

    return wall;
}

/* --------------------------------------------------------- */
/* --------------------------------------------------------- */
/* --------------------------------------------------------- */
Tree* Castle::create_castle(void){
    Node* castle = new Node();
    Tree* piece;
    Object3D* objet;
    glm::vec3 point, vecteur;
    s = new Shader("base");

    /* dungeon */
    objet = new Cube(yellow);
    point.x = point.z = 0.0;
    point.y = 3.0;
    vecteur.x = vecteur.z = 2.0;
    vecteur.y = 3.0;
    objet -> apply_translation(point);
    objet -> apply_homothety(vecteur);
    castle -> add_child(objet, s);

    /* towers of the dungeon */
    /* homothety factors */
    vecteur.x = vecteur.z = 0.5;
    vecteur.y = 1.0;
    /* height of the translation */
    point.y = 6.25;

    piece = create_tower();
    point.x = 2.0;
    point.z = -2.0;
    piece -> apply_translation(point);
    piece -> apply_homothety(vecteur);
    castle -> add_children(piece);

    piece = create_tower();
    point.x = point.z = -2.0;
    piece -> apply_translation(point);
    piece -> apply_homothety(vecteur);
    castle -> add_children(piece);

    piece = create_tower();
    point.x = -2.0;
    point.z = 2.0;
    piece -> apply_translation(point);
    piece -> apply_homothety(vecteur);
    castle -> add_children(piece);

    piece = create_tower();
    point.x = point.z = 2.0;
    piece -> apply_translation(point);
    piece -> apply_homothety(vecteur);
    castle -> add_children(piece);

    /*wall*/
    /* front wall */
    piece = create_wall_with_gate();
    point.x = -7.3;
    point.z = 0.0;
    point.y = 1.16;
    vecteur.x = vecteur.z = 1.0;
    vecteur.y = 0.77;
    piece -> apply_translation(point);
    piece -> apply_homothety(vecteur);
    castle -> add_children(piece);

    /* other walls*/
    /* homothety factors */
    vecteur.x = vecteur.z = 1.0;
    vecteur.y = 0.75;
    /* translation height */
    point.y = 1.50;

    piece = create_wall();
    point.x = -7.3*cos(PI/4);
    point.z = -7.3*sin(PI/4);
    piece -> apply_translation(point);
    piece -> apply_rotation_on_y(-PI/4);
    piece -> apply_homothety(vecteur);
    castle -> add_children(piece);

    piece = create_wall();
    point.x = 0.0;
    point.z = -7.3;
    piece -> apply_translation(point);
    piece -> apply_rotation_on_y(-PI/2);
    piece -> apply_homothety(vecteur);
    castle -> add_children(piece);

    piece = create_wall();
    point.x = -7.3*cos(3*PI/4);
    point.z = -7.3*sin(3*PI/4);
    piece -> apply_translation(point);
    piece -> apply_rotation_on_y(-3*PI/4);
    piece -> apply_homothety(vecteur);
    castle -> add_children(piece);

    piece = create_wall();
    point.x = 7.3;
    point.z = 0.0;
    piece -> apply_translation(point);
    piece -> apply_rotation_on_y(-PI);
    piece -> apply_homothety(vecteur);
    castle -> add_children(piece);

    piece = create_wall();
    point.x = -7.3*cos(-3*PI/4);
    point.z = -7.3*sin(-3*PI/4);
    piece -> apply_translation(point);
    piece -> apply_rotation_on_y(3*PI/4);
    piece -> apply_homothety(vecteur);
    castle -> add_children(piece);

    piece = create_wall();
    point.x = 0.0;
    point.z = 7.3;
    piece -> apply_translation(point);
    piece -> apply_rotation_on_y(PI/2);
    piece -> apply_homothety(vecteur);
    castle -> add_children(piece);

    piece = create_wall();
    point.x = -7.3*cos(-PI/4);
    point.z = -7.3*sin(-PI/4);
    piece -> apply_translation(point);
    piece -> apply_rotation_on_y(PI/4);
    piece -> apply_homothety(vecteur);
    castle -> add_children(piece);

    /*wall tower*/
    /* homothety factors */
    vecteur.x = vecteur.z = 1.0;
    vecteur.y = 2.0;
    /* translation height */
    point.y = 2.4;

    piece = create_tower();
    point.x = -7.4;
    point.z = 2.8;
    piece -> apply_translation(point);
    piece -> apply_homothety(vecteur);
    castle -> add_children(piece);

    piece = create_tower();
    point.x = -7.4;
    point.z = -2.8;
    piece -> apply_translation(point);
    piece -> apply_homothety(vecteur);
    castle -> add_children(piece);

    piece = create_tower();
    point.x = 2.8;
    point.z = -7.4;
    piece -> apply_translation(point);
    piece -> apply_homothety(vecteur);
    castle -> add_children(piece);

    piece = create_tower();
    point.x = -2.8;
    point.z = -7.4;
    piece -> apply_translation(point);
    piece -> apply_homothety(vecteur);
    castle -> add_children(piece);

    piece = create_tower();
    point.x = 2.8;
    point.z = 7.4;
    piece -> apply_translation(point);
    piece -> apply_homothety(vecteur);
    castle -> add_children(piece);

    piece = create_tower();
    point.x = -2.8;
    point.z = 7.4;
    piece -> apply_translation(point);
    piece -> apply_homothety(vecteur);
    castle -> add_children(piece);

    piece = create_tower();
    point.x = 7.4;
    point.z = 2.8;
    piece -> apply_translation(point);
    piece -> apply_homothety(vecteur);
    castle -> add_children(piece);

    piece = create_tower();
    point.x = 7.4;
    point.z = -2.8;
    piece -> apply_translation(point);
    piece -> apply_homothety(vecteur);
    castle -> add_children(piece);

    vecteur.x = vecteur.y = vecteur.z = 0.2;
    castle->apply_homothety(vecteur);
    return castle;
}
