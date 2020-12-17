#include "Headers/Point.h"


Point::Point(Component* parent):Component(parent)
{

}

Point::~Point()
{

}

void Point::setPosition(int x, int y)
{
    this->x = x;
    this->y = y;
}

void Point::load(int time)
{

    glEnable(GL_TEXTURE_2D);
    GLuint txid = SOIL_load_OGL_texture("point.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);

    this->texture_id = txid;
}

void Point::update(int time)
{

}

void Point::render(int time)
{
    glBindTexture(GL_TEXTURE_2D, this->texture_id);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex2f(this->x - 10, this->y - 10);
    glTexCoord2f(1, 0);
    glVertex2f(this->x + 10, this->y - 10);
    glTexCoord2f(1, 1);
    glVertex2f(this->x + 10, this->y + 10);
    glTexCoord2f(0, 1);
    glVertex2f(this->x - 10, this->y + 10);
    glEnd();
}

