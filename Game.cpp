#include "Headers/Game.h"
#include "Headers/MainCharacter.h"
#include "Headers/Terrain.h"
#include "Headers/Enemy.h"
#include "Headers/Obstacle.h"
#include "Headers/Point.h"
#include "Headers/Score.h"
#include <ctime>

Game::Game() : Component(NULL)
{
    this->game = this;
}

Game::~Game()
{
}

MainCharacter *Game::getMainCharacter()
{
    return this->mainCharacter;
}

std::vector<Obstacle *> Game::getObstacles()
{
    return this->obstacles;
}

std::vector<Point *> Game::getPoints()
{
    return this->points;
}

void Game::setPoints(std::vector<Point *> points)
{
    this->points = points;
}

Score *Game::getScore()
{
    return this->score;
}

void Game::keyboard(int time, int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_UP:
        mainCharacter->up(time);
        break;
    case GLUT_KEY_DOWN:
        mainCharacter->down(time);
        break;
    case GLUT_KEY_RIGHT:
        mainCharacter->right(time);
        break;
    case GLUT_KEY_LEFT:
        mainCharacter->left(time);
        break;
    default:
        break;
    }
}

void Game::keyboard_up(int time, int key, int x, int y)
{
    mainCharacter->stop(time);
}

void Game::generateObstacles()
{

    Obstacle *obstacle1 = new Obstacle(this);
    obstacle1->setPosition(50, 500, 170, 555, false);
    this->obstacles.push_back(obstacle1);

    Obstacle *obstacle2 = new Obstacle(this);
    obstacle2->setPosition(50, 360, 170, 360 + 55, false);
    this->obstacles.push_back(obstacle2);

    Obstacle *obstacle3 = new Obstacle(this);
    obstacle3->setPosition(50, 170, 170, 170 + 55, false);
    this->obstacles.push_back(obstacle3);

    Obstacle *obstacle4 = new Obstacle(this);
    obstacle4->setPosition(170, 82, 170 + 60, 170 + 55, true);
    this->obstacles.push_back(obstacle4);

    Obstacle *obstacle5 = new Obstacle(this);
    obstacle5->setPosition(235, 500, 355, 555, false);
    this->obstacles.push_back(obstacle5);

    Obstacle *obstacle6 = new Obstacle(this);
    obstacle6->setPosition(445, 500, 565, 555, false);
    this->obstacles.push_back(obstacle6);

    Obstacle *obstacle7 = new Obstacle(this);
    obstacle7->setPosition(630, 500, 750, 555, false);
    this->obstacles.push_back(obstacle7);

    Obstacle *obstacle8 = new Obstacle(this);
    obstacle8->setPosition(630, 360, 750, 360 + 55, false);
    this->obstacles.push_back(obstacle8);

    Obstacle *obstacle9 = new Obstacle(this);
    obstacle9->setPosition(630, 170, 750, 170 + 55, false);
    this->obstacles.push_back(obstacle9);

    Obstacle *obstacle10 = new Obstacle(this);
    obstacle10->setPosition(630 - 60, 82, 630, 170 + 55, true);
    this->obstacles.push_back(obstacle10);

    Obstacle *obstacle11 = new Obstacle(this);
    obstacle11->setPosition(324, 36, 464, 36 + 55, false);
    this->obstacles.push_back(obstacle11);

    Obstacle *obstacle12 = new Obstacle(this);
    obstacle12->setPosition(324 + 41, 82, 324 + 41 + 60, 170 + 55, true);
    this->obstacles.push_back(obstacle12);

    Obstacle *obstacle13 = new Obstacle(this);
    obstacle13->setPosition(278, 275, 278 + 60, 275 + 143, true);
    this->obstacles.push_back(obstacle13);

    Obstacle *obstacle14 = new Obstacle(this);
    obstacle14->setPosition(522 - 60, 275, 522, 275 + 143, true);
    this->obstacles.push_back(obstacle14);
}

void Game::generatePoints()
{
    std::srand((unsigned int)time(NULL));
    auto numberOfPoints = 6 + (std::rand() % (20 - 6 + 1));

    for (auto i = 0; i < numberOfPoints; i++)
    {
        auto randXPos = 2 + (std::rand() % (798 - 2 + 1));
        auto randYPos = 2 + (std::rand() % (598 + 1));

        Point *point = new Point(this);
        point->setPosition(randXPos, randYPos);
        this->points.push_back(point);
    }
}
void Game::load(int time)
{

    // Generate Obstacles
    generateObstacles();

    // Generate Points
    generatePoints();

    //TODO: Generate Enemies

    MainCharacter *mainCharacter = new MainCharacter(this);
    mainCharacter->setInitialMotionPositionAndTime(500, 500, time);
    this->mainCharacter = mainCharacter;
    mainCharacter->load(time);

    Score *score = new Score(this);
    score->load(time);
    this->score = score;

    Terrain *terrain = new Terrain(this);
    terrain->load(time);
    this->terrain = terrain;

    // Generate
    Enemy *enemy1 = new Enemy(this);
    enemy1->setInitialMotionPositionAndTime(200, 200, time);
    this->enemies.push_back(enemy1);

    Enemy *enemy2 = new Enemy(this);
    enemy2->setInitialMotionPositionAndTime(400, 400, time);
    this->enemies.push_back(enemy2);

    // Obstacle *obstacle1 = new Obstacle(this);
    // obstacle1->setPosition(90, 90, 140, 120);
    // this->obstacles.push_back(obstacle1);

    // Point *point1 = new Point(this);
    // point1->setPosition(300, 300);
    // this->points.push_back(point1);

    for (auto enemy = this->enemies.begin(); enemy < this->enemies.end(); enemy++)
        (*enemy)->load(time);

    for (auto obs = this->obstacles.begin(); obs < this->obstacles.end(); obs++)
        (*obs)->load(time);

    for (auto point = this->points.begin(); point < this->points.end(); point++)
        (*point)->load(time);
}

void Game::update(int time)
{
    // TODO: check if the game is over now, all the points are taken
    mainCharacter->update(time);

    terrain->update(time);

    for (auto enemy = this->enemies.begin(); enemy < this->enemies.end(); enemy++)
        (*enemy)->update(time);

    for (auto obs = this->obstacles.begin(); obs < this->obstacles.end(); obs++)
        (*obs)->update(time);

    for (auto point = this->points.begin(); point < this->points.end(); point++)
        (*point)->update(time);

    score->update(time);
}

void Game::render(int time)
{
    terrain->render(time);
    mainCharacter->render(time);

    for (auto enemy = this->enemies.begin(); enemy < this->enemies.end(); enemy++)
        (*enemy)->render(time);

    for (auto obs = this->obstacles.begin(); obs < this->obstacles.end(); obs++)
        (*obs)->render(time);

    for (auto point = this->points.begin(); point < this->points.end(); point++)
        (*point)->render(time);

    score->render(time);
}
