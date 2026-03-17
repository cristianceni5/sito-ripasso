/*
 * Character.cpp
 *
 */

#include "GameCharacter.h"

#include <ctime>
#include <iostream>

using namespace std;

GameCharacter::GameCharacter(int hp, int a) : HP(hp), armor(a), posX(0), posY(0), weapon(nullptr) {
    if (hp <= 0)
        HP = 10;

    if (a <= 0)
        armor = 10;
}

int GameCharacter::getHP() {
    return HP;
}

void GameCharacter::setHP(int hp) {
    this->HP = hp;
}

Weapon *GameCharacter::getWeapon() {
    return weapon;
}

void GameCharacter::setWeapon(Weapon *weapon) {
    this->weapon = weapon;
}

void GameCharacter::move(int x, int y) {
    posX += x;
    posY += y;
}

void GameCharacter::move(int distance) {
    posX += distance;
    posY += distance;
}

int GameCharacter::getArmor() {
    return armor;
}

void GameCharacter::setArmor(int defense) {
    this->armor = defense;
}

bool GameCharacter::fight(GameCharacter &enemy) {
    int hit = 1;

    if (weapon) {
        hit = weapon->use();
    }

    int damage = 0;
    if (hit > enemy.armor) {
        damage = receiveDamage(hit);
    }

    bool success = false;
    if (damage) {
        cout << "You hit the enemy fratm ! enemy HP: " << enemy.HP << endl;
        success = true;
    } else
        cout << "You miss the hit..." << endl;
    return success;
}

int GameCharacter::receiveDamage(int points) {
    if (armor > 4)
        points = points / 3;
    else if (armor > 2)
        points = points / 2;
    else if (armor >= 1)
        points = points - 2;

    if (points <= 0)
        points = 1;

    HP -= points;
    if (points > 10)
        armor--;

    return points;
}

bool GameCharacter::isLegalFight(GameCharacter &enemy) {
    int maxDistance = 1;

    if (posX <= maxDistance || posY <= maxDistance)
        return true;

    return false;
}
