#include"../include/Bicycle.h"


class DragonBicycle : public Bicycle
{
    void take_damage(float damage);

    private:
    int heads;
    float health;
};
