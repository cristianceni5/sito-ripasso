/*
 * Character.h
 *
 */

#ifndef CHARACTER_H_
#define CHARACTER_H_

#include "Weapon.h"

class GameCharacter {
public:
    GameCharacter(int hp = 10, int a = 10);

    // overload
    void move(int x, int y);
    void move(int distance);

    int getPosX() {
        return posX;
    }

    void setPosX(int posX) {
        GameCharacter::posX = posX;
    }

    int getPosY() {
        return posY;
    }

    void setPosY(int posY) {
        GameCharacter::posY = posY;
    }

    int getHP();

    void setHP(int hp);

    Weapon* getWeapon();

    void setWeapon(Weapon* weapon);

    int getArmor();

    void setArmor(int defense);

    bool fight(GameCharacter &enemy);
    bool isLegalFight(GameCharacter &enemy);

    int receiveDamage(int points);

private:
    int HP;
    int armor;
    int posX;
    int posY;
    Weapon* weapon;
};

#endif // CHARACTER_H_
