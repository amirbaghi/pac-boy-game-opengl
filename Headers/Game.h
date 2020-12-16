#include "Component.h"

class Enemy;
class MainCharacter;
class Obstacle;
class Terrain;

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
    Terrain *terrain;
    MainCharacter *mainCharacter;
};