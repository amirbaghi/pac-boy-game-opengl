#include <iostream>
#include <ctime>
#include "Headers/Direction.h"
#include "Headers/Enemy.h"
#include "Headers/Game.h"
#include "Headers/Component.h"
#include "Headers/MainCharacter.h"
#include "Headers/Obstacle.h"
#include "Headers/Utils.h"

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

void Enemy::setColor(Color color)
{
    this->color = color;
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

    GLuint txid = SOIL_load_OGL_texture("character_sprite.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);

    this->texture_id = txid;

    // Setting a random direction in the beginning
    auto randDirection = 0 + (std::rand() % (3 - 0 + 1));

    setDirection((Direction)randDirection, time);

    // Setting a random color
    auto randColor = (std::rand() % (3 - 0 + 1));
    setColor((Color)randColor);

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
        this->offset_y = 6 * diffTime;
        break;
    case DOWN:
        this->offset_y = -6 * diffTime;
        break;
    case LEFT:
        this->offset_x = -6 * diffTime;
        break;
    case RIGHT:
        this->offset_x = 6 * diffTime;
        break;
    default:
        break;
    }

    // Updating the frame of the character
    this->current_frame = (this->init_frame + (3 * diffTime)) % 2;

    Game *game = dynamic_cast<Game *>(parent_component);
    std::vector<Obstacle *> obstacles = game->getObstacles();
    MainCharacter *mainCharacter = game->getMainCharacter();

    // Check for the main character in its col or row and turn towards it, if there is no obstacle between them

    bool shouldChangeDirection = true;

    // If the enemy and the character are in the same column (Considering their widths)
    if (abs((mainCharacter->getCurrentXPosition()) - (this->init_x + this->offset_x)) < 10)
    {
        // The main character is above
        if ((mainCharacter->getCurrentYPosition()) > (this->init_y + this->offset_y))
        {
            if (direction != UP)
            {
                // Checking for obstacles between them, and if there is one, we shouldnt change direction
                for (auto obs = obstacles.begin(); obs < obstacles.end(); obs++)
                {
                    auto height2 = (*obs)->getY2() - (*obs)->getY1();

                    if (((*obs)->getY1() + height2 / 2.0) >= (this->init_y + this->offset_y) && (((*obs)->getY1() + height2 / 2.0) <= mainCharacter->getCurrentYPosition()))
                    {
                        if (((*obs)->getX1() <= (this->init_x + this->offset_x)) && ((this->init_x + this->offset_x) <= (*obs)->getX2()))
                        {
                            shouldChangeDirection = false;
                            break;
                        }
                    }
                }
                if (shouldChangeDirection)
                {
                    setDirection(UP, time);
                }
            }
        }
        // The main character is below
        else if ((mainCharacter->getCurrentYPosition()) < (this->init_y + this->offset_y))
        {
            if (direction != DOWN)
            {
                // Checking for obstacles between them, and if there is one, we shouldnt change direction
                for (auto obs = obstacles.begin(); obs < obstacles.end(); obs++)
                {
                    auto height2 = (*obs)->getY2() - (*obs)->getY1();

                    if ((((*obs)->getY1() + height2 / 2.0) <= (this->init_y + this->offset_y)) && (((*obs)->getY1() + height2 / 2.0) >= mainCharacter->getCurrentYPosition()))
                    {
                        if (((*obs)->getX1() <= (this->init_x + this->offset_x)) && ((this->init_x + this->offset_x) <= (*obs)->getX2()))
                        {
                            shouldChangeDirection = false;
                            break;
                        }
                    }
                }
                if (shouldChangeDirection)
                {
                    setDirection(DOWN, time);
                }
            }
        }
    }

    // If the enemy and the character are in the same row (Considering their widths)
    else if (abs((mainCharacter->getCurrentYPosition()) - (this->init_y + this->offset_y)) < 10)
    {
        // The main character is to the right
        if ((mainCharacter->getCurrentXPosition()) > (this->init_x + this->offset_x))
        {
            if (direction != RIGHT)
            {
                // Checking for obstacles between them, and if there is one, we shouldnt change direction
                for (auto obs = obstacles.begin(); obs < obstacles.end(); obs++)
                {
                    auto width2 = (*obs)->getX2() - (*obs)->getX1();

                    if (((*obs)->getX1() + width2 / 2.0) >= (this->init_x + this->offset_x) && (((*obs)->getX1() + width2 / 2.0) <= mainCharacter->getCurrentXPosition()))
                    {
                        if (((*obs)->getY1() <= (this->init_y + this->offset_y)) && ((this->init_y + this->offset_y) <= (*obs)->getY2()))
                        {
                            shouldChangeDirection = false;
                            break;
                        }
                    }
                }
                if (shouldChangeDirection)
                {
                    setDirection(RIGHT, time);
                }
            }
        }
        // The main character is below
        else if ((mainCharacter->getCurrentXPosition()) < (this->init_x + this->offset_x))
        {
            if (direction != LEFT)
            {
                // Checking for obstacles between them, and if there is one, we shouldnt change direction
                for (auto obs = obstacles.begin(); obs < obstacles.end(); obs++)
                {
                    auto width2 = (*obs)->getX2() - (*obs)->getX1();

                    if ((((*obs)->getX1() + width2 / 2.0) <= (this->init_x + this->offset_x)) && (((*obs)->getX1() + width2 / 2.0) >= mainCharacter->getCurrentXPosition()))
                    {
                        if (((*obs)->getY1() <= (this->init_y + this->offset_y)) && ((this->init_y + this->offset_y) <= (*obs)->getY2()))
                        {
                            shouldChangeDirection = false;
                            break;
                        }
                    }
                }
                if (shouldChangeDirection)
                {
                    setDirection(LEFT, time);
                }
            }
        }
    }

    // Check for collision with an obstacle and change Direction based on that

    auto width = 30;
    auto height = 30;

    for (auto obs = obstacles.begin(); obs < obstacles.end(); obs++)
    {
        auto width2 = (*obs)->getX2() - (*obs)->getX1();
        auto height2 = (*obs)->getY2() - (*obs)->getY1();

        if (Utils::collision((this->init_x + this->offset_x) - 12, (this->init_y + this->offset_y) - 12, width,
                             height, (*obs)->getX1(), (*obs)->getY1(), width2, height2))
        {
            bool sameDirection;
            int newDir;

            switch (direction)
            {
            case UP:
                this->init_y = (this->init_y + this->offset_y) - 8;
                this->offset_y = 0;

                // Choosing a new random direction that is not the same as the one before
                do
                {
                    newDir = 0 + (std::rand() % (3 - 0 + 1));

                    sameDirection = false;
                    if (newDir == UP)
                        sameDirection = true;

                } while (sameDirection);

                setDirection((Direction)newDir, time);
                break;
            case DOWN:
                this->init_y = (this->init_y + this->offset_y) + 8;
                this->offset_y = 0;

                // Choosing a new random direction that is not the same as the one before
                do
                {
                    newDir = 0 + (std::rand() % (3 - 0 + 1));

                    sameDirection = false;
                    if (newDir == DOWN)
                        sameDirection = true;

                } while (sameDirection);

                setDirection((Direction)newDir, time);
                break;
            case RIGHT:
                this->init_x = (this->init_x + this->offset_x) - 8;
                this->offset_x = 0;

                // Choosing a new random direction that is not the same as the one before
                do
                {
                    newDir = 0 + (std::rand() % (3 - 0 + 1));

                    sameDirection = false;
                    if (newDir == RIGHT)
                        sameDirection = true;

                } while (sameDirection);

                setDirection((Direction)newDir, time);
                break;
            case LEFT:
                this->init_x = (this->init_x + this->offset_x) + 8;
                this->offset_x = 0;

                // Choosing a new random direction that is not the same as the one before
                do
                {
                    newDir = 0 + (std::rand() % (3 - 0 + 1));

                    sameDirection = false;
                    if (newDir == LEFT)
                        sameDirection = true;

                } while (sameDirection);

                setDirection((Direction)newDir, time);
                break;
            default:
                break;
            }
            break;
        }
    }

    // Check for collision with the main character and end the game if so
    if (Utils::collision((this->init_x + this->offset_x) - 12, (this->init_y + this->offset_y) - 12, width,
                             height, mainCharacter->getCurrentXPosition(), mainCharacter->getCurrentYPosition(), 12, 12))
    {
        game->setGameState(END_LOSE);
    }

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

    float spriteCol, spriteRow;

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

    switch (this->color)
    {
    case YELLOW:
        spriteRow = 0;
        break;
    case CYAN:
        spriteRow = 1;
        break;
    case PINK:
        spriteRow = 2;
        break;
    case RED:
        spriteRow = 3;
        break;    
    default:
        break;
    }

    auto col_error = 1 / (6 * 14.0);
    auto row_error = 1 / (6 * 8.0);
    spriteCol += col_error;

    glBindTexture(GL_TEXTURE_2D, this->texture_id);
    glBegin(GL_QUADS);
    glTexCoord2f(spriteCol + (this->current_frame * 1 / 14.0), (spriteRow * 1 / 8.0) + row_error);
    glVertex2f(-30 / 2.0, -30 / 2.0);
    glTexCoord2f(spriteCol + (this->current_frame * 1 / 14.0) + 1 / 14.0 - col_error, (spriteRow * 1 / 8.0) + row_error);
    glVertex2f(30 / 2.0, -30 / 2.0);
    glTexCoord2f(spriteCol + (this->current_frame * 1 / 14.0) + 1 / 14.0 - col_error, (spriteRow * 1 / 8.0) + 1 / 8.0 );
    glVertex2f(30 / 2.0, 30 / 2.0);
    glTexCoord2f(spriteCol + (this->current_frame * 1 / 14.0), (spriteRow * 1 / 8.0) + 1 / 8.0);
    glVertex2f(-30 / 2.0, 30 / 2.0);
    glEnd();

    glPopMatrix();
}
