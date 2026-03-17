//
// Created by Marco Bertini on 08/04/18.
//

#include "Bow.h"


int Bow::use() {
    int result = 0;
    if (arrows) {
        result = Weapon::use();
        arrows --;
    }
    return result;
}