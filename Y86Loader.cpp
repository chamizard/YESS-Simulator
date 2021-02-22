/*
    File:   Y86Loader.h
    Desc:   Declarations for utility functions used in
            Y86 loader. 
    
    Author: Cameron Mann and Milton Barba
*/
#include <cstdint>
#include <stdint.h>
#include <string>
#include <iostream>
#include <fstream>

namespace Y86Loader 
{

/*

*/
bool isValidFileName(std::string filename)  
{

return filename.find(".yo") > 0;
}

/*

*/
void readFile(std::ifstream infile) {
    while (infile) {
        // read file
        
    }
}

/*

*/
bool checkLine(std::string line) {
    if (hasValidAddress(line) || isCommentLine(line) || isBlankLine(line)) {
        return true;
    }
    return false;
}

/*
    returns true if line has a valid address field
*/
bool hasValidAddress(std::string line) {


}

/*

*/
bool isCommentLine(std::string line) {


}

/*

*/
bool isBlankLine(std::string line) {


}

/*

*/
bool hasData(std::string line) {


}

/*

*/
uint64_t hasValidData(std::string line) {




/*

*/
uint64_t getAddress(std::string input) {


}

<<<<<<< HEAD
=======


>>>>>>> 118c910d1a481f23fe606e141cb7fa25a04bd78c
/*
    takes as input a record and starting and ending indices into 
    that record and returns true if there are spaces 
    beginning at the starting position through to the ending position
*/
<<<<<<< HEAD
bool hasSpaces(std::string input, int start, int end) {
    for (int i = start; i < end; i++) {
        if (input[i] != ' ') {
            return true;
        }
    }
    return false;
}
=======
uint64_t hasSpaces(std::string input, int start, int end) {


}


>>>>>>> 118c910d1a481f23fe606e141cb7fa25a04bd78c

/*

*/
bool checkHex(std::string input, int start, int end) {


}

/*

*/
bool storeData(std::string input, int numBytes) {


}

/*

*/
bool storeByte(std::string input, uint64_t byteAddress) {


}

} // end namespace Y86Loader
