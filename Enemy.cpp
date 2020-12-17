#include <iostream>
#include "Headers/Enemy.h"
#include "Headers/Game.h"
#include "Headers/Component.h"
#include "Headers/MainCharacter.h"

Enemy::Enemy(Component *parent) : Component(parent)
{
}

Enemy::~Enemy()
{
}

void Enemy::setInitialMotionPositionAndTime(int x, int y, int time)
{
    this->init_x = x;
    this->init_y = y;
    this->offset_x = 0;
    this->offset_y = 0;
    this->init_motion_time = time;
}

void Enemy::setDirection(Direction direction, int time)
{
    this->direction = direction;
    setInitialMotionPositionAndTime(this->init_x + this->offset_x, this->init_y + this->offset_y, time);
}

void Enemy::setFrame(int frame)
{
    this->current_frame = frame;
}

void Enemy::setInitialFrame(int frame)
{
    this->init_frame = frame;
}

void Enemy::load(int time)
{

    GLuint txid = SOIL_load_OGL_texture("sprite.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);

    this->texture_id = txid;

    // Setting a random direction in the beginning
    auto randDirection = 0 + (std::rand() % (4 - 0 + 1));

    setDirection((Direction)randDirection, time);

    // Setting a random intial frame
    auto randFrame = 0 + (std::rand() % (1 - 0 + 1));

    setInitialFrame(randFrame);
    setFrame(randFrame);
}

void Enemy::update(int time)
{

    auto diffTime = (time - this->init_motion_time) / 200;

    // Updating the x and y values based on the direction
    switch (this->direction)
    {
    case UP:
        this->offset_y = 9 * diffTime;
        break;
    case DOWN:
        this->offset_y = -9 * diffTime;
        break;
    case LEFT:
        this->offset_x = -9 * diffTime;
        break;
    case RIGHT:
        this->offset_x = 9 * diffTime;
        break;
    default:
        break;
    }

    // Updating the frame of the character
    this->current_frame = (this->init_frame + (1 * diffTime)) % 2;

    // Check for the main character in its col or row and turn towards it
    Game *game = dynamic_cast<Game *>(parent_component);
    MainCharacter *mainCharacter = game->getMainCharacter();
    // If the enemy and the character are in the same column
    if (abs((mainCharacter->getCurrentXPosition()) - (this->init_x + this->offset_x)) < 10)
    {
        // The main character is above
        if ((mainCharacter->getCurrentYPosition()) > (this->init_y + this->offset_y))
        {
            if (direction != UP)
            {
                setDirection(UP, time);
            }
        }
        // The main character is below
        else if ((mainCharacter->getCurrentYPosition()) < (this->init_y + this->offset_y))
        {
            if (direction != DOWN)
            {
                setDirection(DOWN, time);
            }
        }
    }

    // If the enemy and the character are in the same row
    else if (abs((mainCharacter->getCurrentYPosition()) - (this->init_y + this->offset_y)) < 10)
    {
        // The main character is to the right
        if ((mainCharacter->getCurrentXPosition()) > (this->init_x + this->offset_x))
        {
            if (direction != RIGHT)
            {
                setDirection(RIGHT, time);
            }
        }
        // The main character is below
        else if ((mainCharacter->getCurrentXPosition()) < (this->init_x + this->offset_x))
        {
            if (direction != LEFT)
            {
                setDirection(LEFT, time);
            }
        }
    }

    // TODO: check for collision with an obstacle and change Direction based on that and select a random starting frame

    // TODO: check for collision with the main character and end the game if so

    // Check if it's out of bounds or not
    if ((this->init_x + this->offset_x) >= 800.0)
    {
        setInitialMotionPositionAndTime(1, this->init_y + this->offset_y, time);
    }
    else if ((this->init_x + this->offset_x) <= 0.0)
    {
        setInitialMotionPositionAndTime(799, this->init_y + this->offset_y, time);
    }
    else if ((this->init_y + this->offset_y) >= 600.0)
    {
        setInitialMotionPositionAndTime(this->init_x + this->offset_x, 1, time);
    }
    else if ((this->init_y + this->offset_y) <= 0.0)
    {
        setInitialMotionPositionAndTime(this->init_x + this->offset_x, 599, time);
    }
}

void Enemy::render(int time)
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(this->offset_x + this->init_x, this->offset_y + this->init_y, 0);

    float spriteCol;

    switch (this->direction)
    {
    case RIGHT:
        spriteCol = 0;
        break;
    case LEFT:
        spriteCol = 2.0 / 14.0;
        break;
    case UP:
        spriteCol = 4.0 / 14.0;
        break;
    case DOWN:
        spriteCol = 6.0 / 14.0;
        break;
    default:
        break;
    }

    auto col_error = 1 / (6 * 14.0);
    auto row_error = 1 / (6 * 8.0);
    spriteCol += col_error;

    glBindTexture(GL_TEXTURE_2D, this->texture_id);
    glBegin(GL_QUADS);
    glTexCoord2f(spriteCol + (this->current_frame * 1 / 14.0), 3 / 8.0 + row_error);
    glVertex2f(-30 / 2.0, -30 / 2.0);
    glTexCoord2f(spriteCol + (this->current_frame * 1 / 14.0) + 1 / 14.0 - col_error, 3 / 8.0 + row_error);
    glVertex2f(30 / 2.0, -30 / 2.0);
    glTexCoord2f(spriteCol + (this->current_frame * 1 / 14.0) + 1 / 14.0 - col_error, 4 / 8.0);
    glVertex2f(30 / 2.0, 30 / 2.0);
    glTexCoord2f(spriteCol + (this->current_frame * 1 / 14.0), 4 / 8.0);
    glVertex2f(-30 / 2.0, 30 / 2.0);
    glEnd();

    glPopMatrix();
}
