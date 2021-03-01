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

    bool testHasData1 = hasData("0x000:                      | 		.pos 0x0");
    cout << "Test 1: " << testHasData1 << '\n';

    bool testHasData2 = hasData("0x000: 30f40020000000000000 | 		irmovq stack, %rsp");
    cout << "Test 2: " << testHasData2 << '\n';

    bool testHasData3 = hasData("0x013: 00                   | 		halt");
    cout << "Test 3: " << testHasData3 << '\n';

    bool testHasData4 = hasData("0x048:                      | 		.align 8");
    cout << "Test 4: " << testHasData4 << '\n';

    // Tests for hasValidData
    cout << "Testing hasValidData:" << '\n';

    uint64_t testHasValidData1 = hasValidData("0x000:                      | 		.pos 0x0");
    cout << "Test 1: " << testHasValidData1 << '\n';

    uint64_t testHasValidData2 = hasValidData("0x000: 30f40020000000000000 | 		irmovq stack, %rsp");
    cout << "Test 2: " << testHasValidData2 << '\n';

    uint64_t testHasValidData3 = hasValidData("0x013: 00                   | 		halt");
    cout << "Test 3: " << testHasValidData3 << '\n';

    uint64_t testHasValidData4 = hasValidData("0x038: 30f7180000000000000  | main:	irmovq array,%rdi  ***Error: odd number of data chars");
    cout << "Test 4: " << testHasValidData4 << '\n';

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
    
    bool testCheckHex5 = checkHex("0x038: 30f7180000000000000  |", 7, 27);
    cout << "Test 5: " << testCheckHex5 << '\n';

    // Tests for storeData
    cout << "Testing storeData:" << '\n';

    // Tests for storeByte
    cout << "Testing storeByte:" << '\n';

}




