#include <interface.hpp>
#include <iostream>

int nb_turn = 0;
int fire_phasis = 0;
bool mod_anim = true;
static Tree* root = new Node();

void Interface::change_animation(){
    if(mod_anim == true) {
        mod_anim = false;
        nb_turn = 0;
        return;
    }
};

Interface::Interface(int width, int height)
{
    this -> width = width;
    this -> height = height;
    this -> display_mode = 0;
};

Interface::~Interface()
{
    delete root;
};

void Interface::keyboard_function(unsigned char c, int x, int y)
{
    switch(c) {
    case 27: // quit
        exit(EXIT_SUCCESS);
        break;
    case 'z':
        camera.move_front(1);
        break;
    case 'q':
        camera.move_left(1);
        break;
    case 's':
        camera.move_back(1);
        break;
    case 'd':
        camera.move_right(1);
        break;
    case 'r':
        reset();
        break;
    case 'f':
        change_animation();
        break;
    default :
        std::cerr<<"Key with no binding (mouse at "<<x<<"/"<<y<<")"<<std::endl;
    }
    glutPostRedisplay();
};

void Interface::keyboard_special_function(int c, int x, int y)
{
    switch(c)
    {
        case GLUT_KEY_F1 : case GLUT_KEY_F2 : case GLUT_KEY_F3 :
        case GLUT_KEY_F4 : case GLUT_KEY_F5 : case GLUT_KEY_F6 :
        case GLUT_KEY_F7 : case GLUT_KEY_F8 : case GLUT_KEY_F9 :
            display_mode = c - GLUT_KEY_F1;
            break;
        default :
            std::cerr<<"Touche speciale non fonctionnelle"<<std::endl;
    }
    glutPostRedisplay();
};

void Interface::mouse_function(int button, int state, int x, int y)
{
    if ((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN)) {
        std::cerr<<"We clic on "<<x<<"/"<<y<<" coordinates of the screen"<<std::endl;
    }
    glutPostRedisplay();
};

void Interface::idle_function()
{
    root->animation();
    nb_turn++;
};

void Interface::reshape(int width, int height)
{
    this -> width = width;
    this -> height = height;

    glViewport( 0, 0, (GLint)width, (GLint)height );
};

void Interface::init(void) {
    int i, j;
    nb_turn = 0;
    glm::vec4 color = {0.5, 0.5, 0.24, 1.00};

    ((Node*)root)->add_children(Scene::create_scene());

}

void Interface::reset(void) {
    root = new Node();
    init();
    nb_turn = 0;
    fire_phasis = 0;
    mod_anim = true;
}

void Interface::draw(void) {
    root->draw(this -> camera);
}
