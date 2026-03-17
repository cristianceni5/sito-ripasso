#ifndef WEAPON_H
#define WEAPON_H

class Weapon {
public:
    Weapon(int s = 0, bool magic = false) : strength(s), magic(magic) {
        if (strength <= 0)
            strength = 1;
    }

    int use();

    // Getter - prende e ritorna il valore
    int getStrength() {
        return strength;
    }

    bool isMagic() {
        return magic;
    }

    // Setter - setta e non ritorna
    void setStrength(int s) {
        if (s > 0)
            strength = s;
    }

    void setMagic(bool m) {
        magic = m;
    }

protected:
    int strength;
    bool magic;
};

#endif //WEAPON_H
