#include <vector>
#include <GL/glut.h>

class Game;

// Component Class
class Component
{
public:
    Component(Component *parent);

    // Main methods for each component
    void virtual load(int time);
    void virtual update(int time) = 0;
    void virtual render(int time) = 0;

private:
protected:
    // Time of the component's creation
    int created_time;
    // Pointer to the game object
    Game *game;
    // Pointer to the parent component
    Component *parent_component;
};
