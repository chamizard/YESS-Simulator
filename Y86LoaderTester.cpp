#include <cstdlib>
#include <iostream> // for std::cout , etc.
#include <iomanip>  // additional formatting for cout
#include <cstdint>  // standard int types like uint64_t 
#include <stdio.h> // in case you want to use printf
#include "Y86Loader.h" // Y86Loader function declarations


using namespace std;
using namespace Y86Loader;  

int main(int argc, char *argv[])
{
    // Tests for isValidFileName
    cout << "Testing isValidFileName:" << '\n';

    // Tests for readFile
    cout << "Testing readFile:" << '\n';

    // Tests for checkLine
    cout << "Testing checkLine:" << '\n';

    // Tests for hasValidAddress
    cout << "Testing hasValidAddress:" << '\n';

    // Tests for isCommentLine
    cout << "Testing isCommentLine:" << '\n';

    // Tests for isBlankLine
    cout << "Testing isBlankLine:" << '\n';

    // Tests for hasData
    cout << "Testing hasData:" << '\n';

    // Tests for hasValidData
    cout << "Testing hasValidData:" << '\n';

    // Tests for getAddress
    cout << "Testing getAddress:" << '\n';

    // Tests for hasSpaces
    cout << "Testing hasSpaces:" << '\n';
    bool testSpaces1 = hasSpaces("0x013: 00                   ", 0, 27);
    cout << "Test 1: " << testSpaces1 << '\n';

    // Tests for checkHex
    cout << "Testing checkHex;" << '\n';

    // Tests for storeData
    cout << "Testing storeData:" << '\n';

    // Tests for storeByte
    cout << "Testing storeByte:" << '\n';

}




