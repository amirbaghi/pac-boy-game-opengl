#include "Headers/Terrain.h"

Terrain::Terrain(Component* parent) : Component(parent)
{

}

Terrain::~Terrain()
{

}

void Terrain::load(int time)
{

    GLuint txid = SOIL_load_OGL_texture("tile.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);

    this->texture_id = txid;

}

void Terrain::update(int time)
{

}

void Terrain::render(int time)
{
    glBindTexture(GL_TEXTURE_2D, this->texture_id);

    glColor4f(0.2, 0.0, 0.5, 0.5);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex2f(0.0, 0.0);
    glTexCoord2f(1, 0);
    glVertex2f(800.0, 0.0);
    glTexCoord2f(1, 1);
    glVertex2f(800.0, 600.0);
    glTexCoord2f(0, 1);
    glVertex2f(0.0, 600.0);
    glEnd();
    
    glColor4f(1.0, 1.0, 1.0, 1.0);
}