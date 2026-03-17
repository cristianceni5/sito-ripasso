//
// Created by Marco Bertini on 08/04/18.
//

#ifndef E3_INHERITANCE_EXERCISE_SWORD_H
#define E3_INHERITANCE_EXERCISE_SWORD_H

#include "Weapon.h"

class Sword : public Weapon {
public:
    explicit Sword(int s, bool m = false, bool v = false);

    virtual int use() override;

    bool isValirian() const {
        return valirian;
    }

    void setValirian(bool valirian) {
        Sword::valirian = valirian;
    }

protected:
    bool valirian;

};


#endif //E3_INHERITANCE_EXERCISE_SWORD_H
