//
// Created by Marco Bertini on 08/04/18.
//

#ifndef E3_INHERITANCE_EXERCISE_SKELETON_H
#define E3_INHERITANCE_EXERCISE_SKELETON_H


// TODO extend GameCharacter
class Skeleton {
public:
    // TODO add magicRecover param in c'tor

    // TODO override receiveDamage(int points);
    // XXX it's already implemented in .cpp file

    // XXX no need to override other base class methods in this class

    // override base class method
    char getCharacterSymbol() const {
        return 'S';
    }

private:
    bool magicRecover;
};


#endif //E3_INHERITANCE_EXERCISE_SKELETON_H
