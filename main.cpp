#include "Headers/Game.h"
#include <iostream>
#include <GL/glut.h>

Game *game;

void keyboard(int key, int x, int y)
{
    auto time = glutGet(GLUT_ELAPSED_TIME);
    game->keyboard(time, key, x, y);
}

void keyboard_up(int key, int x, int y)
{
    auto time = glutGet(GLUT_ELAPSED_TIME);
    game->keyboard_up(time, key, x, y);
}

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

    glutSwapBuffers();
}

void mouse(int button, int state, int x, int y)
{
    auto H = glutGet(GLUT_WINDOW_HEIGHT);
    std::cout << x << ' ' << H - y << std::endl;
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Pac-Man!");

    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 800.0, 0.0, 600.0);

    init();

    glutDisplayFunc(render);
    glutIdleFunc(render);
    glutSpecialFunc(keyboard);
    glutIgnoreKeyRepeat(1);
    glutSpecialUpFunc(keyboard_up);
    glutMouseFunc(mouse);
    glutMainLoop();

    delete game;
}