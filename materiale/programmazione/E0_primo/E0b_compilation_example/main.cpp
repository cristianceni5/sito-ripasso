#include <iostream>
#include <cstdlib>
#include "greeter.h"
#include "adder.h"

int main() {
    sayHello("Joe");
    int *array;
    int arraySize = 10;
    array = static_cast<int*>(std::malloc(arraySize * sizeof(int)));
    for (int i = 0; i < arraySize; i++)
        array[i] = i;
    std::cout << sum(array, arraySize) << std::endl;
    std::free(array);
    return 0;
}
