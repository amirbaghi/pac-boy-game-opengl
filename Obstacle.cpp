#include "Headers/Obstacle.h"

#define M_PI 3.14159265358979323846

Obstacle::Obstacle(Component *parent) : Component(parent)
{
}

Obstacle::~Obstacle()
{
}

int Obstacle::getX1()
{
    return x1;
}

int Obstacle::getY1()
{
    return y1;
}

int Obstacle::getX2()
{
    return x2;
}

int Obstacle::getY2()
{
    return y2;
}

void Obstacle::setPosition(int x1, int y1, int x2, int y2, bool isVertical)
{
    this->x1 = x1;
    this->y1 = y1;
    this->x2 = x2;
    this->y2 = y2;
    this->isVertical = isVertical;
}

void Obstacle::load(int time)
{

    GLuint txid = SOIL_load_OGL_texture("bricks.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);

    this->texture_id = txid;
}

void Obstacle::update(int time)
{
}

void Obstacle::render(int time)
{
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, this->texture_id);

    if (isVertical)
    {

        auto width = this->y2 - this->y1;
        auto height = this->x2 - this->x1;

        glTranslatef(this->x1, this->y2, 0.0);
        glRotatef(-90.0, 0.0, 0.0, 1.0);
        glBegin(GL_QUADS);
        glTexCoord2f(0, 0);
        glVertex2f(0, 0);
        glTexCoord2f(1, 0);
        glVertex2f(width, 0);
        glTexCoord2f(1, 1);
        glVertex2f(width, height);
        glTexCoord2f(0, 1);
        glVertex2f(0, height);
        glEnd();
    }
    else
    {
        auto width = this->x2 - this->x1;
        auto height = this->y2 - this->y1;

        glTranslatef(this->x1, this->y1, 0.0);
        glBegin(GL_QUADS);
        glTexCoord2f(0, 0);
        glVertex2f(0, 0);
        glTexCoord2f(1, 0);
        glVertex2f(width, 0);
        glTexCoord2f(1, 1);
        glVertex2f(width, height);
        glTexCoord2f(0, 1);
        glVertex2f(0, height);
        glEnd();
    }

    glPopMatrix();
}