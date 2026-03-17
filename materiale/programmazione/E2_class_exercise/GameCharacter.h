/*
 * Character.h
 *
 *  Created on: 13/mar/2018
 *  Author: bertini
 */

#ifndef CHARACTER_H_
#define CHARACTER_H_

#include "Weapon.h"

// FIXME add all the needed const
class GameCharacter {
public:
    // TODO: add default constructor
    GameCharacter(int hp = 10, int a = 10); // FIXME: explicit ?
    // TODO use constructor delegates ?

    // TODO add destructor: when hero dies his weapon is eliminated

    // TODO add copy constructor ?
    // TODO add assignment operator ?

    void move(int x, int y);

    void move(int distance);

    // TODO add static method to compute L1 distance between GameCharacters

    int getPosX() const {
        return posX;
    }

    void setPosX(int posX) {
        GameCharacter::posX = posX;
    }

    int getPosY() const {
        return posY;
    }

    void setPosY(int posY) {
        GameCharacter::posY = posY;
    }

    int getHP() const;

    void setHP(int hp);

    Weapon* getWeapon();

    void setWeapon(Weapon* weapon);

    int getArmor() const;

    void setArmor(int defense);

    bool fight(GameCharacter &enemy);
    bool isLegalFight(const GameCharacter &enemy) const;

    int receiveDamage(int points);

private:
    int HP;
    int armor;
    int posX;
    int posY;
    Weapon* weapon;
};

#endif // CHARACTER_H_
