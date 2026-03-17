//
// Created on: 13/mar/2018
//  Author: bertini
//

#ifndef WEAPON_H
#define WEAPON_H

class Weapon {
public:
    // Delegazione
    Weapon() : Weapon(STRENGTH_MIN, false){}
    explicit Weapon(int s, bool m = false);

    int use();

    void setStrength(int s) {
        strength = s;
    }

    int getStrength() {
        return strength;
    }

    void setMagic(bool m) {
        magic = m;
    }

    bool isMagic() {
        return magic;
    }

protected:
    int strength;
    bool magic {false};
    static const int STRENGTH_MIN = 10;
};

#endif // WEAPON_H
