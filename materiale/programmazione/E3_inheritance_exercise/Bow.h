//
// Created by Marco Bertini on 08/04/18.
//

#ifndef E3_INHERITANCE_EXERCISE_BOW_H
#define E3_INHERITANCE_EXERCISE_BOW_H
// I'm including Weapon to extend it with this script
#include "Weapon.h"

class Bow : public Weapon {
public:
    // Add a constructor with an "a" parameter with a default of 20
    explicit Bow(int s, bool m = false, int a = 20): Weapon(s, m), arrows(a) {}

    // I need to re-declare use() to change its behaviour
    int use();

    int getArrows() const {
        return arrows;
    }

    void setArrows(int arrows) {
        Bow::arrows = arrows;
    }

protected:
    int arrows;
};


#endif //E3_INHERITANCE_EXERCISE_BOW_H
