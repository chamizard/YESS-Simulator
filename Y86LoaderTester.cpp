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

    uint64_t testGetAddress1 = getAddress("0x013: 00                   ");
    cout << "Test 1: " << testGetAddress1 << '\n';

    uint64_t testGetAddress2 = getAddress("0x048: efcdab8967452301     ");
    cout << "Test 2: " << testGetAddress2 << '\n';

    uint64_t testGetAddress3 = getAddress("0x1000:0800000000000000      ");
    cout << "Test 3: " << testGetAddress3 << '\n';

    uint64_t testGetAddress4 = getAddress("0800000000000000      ");
    cout << "Test 4: " << testGetAddress4 << '\n';

    // Tests for hasSpaces
    cout << "Testing hasSpaces:" << '\n';

    bool testSpaces1 = hasSpaces("0x013: 00                   ", 0, 27);
    cout << "Test 1: " << testSpaces1 << '\n';

    bool testSpaces2 = hasSpaces("30f40020000000000000", 0, 10);
    cout << "Test 2: " << testSpaces2 << '\n';

    bool testSpaces3 = hasSpaces(" fadf      adsfja    j", 3, 11);
    cout << "Test 3: " << testSpaces3 << '\n';

    bool testSpaces4 = hasSpaces("0x1000:0800000000000000      ", 0, 20);
    cout << "Test 4: " << testSpaces4 << '\n';

    // Tests for checkHex
    cout << "Testing checkHex;" << '\n';

    bool testCheckHex1 = checkHex("0x013: 00                   ", 0, 27);
    cout << "Test 1: " << testCheckHex1 << '\n';

    bool testCheckHex2 = checkHex("30f40020000000000000", 0, 10);
    cout << "Test 2: " << testCheckHex2 << '\n';

    bool testCheckHex3 = checkHex(" fadf      adsfja    j", 3, 11);
    cout << "Test 3: " << testCheckHex3 << '\n';

    bool testCheckHex4 = checkHex("0800000000000000      ", 0, 10);
    cout << "Test 4: " << testCheckHex4 << '\n';

    // Tests for storeData
    cout << "Testing storeData:" << '\n';

    // Tests for storeByte
    cout << "Testing storeByte:" << '\n';

}




