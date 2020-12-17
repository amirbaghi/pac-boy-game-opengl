#include "Headers/Terrain.h"

Terrain::Terrain(Component* parent) : Component(parent)
{

}

Terrain::~Terrain()
{

}

void Terrain::load(int time)
{
    int width, height;

    auto texture_data = SOIL_load_image("Resources/tile.png", &width, &height, 0, SOIL_LOAD_RGBA);

    GLuint txid;

    glEnable(GL_TEXTURE_2D);
    glGenTextures(1, &txid);
    glBindTexture(GL_TEXTURE_2D, txid);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture_data);

    this->texture_id = txid;

}

void Terrain::update(int time)
{

}

void Terrain::render(int time)
{
    glBindTexture(GL_TEXTURE_2D, this->texture_id);
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
}