#include "Headers/Obstacle.h"

Obstacle::Obstacle(Component* parent) : Component(parent)
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

void Obstacle::setPosition(int x1, int y1, int x2, int y2)
{
    this->x1 = x1;
    this->y1 = y1;
    this->x2 = x2;
    this->y2 = y2;
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
    glBindTexture(GL_TEXTURE_2D, this->texture_id);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex2f(this->x1, this->y1);
    glTexCoord2f(1, 0);
    glVertex2f(this->x2, this->y1);
    glTexCoord2f(1, 1);
    glVertex2f(this->x2, this->y2);
    glTexCoord2f(0, 1);
    glVertex2f(this->x1, this->y2);
    glEnd();
}