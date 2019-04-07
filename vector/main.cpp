#include <iostream>
#include "vectorishka.h"

int main() {

    file_ = fopen(Log, "w");

    Vectorishka vector(1);
    vector.pushback(7);

    Vectorishka test(2);
    test[0] = 1;
    test[1] = 2;

    Vectorishka test_add(2);
    test_add[0] = 1;
    test_add[1] = 2;

    vector = test + test_add;

    Vectorishka test_move(test + vector);

    test.Dump();
    test_add.Dump();
    vector.Dump();
    test_move.Dump();

    fclose(file_);
    return 0;
}