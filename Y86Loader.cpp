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
void readfile(std::ifstream infile) {


}

/*

*/
bool checkLine() {


}

/*

*/
bool hasValidAddress() {


}

/*

*/
bool isCommentLine() {


}

/*

*/
bool isBlankLine() {


}

/*

*/
bool hasData() {


}

/*

*/
uint64_t hasValidData() {


}



/*

*/
uint64_t getAddress(std::string input) {


}



/*

*/
uint64_t hasSpaces(std::string input, int start, int end) {


}



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
