#include "Component.h"

class Enemy;
class MainCharacter;
class Obstacle;
class Terrain;
class Point;

// Game class, inheriting from Component class
class Game : public Component
{
public:
    Game();
    ~Game();

    void load(int time);
    void update(int time);
    void render(int time);

private:
protected:
    std::vector<Enemy *> enemies;
    std::vector<Obstacle *> obstacles;
    std::vector<Point *> points;
    Terrain *terrain;
    MainCharacter *mainCharacter;
};