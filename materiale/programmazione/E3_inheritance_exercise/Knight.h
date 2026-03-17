//
// Created by Marco Bertini on 08/04/18.
//

#ifndef E3_INHERITANCE_EXERCISE_KNIGHT_H
#define E3_INHERITANCE_EXERCISE_KNIGHT_H

#include <string>

// extend GameCharacter
class Knight {
public:
    // TODO add a std::string name and some values for the new attributes

    // TODO override fight: dexterity > 10 perform second attack
    // if paladin then +10 damage

    // TODO override move: if dexterity > 10 allow +1 movement

    // override base class method
    char getCharacterSymbol() const {
        return 'K';
    }

private:
    int dexterity;
    bool paladin;
    std::string name;
};


#endif //E3_INHERITANCE_EXERCISE_KNIGHT_H
