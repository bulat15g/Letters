#include <iostream>
using namespace std;
#include "Letter.h"

int main() {
    srand(time(0));
    Letter testLetter,test2Letter;

    testLetter.fillRandLetter();
    testLetter.showLetter();

    test2Letter.fillRandLetter();
    test2Letter.showLetter();

    cout<<testLetter.compare(test2Letter.image);

    testLetter.writeToFile("Primitives/ME");


    return 0;
}