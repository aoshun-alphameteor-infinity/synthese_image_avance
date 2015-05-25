#include <interface.hpp>
#include <iostream>

int phase_time = 0;
int fire_phasis = 0;
bool shoot_mod_anim = false;
static Node* root = new Node();
static const float STEP_DEP = 0.1;

using namespace std;

void Interface::change_animation()
{
    if(!shoot_mod_anim)
    {
        shoot_mod_anim = true;
        phase_time = 0;
        return;
    }
}

Interface::Interface(int width, int height)
{
    this -> width = width;
    this -> height = height;
    this -> display_mode = 0;
    this -> camera = Camera(glm::vec3(3, 3, 3), glm::vec3(-1, -1, -1));
}

Interface::~Interface()
{
    delete root;
}

void Interface::keyboard_function(unsigned char c, int x, int y)
{
    switch(c) {
    case 27: // quit
        canonical_delete();
        exit(EXIT_SUCCESS);
        break;
    case 'i' :
        glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
        break;
    case 'I' :
        glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
        break;
    case 'z':
        camera.look_up(5. * M_PI / 180.);
        break;
    case 'q':
        camera.look_left(5. * M_PI / 180.);
        break;
    case 's':
        camera.look_down(5. * M_PI / 180.);
        break;
    case 'd':
        camera.look_right(5. * M_PI / 180.);
        break;
    case 'r':
        //reset();
        break;
    case 'f':
        change_animation();
        break;
    default :
        std::cerr<<"Key with no binding (mouse at "<<x<<"/"<<y<<")"<<std::endl;
    }
    glutPostRedisplay();
}

void Interface::keyboard_special_function(int c, int x, int y)
{
    switch(c)
    {
        case GLUT_KEY_F1 : case GLUT_KEY_F2 : case GLUT_KEY_F3 :
        case GLUT_KEY_F4 : case GLUT_KEY_F5 : case GLUT_KEY_F6 :
        case GLUT_KEY_F7 : case GLUT_KEY_F8 : case GLUT_KEY_F9 :
            display_mode = c - GLUT_KEY_F1;
            break;
        case GLUT_KEY_PAGE_UP:
            camera.move_up(STEP_DEP);
            break;
        case GLUT_KEY_PAGE_DOWN:
            camera.move_down(STEP_DEP);
            break;
        case GLUT_KEY_UP:
            camera.move_front(STEP_DEP);
            break;
        case GLUT_KEY_DOWN:
            camera.move_back(STEP_DEP);
            break;
        case GLUT_KEY_LEFT:
            camera.move_left(STEP_DEP);
            break;
        case GLUT_KEY_RIGHT:
            camera.move_right(STEP_DEP);
            break;
        default :
            std::cerr<<"Touche speciale non fonctionnelle"<<std::endl;
    }
    glutPostRedisplay();
}

void Interface::mouse_function(int button, int state, int x, int y)
{
    if ((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN)) {
        std::cerr<<"We clic on "<<x<<"/"<<y<<" coordinates of the screen"<<std::endl;
    }
    glutPostRedisplay();
}

void Interface::idle_function()
{
    int t = timer.elapsed_time();
    root->animation(t);
    phase_time+=t;

    if(shoot_mod_anim)
    {
        switch(fire_phasis)
        {
            case 0 :
                if(phase_time > TIME_ROTATION_SELF)
                {
                    phase_time = 0;
                    fire_phasis++;
                }
                break;
            case 1 :
                if(phase_time > (TIME_SPOON_REACT - 1))
                {
                    phase_time = 0;
                    fire_phasis++;
                }
                break;
            case 2 :
                if(phase_time > (RELOAD_TIME - 1))
                {
                    phase_time = 0;
                    fire_phasis++;
                }
                break;
            case 3 :
                if(phase_time > TIME_ROTATION_SELF)
                {
                    phase_time = 0;
                    fire_phasis = 0;
                    shoot_mod_anim = false;
                }
                break;
            default :
                break;
        }
    }

    glutPostRedisplay();
}

void Interface::reshape(int width, int height)
{
    this -> width = width;
    this -> height = height;

    glViewport( 0, 0, (GLint)width, (GLint)height );
}

void Interface::init(void)
{
    int i, j;
    phase_time = 0;

    root->add_children(Scene::create_scene());


    /// GL INITIALISATION
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glShadeModel( GL_SMOOTH );
    glDisable(GL_BLEND);
    glCullFace(GL_BACK);
    glDisable( GL_CULL_FACE );

}

void Interface::reset(void)
{
    delete root;
    root = new Node();
    init();
    phase_time = 0;
    fire_phasis = 0;
    shoot_mod_anim = false;
}

void Interface::draw(void)
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glEnable(GL_DEPTH_TEST);
    Scene::update_lights(this->camera);
    root->draw(this -> camera);
    glutSwapBuffers();
}
