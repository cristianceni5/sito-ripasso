//
// Created on: 13/mar/2018
// Author: bertini
//

#include "Weapon.h"

// Lista di inizializzazione
Weapon::Weapon(int s, bool m): strength(s), magic(m) {
    if (strength <= 0) {
        strength = STRENGTH_MIN;
    }
}

int Weapon::use() {
    int result = strength;
    if (magic)
        result *= 2;
    return result;
}