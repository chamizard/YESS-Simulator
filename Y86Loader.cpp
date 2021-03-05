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
    returns if file is of valid type
*/
static bool isValidFileName(std::string filename)  
{
    return filename.find(".yo") > 0;
}


/*
    returns true if line has a valid address field
*/
bool hasValidAddress(std::string line) {

   
}

/*
    returns if line is a comment
*/
bool isCommentLine(std::string line) 
{
    if(line [0] == '/');
    {
        return true;
    }



}

/*
    returns if line is blank
*/
bool isBlankLine(std:: string line) 
{
   
    if(line == "");
    {
        return true;
    }
    
}


bool checkLine(std::string line) {
    if (hasValidAddress(line) || isCommentLine(line) || isBlankLine(line)) {
        return true;
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
*/
bool hasData(std::string line) {
    if (hasSpaces(line, 7, 27)) {
        if (hasSpaces(line, 7, 25)) {
            if (hasSpaces(line, 7, 12)) {
                if (hasSpaces(line, 7, 9)) {
                    return false;
                } else {
                    return true;
                }
            } else {
                return true;
            }
        } else {
            return true;
        }
    }
    else {
        return true;
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
    if (numBytes % 2 == 1) {
        numBytes = 0;
        //std::cout << "Error on line " << '\n';
        //std::cout << line << '\n';
    }
    return numBytes / 2;
}

/*
    takes a string representation of two hex characters and a byte address, 
    converts the string to a byte and stores the byte at the specified address.
*/
uint64_t getByte(std::string input) {
    uint64_t byteVal = 0;

     if (input[0] >= 48 && input[0] <= 57) {
        byteVal += (input[0] - 48);
        byteVal <<= 4;
        if (input[1] >= 48 && input[1] <= 57) {
            byteVal += (input[1] - 48);
        } else {
            byteVal += (input[1] - 87);
        }
    } else {
        byteVal += (input[0] - 87);
        byteVal <<= 4;
        if (input[1] >= 48 && input[1] <= 57) {
            byteVal += (input[1] - 48);
        } else {
            byteVal += (input[1] - 87);
        }
    }
    return byteVal;
}

/*
    takes as input a record and number of data bytes, extracts data and stores in YESS memory.
*/
uint64_t* storeData(std::string input, int numBytes) {
    
    uint64_t *data = new uint64_t[numBytes];
    //uint64_t *ptr = new uint64_t[numBytes];
    int dataIndex = 0;
    for (int i = 25; i > 7; i -= 2) {
        data[dataIndex] = storeByte(input.substr(i, 2));
        dataIndex++;
    }
    return data;
}

} // end namespace Y86Loader
