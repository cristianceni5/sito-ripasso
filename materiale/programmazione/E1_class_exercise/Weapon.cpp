#include "Weapon.h"


int Weapon::use() {
    if (magic)
        strength = strength * 2; // XXX int overflow risk

    return strength;
}
