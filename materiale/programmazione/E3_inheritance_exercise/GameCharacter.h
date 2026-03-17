/*
 * Character.h
 *
 *  Created on: 13/mar/2018
 *  Author: bertini
 */

#ifndef CHARACTER_H_
#define CHARACTER_H_

#include "Weapon.h"

class GameCharacter {
public:
    GameCharacter();
    explicit GameCharacter(int hp, int a = 10);

    ~GameCharacter();

    GameCharacter(const GameCharacter &original);
    GameCharacter &operator=(const GameCharacter &right);

    void move(int x, int y); // TODO we want to override it. Must it be virtual ?

    // TODO we want to override it. Must it be virtual ?
    char getCharacterSymbol() const {
        return 'C';
    }

    int fight(GameCharacter &enemy); // TODO we want to override it. Must it be virtual ?
    bool isLegalFight(const GameCharacter &enemy) const;

    int receiveDamage(int points); // TODO we want to override it. Must it be virtual ?

    static int l1Distance(const GameCharacter& p, const GameCharacter& q);

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

    int getMovements() const;
    void setMovements(int movements);

// TODO change to protected ?
private:
    int HP;
    int armor;
    int movements;
    int posX;
    int posY;
    Weapon* weapon;
};

#endif // CHARACTER_H_
