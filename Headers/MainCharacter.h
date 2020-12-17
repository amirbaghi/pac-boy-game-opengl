#ifndef MAIN_CHARACTER_H
#define MAIN_CHARACTER_H
#include "Component.h"
#include "Direction.h"
#include "MotionState.h"

class MainCharacter : public Component
{
public:
    MainCharacter(Component *parent);
    ~MainCharacter();

    void load(int time);
    void update(int time);
    void render(int time);


    // Method to set the initial position of the character (Also sets the initial time of the motion)
    void setInitialMotionPositionAndTime(int x, int y, int time); 
    // Method to set the direction of the character, also calls the setInitialMotionPositionAndTime to change the initial motion factors
    void setDirection(Direction direction, int time);
    // Method to set the initial frame
    void setInitialFrame(int frame);
    // Method to set the frame of the character
    void setFrame(int frame);
    // Method to change the motion state of the character
    void setMotionState(MotionState newMotionState);

    // Methods to handle events related to the character's movement
    void up(int time);
    void down(int time);
    void left(int time);
    void right(int time);
    void stop(int time);

private:
    // Initial position in the beginning of the current motion
    int init_x, init_y;
    // Current offset from the initial position in the current motion
    int offset_x, offset_y;
    // Initial time of the start of the current motion
    int init_motion_time;
    // Initial Frame, and the Current Frame of the character (Either 0 or 1)
    int init_frame, current_frame;
    // Direction of the character
    Direction direction;
    // Character's motion state (Standing or Moving)
    MotionState motionState;
    // Texture id of the character
    GLuint texture_id;

protected:
};

#endif