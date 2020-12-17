#include "Headers/Game.h"
#include "Headers/MainCharacter.h"
#include "Headers/Terrain.h"
#include "Headers/Enemy.h"
#include "Headers/Obstacle.h"
#include "Headers/Point.h"

Game::Game() : Component(NULL)
{
    this->game = this;
}

Game::~Game()
{
}

void Game::load(int time)
{

    // MainCharacter *mainCharacter = new MainCharacter(this);
    // mainCharacter->setInitialPosition(500, 500);
    // this->mainCharacter = mainCharacter;
    // mainCharacter->load(time);

    Terrain *terrain = new Terrain(this);
    terrain->load(time);
    this->terrain = terrain;

    Enemy *enemy1 = new Enemy(this);
    enemy1->setInitialMotionPositionAndTime(200, 200, time);
    this->enemies.push_back(enemy1);

    Enemy *enemy2 = new Enemy(this);
    enemy2->setInitialMotionPositionAndTime(400, 400, time);
    this->enemies.push_back(enemy2);

    Obstacle *obstacle1 = new Obstacle(this);
    obstacle1->setPosition(90, 90, 120, 120);
    this->obstacles.push_back(obstacle1);

    Point *point1 = new Point(this);
    point1->setPosition(300, 300);
    this->points.push_back(point1);


    for (auto enemy = this->enemies.begin(); enemy < this->enemies.end(); enemy++)
        (*enemy)->load(time);

    for (auto obs = this->obstacles.begin(); obs < this->obstacles.end(); obs++)
        (*obs)->load(time);
    
    for (auto point = this->points.begin(); point < this->points.end(); point++)
        (*point)->load(time);
    
}

void Game::update(int time)
{
    // mainCharacter->update(time);
    terrain->update(time);

    for (auto enemy = this->enemies.begin(); enemy < this->enemies.end(); enemy++)
        (*enemy)->update(time);

    for (auto obs = this->obstacles.begin(); obs < this->obstacles.end(); obs++)
        (*obs)->update(time);

    for (auto point = this->points.begin(); point < this->points.end(); point++)
        (*point)->update(time);
}

void Game::render(int time)
{
    terrain->render(time);
    // mainCharacter->render(time);

    for (auto enemy = this->enemies.begin(); enemy < this->enemies.end(); enemy++)
        (*enemy)->render(time);

    for (auto obs = this->obstacles.begin(); obs < this->obstacles.end(); obs++)
        (*obs)->render(time);

    for (auto point = this->points.begin(); point < this->points.end(); point++)
        (*point)->render(time);
}

