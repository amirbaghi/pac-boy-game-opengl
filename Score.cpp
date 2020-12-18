#include "Headers/Score.h"
#include <iostream>
#include <string>

Score::Score(Component *parent) : Component(parent)
{
}

Score::~Score()
{
}

int Score::getScore()
{
    return this->score;
}

void Score::setScore(int score)
{
    this->score = score;
}

void Score::load(int time)
{
    // Set initial score to 0
    this->score = 0;

    // Load texture
    GLuint txid = SOIL_load_OGL_texture("text_sprite.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);

    this->texture_id = txid;
}

void Score::update(int time)
{
}

void Score::render(int time)
{

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    std::string num = std::to_string(this->score);

    auto col_error = 1 / (7 * 16.0);
    auto row_error = 1 / (6 * 28.0);
    int count = 0;

    for (auto it = num.begin(); it < num.end(); it++, count++)
    {
        glPushMatrix();
        glTranslatef(700 + (17 * count), 570, 0);
        glBindTexture(GL_TEXTURE_2D, this->texture_id);
        glBegin(GL_QUADS);
        glTexCoord2f(((*it) - '0') * (1 / 16.0) + col_error, 1 / 28.0 + row_error);
        glVertex2f(-17 / 2.0, -17 / 2.0);
        glTexCoord2f(((*it) - '0') * (1 / 16.0) + 1 / 16.0, 1 / 28.0 + row_error);
        glVertex2f(17 / 2.0, -17 / 2.0);
        glTexCoord2f(((*it) - '0') * (1 / 16.0) + 1 / 16.0, 2 / 28.0);
        glVertex2f(17 / 2.0, 17 / 2.0);
        glTexCoord2f(((*it) - '0') * (1 / 16.0) + col_error, 2 / 28.0);
        glVertex2f(-17 / 2.0, 17 / 2.0);
        glEnd();
        glPopMatrix();
    }
}