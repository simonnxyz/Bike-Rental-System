#include "../include/DragonBicycle.h"

void DragonBicycle::take_damage(float damage) {
    health -= damage;
    if(health<0)
        health = 0;
}
void DragonBicycle::breathe_fire() {
    std::cout << "🔥🔥🔥🔥🔥🔥" << std::endl;
}
void DragonBicycle::fly() {
    std::cout << "lece bo chceeeee" << std::endl;
    std::cout << "lece bo zyyyciee jest zleee" << std::endl;
}
