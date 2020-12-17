#include "Headers/MainCharacter.h"

MainCharacter::MainCharacter(Component *parent) : Component(parent)
{
}

MainCharacter::~MainCharacter()
{
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

    //TODO: Maybe randomize init frame?
}

void MainCharacter::down(int time)
{
    this->motionState = MOVING;
    this->setDirection(DOWN, time);

    //TODO: Maybe randomize init frame?
}

void MainCharacter::right(int time)
{
    this->motionState = MOVING;
    this->setDirection(RIGHT, time);

    //TODO: Maybe randomize init frame?
}

void MainCharacter::left(int time)
{
    this->motionState = MOVING;
    this->setDirection(LEFT, time);

    //TODO: Maybe randomize init frame?
}

void MainCharacter::stop(int time)
{
    this->motionState = STANDING;
}

void MainCharacter::load(int time)
{
    GLuint txid = SOIL_load_OGL_texture("sprite.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);

    this->texture_id = txid;

    // Setting a random direction in the beginning
    auto randDirection = 0 + (std::rand() % (4 - 0 + 1));

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

        // TODO: check for collision with an obstacle 

        // TODO: check for collision with a point and add to score

        // TODO: check if it's out of bounds or not
    }
    else if (this->motionState == STANDING)
    {
        setInitialFrame(0);
        setFrame(0);
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
        spriteRow = 7.0/8.0;
        break;
    case LEFT:
        spriteRow = 6.0/8.0;
        break;
    case UP:
        spriteRow = 5.0/8.0;
        break;
    case DOWN:
        spriteRow = 4.0/8.0;
        break;
    default:
        break;
    }

    auto col_error = 1/(6*14.0); 
    auto row_error = 1/(6*8.0);
    // spriteCol += col_error;


    glBindTexture(GL_TEXTURE_2D, this->texture_id);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0 + (this->current_frame * 1/14.0) + col_error, spriteRow + row_error);
    glVertex2f(-30/ 2.0, -30/ 2.0);
    glTexCoord2f(0.0 + (this->current_frame * 1/14.0) + 1/14.0, spriteRow + row_error);
    glVertex2f(30 / 2.0, -30/ 2.0);
    glTexCoord2f(0.0 + (this->current_frame * 1/14.0) + 1/14.0, spriteRow + 1/8.0);
    glVertex2f(30 / 2.0, 30 / 2.0);
    glTexCoord2f(0.0 + (this->current_frame * 1/14.0) + col_error, spriteRow + 1/8.0);
    glVertex2f(-30 / 2.0, 30 / 2.0);
    glEnd();

    glPopMatrix();
}