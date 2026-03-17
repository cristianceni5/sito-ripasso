//
// Created by Marco Bertini on 08/04/18.
//

#ifndef E3_INHERITANCE_EXERCISE_ORC_H
#define E3_INHERITANCE_EXERCISE_ORC_H

// TODO extend GameCharacter... do we need to include GameCharacter.h?
class Orc {
public:
    explicit Orc(int s, int hp=20);

    // TODO override fight: if strength > 10 perform second attack

    // TODO override move; if strength > 10 then allow +1 on the movements (see base class method)
    // XXX it's already implemented in .cpp file

    // override base class method
    char getCharacterSymbol() {
        return 'O';
    }

protected:
    int strength;
};


#endif //E3_INHERITANCE_EXERCISE_ORC_H
