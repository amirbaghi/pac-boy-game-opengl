#include "Component.h"

// Obstacle Component, inheriting from Component class
class Obstacle : public Component
{
public:
    Obstacle(Component *parent);
    ~Obstacle();

    void load(int time);
    void update(int time);
    void render(int time);
    // Method to set the position of this obstacle
    void setPosition(int x1, int y1, int x2, int y2);

private:
    // Lower-left corner of the rectangle (x1, y1) and the upper-right one (x2, y2)
    int x1, x2, y1, y2;
    // Texture id of the obstacle
    GLuint texture_id;

protected:
};