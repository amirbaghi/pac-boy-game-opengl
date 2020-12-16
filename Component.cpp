#include "Headers/Component.h"

Component::Component(Component* parent)
{
    auto time = glutGet(GLUT_ELAPSED_TIME);
    this->created_time = time;
    this->parent_component = parent;
}