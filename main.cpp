#include "Headers/Game.h"
#include <GL/glut.h>

Game* game;

void init()
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    game = new Game();

    auto time = glutGet(GLUT_ELAPSED_TIME);

    game->load(time);

}

void render()
{
    glClear(GL_COLOR_BUFFER_BIT);

    auto time = glutGet(GLUT_ELAPSED_TIME);

    game->update(time);
    game->render(time);

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

    init();

    glutDisplayFunc(render);
    glutIdleFunc(render);
    glutMainLoop();

    delete game;
}