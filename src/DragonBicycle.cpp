#include "../include/DragonBicycle.h"

void DragonBicycle::take_damage(float damage)
{
    health -= damage;
    if(health<0)
        health = 0;
}