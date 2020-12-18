#ifndef OBSTACLE_H
#define OBSTACLE_H
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

    // x1 Getter 
    int getX1();
    // y1 Getter
    int getY1();
    // x2 Getter
    int getX2();
    // y2 Getter
    int getY2();

    // Method to set the position of this obstacle and the alignment of it 
    void setPosition(int x1, int y1, int x2, int y2, bool isVertical);

private:
    // Lower-left corner of the rectangle (x1, y1) and the upper-right one (x2, y2)
    int x1, x2, y1, y2;
    // Is to be placed vertical or horizontal
    bool isVertical;
    // Texture id of the obstacle
    GLuint texture_id;

protected:
};

#endif