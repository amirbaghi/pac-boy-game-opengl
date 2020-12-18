#include "Component.h"


class Score: public Component
{
public:

    Score(Component* parent);
    ~Score();

    void load(int time);
    void render(int time);
    void update(int time);

    // Score Getter
    int getScore();
    // Score Setter
    void setScore(int score);

private:
    // Score so far
    int score;
    // Texture Id
    GLuint texture_id;

protected:

};