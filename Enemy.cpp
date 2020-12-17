#include "Headers/Enemy.h"

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

void Enemy::setDirection(Direction direction)
{
    auto time = glutGet(GLUT_ELAPSED_TIME);
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
    int width, height;

    auto texture_data = SOIL_load_image("general_sprite_sheet.png", &width, &height, 0, SOIL_LOAD_RGBA);

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

    // Setting a random direction in the beginning
    auto randDirection = 0 + (std::rand() % (4 - 0 + 1));

    setDirection((Direction)randDirection);

    // Setting a random intial frame
    auto randFrame = 1 + (std::rand() % (2 - 1 + 1));

    setInitialFrame(randFrame);
    setFrame(randFrame);
}

void Enemy::update(int time)
{

    auto diffTime = (time - this->init_motion_time) / 1000;

    // Updating the x and y values based on the direction
    switch (this->direction)
    {
    case UP:
        this->offset_y = 4 * diffTime;
        break;
    case DOWN:
        this->offset_y = -4 * diffTime;
        break;
    case LEFT:
        this->offset_x = -4 * diffTime;
        break;
    case RIGHT:
        this->offset_x = 4 * diffTime;
        break;
    default:
        break;
    }

    // Updating the frame of the character
    this->current_frame = (this->init_frame + (1 * diffTime)) % 2;

    // TODO: check for collision with an obstacle and change Direction based on that and select a random starting frame

    // TODO: check for collision with the main character and end the game if so
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
        spriteCol = 2/14.0;
        break;
    case UP:
        spriteCol = 4/14.0;
        break;
    case DOWN:
        spriteCol = 6/14.0;
        break;
    default:
        break;
    }
    glBindTexture(GL_TEXTURE_2D, this->texture_id);
    glBegin(GL_QUADS);
    glTexCoord2f(spriteCol + (this->current_frame * 1/14.0), 3/8.0);
    glVertex2f(-10/ 2.0, -10/ 2.0);
    glTexCoord2f(spriteCol + (this->current_frame * 1/14.0) + 1/14.0, 3/8.0);
    glVertex2f(10 / 2.0, -10/ 2.0);
    glTexCoord2f(spriteCol + (this->current_frame * 1/14.0) + 1/14.0, 4/8.0);
    glVertex2f(10 / 2.0, 10 / 2.0);
    glTexCoord2f(spriteCol + (this->current_frame * 1/14.0), 4/8.0);
    glVertex2f(-10 / 2.0, 10 / 2.0);
    glEnd();

    glPopMatrix();
}
