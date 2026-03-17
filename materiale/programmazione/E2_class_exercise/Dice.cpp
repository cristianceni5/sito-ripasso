//
// Created by Marco Bertini on 21/03/18.
//

#include "Dice.h"
#include <cmath>
#include <ctime> // for time
#include <cstdlib> // for rand and srand

int Dice::numRoll = 0;
// read: https://stackoverflow.com/questions/7343833/srand-why-call-it-only-once
// TODO in the constructor add srand( time(0) ); to initialize random number generator

int Dice::roll(int r) {
    int result=0;

    if (numRoll > NUM_MAX) {
        srand(time(0));
        numRoll = 0;
    }
    // XXX it goes against the best practice. Set a very high number for max num rolls
    // read: https://stackoverflow.com/questions/1452934/what-is-the-meaning-of-xxx-in-code-comments

    for (int i=0; i<r; i++)
        result += rand() % faces;
    // TODO update number of rolls
    return result;
}