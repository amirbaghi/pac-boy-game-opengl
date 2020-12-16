#include "Headers/Game.h"
#include "Headers/MainCharacter.h"
#include "Headers/Terrain.h"
#include "Headers/Enemy.h"
#include "Headers/Obstacle.h"

Game::Game() : Component(NULL)
{
    auto time = glutGet(GLUT_ELAPSED_TIME);
    this->game = this;
    this->created_time = time;
}

Game::~Game()
{
}

void Game::load(int time)
{

    MainCharacter *mainCharacter = new MainCharacter(this);
    mainCharacter->setInitialPosition(500, 500);
    this->mainCharacter = mainCharacter;
    mainCharacter->load(time);

    Terrain *terrain = new Terrain(this);
    terrain->load(time);

    Enemy *enemy1 = new Enemy(this);
    enemy1->setInitialPosition(200, 200);
    this->enemies.push_back(enemy1);

    Enemy *enemy2 = new Enemy(this);
    enemy2->setInitialPosition(200, 200);
    this->enemies.push_back(enemy2);

    Obstacle *obstacle1 = new Obstacle(this);
    obstacle1->setPosition(90, 90, 100, 100);
    this->obstacles.push_back(obstacle1);

    for (auto enemy = this->enemies.begin(); enemy < this->enemies.end(); enemy++)
        (*enemy)->load(time);

    for (auto obs = this->obstacles.begin(); obs < this->obstacles.end(); obs++)
        (*obs)->load(time);
    
}

void Game::update(int time)
{
    mainCharacter->update(time);
    terrain->update(time);

    for (auto enemy = this->enemies.begin(); enemy < this->enemies.end(); enemy++)
        (*enemy)->update(time);

    for (auto obs = this->obstacles.begin(); obs < this->obstacles.end(); obs++)
        (*obs)->update(time);
}

void Game::render(int time)
{
    mainCharacter->render(time);
    terrain->render(time);

    for (auto enemy = this->enemies.begin(); enemy < this->enemies.end(); enemy++)
        (*enemy)->render(time);

    for (auto obs = this->obstacles.begin(); obs < this->obstacles.end(); obs++)
        (*obs)->render(time);
}

