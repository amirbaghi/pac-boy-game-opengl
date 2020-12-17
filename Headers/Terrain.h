#ifndef TERRAIN_H
#define TERRAIN_H

#include "Component.h"

class Terrain : public Component
{
public:
    Terrain(Component *parent);
    ~Terrain();

    void load(int time);
    void update(int time);
    void render(int time);

private:
    // Texture id of the ground
    GLuint texture_id;

protected:
};

#endif