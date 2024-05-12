#include"../include/Bicycle.h"


class DragonBicycle : public Bicycle
{
    void take_damage(float damage);
    void breathe_fire();
    void fly();

    private:
    int heads;
    float health;
};
