/** Example Library
 *
 * Containing some of the basics, plus the use of a serial port instance
 * within the library without hard coding the `Serial` code word for access.
 */

// Include guard
#ifndef test_h
#define test_h
#include <Arduino.h>

class test {
    private:
        Stream* serialInstance;
    public:
        // Function prototypes
        test(Stream* initSerial);
        int printOut(char* inString);
};
#endif
