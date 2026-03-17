#ifndef E2_CLASS_EXERCISE_DICE_H
#define E2_CLASS_EXERCISE_DICE_H
#include <ctime>
#include <cmath>

class Dice {
public:
    explicit Dice(int f = 6) : faces(f) {
        if (faces < 2) {
            faces = 6;
        }

        srand(time(0));
    }

    int roll(int r);

private:
    int faces; // Facce del dado
    static int numRoll; // Numero dei roll di sto cazzo di dado
    const int NUM_MAX = 6969; // Numero massimo alto
};


#endif //E2_CLASS_EXERCISE_DICE_H
