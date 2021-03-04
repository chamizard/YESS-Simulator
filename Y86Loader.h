/*
    File:   Y86Loader.h
    Desc:   Declarations for utility functions used in
            Y86 loader. 
    
    Author: Cameron Mann and Milton Barba
*/

#ifndef Y86Loader_H
#define Y86Loader_H

#include <iostream>
#include <cstdint>
#include <string>

namespace Y86Loader {
	
    bool isValidFileName(std::string input);

    void readFile(std::ifstream infile);

    bool checkLine(std::string line);

    bool hasValidAddress(std::string line);

    bool isCommentLine(std::string line);

    bool isBlankLine(std::string line);

    bool hasData(std::string line);

    uint64_t hasValidData(std::string line);

    uint64_t getAddress(std::string input);

    uint64_t hasSpaces(std::string input, int start, int end);

    bool checkHex(std::string input, int start, int end);

    bool storeData(std::string input, int numBytes, Memory mem);

    bool storeByte(std::string input, uint64_t byteAddress, Memory mem);
    

};

#endif