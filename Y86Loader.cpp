/*
    File:   Y86Loader.cpp
    Desc:   Declarations for utility functions used in
            Y86 loader. 
    
    Author: Cameron Mann and Milton Barba
*/
#include <cstdint>
#include <stdint.h>
#include <string>
#include <iostream>
#include <fstream>
#include "Y86.h"
#include "Sim.h"

// Prototypes

bool isValidFileName(std::string input);

bool checkLine(std::string line);

bool hasValidAddress(std::string line);

bool isCommentLine(std::string line);

bool isBlankLine(std::string line);

bool hasData(std::string line);

uint64_t hasValidData(std::string line);

uint64_t getAddress(std::string input);

bool hasSpaces(std::string input, int start, int end);

bool checkHex(std::string input, int start, int end);

// Functions

/*
    returns true if file is of valid type
*/
bool isValidFileName(std::string filename)  
{
    return filename.find(".yo") > 0;
}

/*
    returns true if line has a valid address field
*/
bool hasValidAddress(std::string line) {
    int addrEnd = -1;
    for (int i = 0; i < 7; i++) {
        if (line[i] == ':') {
            addrEnd = i;
            break;
        }
    }
    if (line[0] == '0' && line[1] == 'x' )
    {
        if (addrEnd == -1) {
            return false;
        }
        if (checkHex(line, 2, addrEnd)) {
            return true;
        }
    }
    return false;
}

/*
    returns true if line is a comment
*/
bool isCommentLine(std::string line) 
{
    if (!hasData(line) && !isBlankLine(line)) {
        if (line[28] == '|' || line[29] == '|') {
            return true;
        }
    }
    return false;
}

/*
    returns true if line is blank
*/
bool isBlankLine(std:: string line) 
{
    if (line == "") {
        return true;
    }
    return false;
}

/*
    returns true if line has a valid address and data that is correctly formatted
*/
bool checkLine(std::string line) {
    if (hasValidAddress(line) && hasValidData(line) != 0) {
        int numHexChar = 0;
        for (int i = 2; i < 7; i++) {
            if (line[i] != ':') {
                numHexChar++;
            }
            if (line[i] == ':') {
                break;
            }
        }
        if (line[28] == '|' && numHexChar == 3) {
            if (line[6] == ' ' && line[27] == ' ') {
                return true;
            }
        } else if (line[29] == '|' && numHexChar == 4) {
            if (line[6] != ' ' && line[27] == ' ' && line[28] == ' ') {
                return true;
            }
        }
    }
    return false;
}

/*
    takes as input a record and starting and ending indices into that 
    record and returns true if there are hex characters beginning at 
    the starting position through to the ending position
*/
bool checkHex(std::string input, int start, int end) 
{
    for (int i = start; i < end; i++) 
    {
        if (input[i] < 48 || input[i] > 57) 
        {
            if (input[i] < 97 || input[i] > 102) 
            {
                return false;
            }
        }
    }
    return true;
}

/*
    takes as input a data record and returns the address in that line
*/
uint64_t getAddress(std::string input) 
{
    int addrEnd;
    uint64_t result = 0;
    for (int i = 0; i < 7; i++) {
        if (input[i] == ':') {
            addrEnd = i;
            break;
        }
    }
    if (checkHex(input, 2, addrEnd)) {
        for (int i = 2; i < addrEnd; ++i) {
            if (input[i] >= 48 && input[i] <= 57) {
                result += (input[i] - 48);
            } else {
                result += (input[i] - 87);
            }
            if (i != addrEnd - 1) {
                result <<= 4;
            }
        }
    }
    else 
    {
        result = -1;
    }
    return result;

}

/*
    takes as input a record and starting and ending indices into 
    that record and returns true if there are spaces 
    beginning at the starting position through to the ending position
*/
bool hasSpaces(std::string input, int start, int end) {
    for (int i = start; i < end; i++) {
        if (input[i] == ' ') {
            return true;
        }
    }
    return false;
}


/*
    true if data is present
    i.e. if character positions 7 through 26 contain anything at all other than spaces
*/
bool hasData(std::string line) {
    for (int i = 7; i < 27; i++) {
        if (line[i] != ' ') {
            return true;
        }
    }
    return false;
}

/*
    returns zero if data is invalid, returns the number of data bytes if valid
*/
uint64_t hasValidData(std::string line) {
    uint64_t numBytes = 0;
    if (hasData(line)) {
        for (int i = 7; i < 27; i++) {
            if (line[i] != ' ') {
                numBytes++;
            }
        }
    }

    // Checks that each byte value is valid hex
    if (!checkHex(line, 7, 7+numBytes)) {
        numBytes = 0;
    }

    // Checks that each byte is the correct size
    if (numBytes % 2 == 1) {
        numBytes = 0;
    }
    return numBytes / 2;
}

bool Y86::load(char *fname) {
  if (isValidFileName(fname)) {
    std::ifstream file;
    file.open(fname, std::ifstream::in);
    std::string line;
    uint64_t address = 0;
    uint64_t prevAddress = 0;
    int lineCount = 1;
    int byteNum = 0;
    int prevByteNum = 0;
    // Main loop that reads and processes the file
    while (file) {
        std::getline(file, line);
        
        // TESTS FOR CHECKING DIFFERENT FUNCTION OUTPUT
        // ----------------------------------------------
        //std::cout << line << '\n';
        //std::cout << "Line has Data: " << hasData(line) << '\n';
        //std::cout << "Line has Valid Data: " << hasValidData(line) << '\n';
        //std::cout << "Line has Valid Address: " << hasValidAddress(line) << '\n';
        //std::cout << "Checkline: " << checkLine(line) << '\n';
        //std::cout << "Comment Line: " << isCommentLine(line) << '\n';
        //std::cout << "Blank Line: " << isBlankLine(line) << '\n';
        // -----------------------------------------------

        if (lineCount == 1) {
            prevAddress = getAddress(line);
            //std::cout << "Previous address: " << prevAddress << '\n';
            prevByteNum = hasValidData(line);
            //std::cout << "Previous number of bytes: " << prevByteNum << '\n';
            //std::cout << '\n';
        } else {
            prevAddress = address;
            //std::cout << "Previous address: " << prevAddress << '\n';
            prevByteNum = byteNum;
            //std::cout << "Previous number of bytes: " << prevByteNum << '\n';
            //std::cout << '\n';
        }

        if (checkLine(line)) {  

            address = getAddress(line);
            //std::cout << "Address: " << address << '\n';
            byteNum = hasValidData(line);
            //std::cout << "Number of bytes: " << byteNum << '\n';

            if (byteNum > 0) {
                // Check if instructions are being written to the correct addresses based
                // on the previous address and previous number of bytes
                if (prevAddress + prevByteNum > address) {
                    std::cout << "Error on line " << lineCount << '\n';
                    std::cout << line << '\n';
                    return false;
                }
                int err = Y86::writeMemory(line.substr(7, 26), byteNum, address);
                if (err == 0) {
                    return false;
                }
            } else {
                std::cout << "Error on line " << lineCount << '\n';
                std::cout << line << '\n';
                return false;
            }
        } else {
            
            if (!isCommentLine(line) && !isBlankLine(line)) {
                std::cout << "Error on line " << lineCount << '\n';
                std::cout << line << '\n';
                return false;
            }
        }
        lineCount++;
    }
  }
  return true;
}