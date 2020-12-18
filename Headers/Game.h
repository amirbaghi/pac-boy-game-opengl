#ifndef GAME_H
#define GAME_H
#include "Component.h"

class Enemy;
class MainCharacter;
class Obstacle;
class Terrain;
class Point;
class Score;

// Game class, inheriting from Component class
class Game : public Component
{
public:
    Game();
    ~Game();

    void load(int time);
    void update(int time);
    void render(int time);

    // Method to generate obstacles
    void generateObstacles();
    // Method to generate points
    void generatePoints();

    // MainCharacter Getter
    MainCharacter *getMainCharacter();
    // Obstacles Getter
    std::vector<Obstacle *> getObstacles();
    // Points Getter
    std::vector<Point *> getPoints();
    // Score Getter
    Score *getScore();

    // Points Setter
    void setPoints(std::vector<Point *> points);

    // Event handling methods
    void keyboard(int time, int key, int x, int y);
    void keyboard_up(int time, int key, int x, int y);

private:
protected:
    std::vector<Enemy *> enemies;
    std::vector<Obstacle *> obstacles;
    std::vector<Point *> points;
    Score *score;
    Terrain *terrain;
    MainCharacter *mainCharacter;
};

#endif