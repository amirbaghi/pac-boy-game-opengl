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

    // Method to set the initial position of the character
    void setInitialPosition(int x, int y);
    // Method to change the motion state of the character
    void changeMotionState(MotionState newMotionState);
    // Method to change the direction of the character
    void changeDirection(Direction direction);

private:
    // Current Position of the character
    int x, y;
    // Initial Frame, and the Current Frame of the character
    int init_frame, current_frame;
    // Direction of the character
    Direction direction;
    // Character's motion state (Standing or Moving)
    MotionState motionState;
    // Texture id of the character
    GLuint texture_id;

protected:
};