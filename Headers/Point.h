#include "Component.h"

class Point : public Component
{
public:

    Point(Component* parent);
    ~Point();

    void load(int time);
    void update(int time);
    void render(int time);

    // Set the position of the point
    void setPosition(int x, int y);

private:
    // Position of the point
    int x, y;
    // The texture id of the point
    GLuint texture_id;

protected:
};