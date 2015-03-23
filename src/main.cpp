#include <iostream>
#include <interface.hpp>

Interface *ui = new Interface(800, 600);

void draw_wrapper()
{
    ui -> draw();
}

void keyboard_function_wrapper(unsigned char c, int x, int y)
{
    ui -> keyboard_function(c, x, y);
}

void keyboard_special_function_wrapper(int c, int x, int y)
{
    ui -> keyboard_special_function(c, x, y);
}

void idle_function_wrapper()
{
    ui -> idle_function();
}

void mouse_function_wrapper(int button, int state, int x, int y)
{
    ui -> mouse_function(button, state, x, y);
}


int main(int argc, char** argv){
    std::cerr << "go" << std::endl;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE | GLUT_STENCIL);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(ui -> get_width(), ui -> get_height());
    if (glutCreateWindow("Synthese Image Avance") == GL_FALSE) return EXIT_FAILURE;
    glewInit();

    ui -> init();

    glutDisplayFunc(draw_wrapper);
    glutMouseFunc(mouse_function_wrapper);
    glutKeyboardFunc(keyboard_function_wrapper);
    glutSpecialFunc(keyboard_special_function_wrapper);
    glutIdleFunc(idle_function_wrapper);

    glutMainLoop();

    return 0;
}

