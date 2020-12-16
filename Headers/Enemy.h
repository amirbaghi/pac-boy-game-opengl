#include "Component.h"
#include "Direction.h"

class Enemy : public Component
{
public:
    Enemy(Component* parent);
    ~Enemy();

    void load(int time);
    void update(int time);
    void render(int time);

    // Method to set the initial position of the character
    void setInitialPosition(int x, int y); 
    // Method to change the direction of the character
    void changeDirection(Direction direction);

private:
    // Current Position of the character
    int x, y;
    // Initial Frame, and the Current Frame of the character
    int init_frame, current_frame;
    // Direction of the character
    Direction direction;
    // Texture id of the character
    GLuint texture_id;

protected:
};