//
// Created on: 13/mar/2018
//  Author: bertini
//

#ifndef WEAPON_H
#define WEAPON_H

class Weapon {
public:
    Weapon();
    explicit Weapon(int s, bool m = false);

    virtual int use();

    void setStrength(int s) {
        strength = s;
    }

    int getStrength() const {
        return strength;
    }

    void setMagic(bool m) {
        magic = m;
    }

    bool isMagic() const {
        return magic;
    }

protected:
    int strength;
    bool magic;
};

#endif // WEAPON_H
