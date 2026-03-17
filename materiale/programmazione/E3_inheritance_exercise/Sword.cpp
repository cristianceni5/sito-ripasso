//
// Created by Marco Bertini on 08/04/18.
//

#include "Sword.h"

Sword::Sword(int s, bool m, bool v) : Weapon(s, m), valirian(v) {
    // there could be some more code here...
    // or just keep it empty, as it makes more sense
}

int Sword::use() {
    int result = Weapon::use();
    if (valirian)
        result *= 2;
    return result;
}
