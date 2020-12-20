#include "Headers/MainCharacter.h"
#include "Headers/Game.h"
#include "Headers/Obstacle.h"
#include "Headers/Point.h"
#include "Headers/Utils.h"
#include "Headers/Score.h"
#include "Headers/GameState.h"
#include <iostream>
#include <ctime>

MainCharacter::MainCharacter(Component *parent) : Component(parent)
{
}

MainCharacter::~MainCharacter()
{
}

int MainCharacter::getCurrentXPosition()
{
    return (this->init_x + this->offset_x);
}

int MainCharacter::getCurrentYPosition()
{
    return (this->init_y + this->offset_y);
}

void MainCharacter::setInitialMotionPositionAndTime(int x, int y, int time)
{
    this->init_x = x;
    this->init_y = y;
    this->offset_x = 0;
    this->offset_y = 0;
    this->init_motion_time = time;
}

void MainCharacter::setDirection(Direction direction, int time)
{
    this->direction = direction;
    setInitialMotionPositionAndTime(this->init_x + this->offset_x, this->init_y + this->offset_y, time);
}

void MainCharacter::setInitialFrame(int frame)
{
    this->init_frame = frame;
}

void MainCharacter::setFrame(int frame)
{
    this->current_frame = frame;
}

void MainCharacter::setMotionState(MotionState newMotionState)
{
    this->motionState = newMotionState;
}

void MainCharacter::up(int time)
{
    this->motionState = MOVING;
    this->setDirection(UP, time);

}

void MainCharacter::down(int time)
{
    this->motionState = MOVING;
    this->setDirection(DOWN, time);

}

void MainCharacter::right(int time)
{
    this->motionState = MOVING;
    this->setDirection(RIGHT, time);

}

void MainCharacter::left(int time)
{
    this->motionState = MOVING;
    this->setDirection(LEFT, time);

}

void MainCharacter::stop(int time)
{
    this->motionState = STANDING;
}

void MainCharacter::load(int time)
{
    GLuint txid = SOIL_load_OGL_texture("Resources/character_sprite.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);

    this->texture_id = txid;

    // Setting a random direction in the beginning
    std::srand((unsigned int)std::time(NULL));
    auto randDirection = 0 + (std::rand() % (3 - 0 + 1));

    setDirection((Direction)randDirection, time);

    // Setting the motion state as Standing in the beginning
    this->motionState = STANDING;

    // Setting an intial state
    setInitialFrame(0);
    setFrame(0);
}

void MainCharacter::update(int time)
{
    if (this->motionState == MOVING)
    {
        auto diffTime = (time - this->init_motion_time) / 185;

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

        Game *game = dynamic_cast<Game *>(parent_component);
        std::vector<Obstacle *> obstacles = game->getObstacles();
        std::vector<Point *> points = game->getPoints();
        Score *score = game->getScore();

        // Check for collision with an obstacle

        auto width = 30;
        auto height = 30;

        for (auto obs = obstacles.begin(); obs < obstacles.end(); obs++)
        {
            auto width2 = (*obs)->getX2() - (*obs)->getX1();
            auto height2 = (*obs)->getY2() - (*obs)->getY1();

            if (Utils::collision((this->init_x + this->offset_x) - 12, (this->init_y + this->offset_y) - 12, width,
                                 height, (*obs)->getX1(), (*obs)->getY1(), width2, height2))
            {
                switch (direction)
                {
                case UP:
                    this->init_y = (this->init_y + this->offset_y) - 8;
                    this->offset_y = 0;
                    break;
                case DOWN:
                    this->init_y = (this->init_y + this->offset_y) + 8;
                    this->offset_y = 0;
                    break;
                case RIGHT:
                    this->init_x = (this->init_x + this->offset_x) - 8;
                    this->offset_x = 0;
                    break;
                case LEFT:
                    this->init_x = (this->init_x + this->offset_x) + 8;
                    this->offset_x = 0;
                    break;
                default:
                    break;
                }
                stop(time);
                break;
            }
        }

        // Check for collision with a point, if found, remove the point from the points list and add to score
        // Also if the points are all taken, set the state of the game to END_WIN
        if (!points.empty())
        {
            for (auto point = points.end() - 1; point >= points.begin(); point--)
            {
                if (Utils::collision((this->init_x + this->offset_x) - 15, (this->init_y + this->offset_y) - 15, 30, 30,
                                     (*point)->getXPosition() + 5, (*point)->getYPosition() + 5, 10, 10))
                {
                    point = points.erase(point);
                    if (points.empty())
                    {
                        game->setGameState(END_WIN);
                    }
                    score->setScore(score->getScore() + 1);
                    game->setPoints(points);                
                    break;
                }
            }
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
    else if (this->motionState == STANDING)
    {
        setInitialFrame(1);
        setFrame(1);
    }
}

void MainCharacter::render(int time)
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(this->offset_x + this->init_x, this->offset_y + this->init_y, 0);

    float spriteRow;

    switch (this->direction)
    {
    case RIGHT:
        spriteRow = 7.0 / 8.0;
        break;
    case LEFT:
        spriteRow = 6.0 / 8.0;
        break;
    case UP:
        spriteRow = 5.0 / 8.0;
        break;
    case DOWN:
        spriteRow = 4.0 / 8.0;
        break;
    default:
        break;
    }

    auto col_error = 1 / (6 * 14.0);
    auto row_error = 1 / (6 * 8.0);

    glBindTexture(GL_TEXTURE_2D, this->texture_id);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0 + (this->current_frame * 1 / 14.0) + col_error, spriteRow + row_error);
    glVertex2f(-30 / 2.0, -30 / 2.0);
    glTexCoord2f(0.0 + (this->current_frame * 1 / 14.0) + 1 / 14.0, spriteRow + row_error);
    glVertex2f(30 / 2.0, -30 / 2.0);
    glTexCoord2f(0.0 + (this->current_frame * 1 / 14.0) + 1 / 14.0, spriteRow + 1 / 8.0);
    glVertex2f(30 / 2.0, 30 / 2.0);
    glTexCoord2f(0.0 + (this->current_frame * 1 / 14.0) + col_error, spriteRow + 1 / 8.0);
    glVertex2f(-30 / 2.0, 30 / 2.0);
    glEnd();

    glPopMatrix();
}