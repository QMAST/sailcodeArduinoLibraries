#include "test.h"

test::test(Stream* initSerial) {
    serialInstance = initSerial;
}

int test::printOut(char* inString) {
    serialInstance->println(inString);

    return 0;
}
