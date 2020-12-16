#include <GL/glut.h>

void render()
{

    glClear(GL_COLOR_BUFFER_BIT);

    glFlush();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Pac-Man!");

    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 800.0, 0.0, 600.0);

    glutDisplayFunc(render);
    glutMainLoop();
}