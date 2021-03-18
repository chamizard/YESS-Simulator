/*
    Name:   Y86.cpp
    Desc:   Starting implementation of Y86 class
    Author: efb
    Date:   1/6/2016
*/
#include <iostream>
#include <fstream>
#include <cstdint>
#include "Y86.h"


/*-------------------------------------------------------------------------
  Name:  Y86()
  Desc:  Constructor
---------------------------------------------------------------------------*/
Y86::Y86()
{
  reset();
}
/*-------------------------------------------------------------------------
  reset - resets Y86 object to initial state.
  
---------------------------------------------------------------------------*/
void Y86::reset()
{
	memory.reset();
  regs.reset();
}

/*-------------------------------------------------------------------------
  clockP0 - calls clock function of ProgRegisters class
  
---------------------------------------------------------------------------*/
void  Y86::clockP0()
{
  regs.clock();
}
/*-------------------------------------------------------------------------
  clockP1 - implements functions that run on second half of clock cycle
  
---------------------------------------------------------------------------*/
void  Y86::clockP1()
{
	return;  // nothing for now (Lab 4)
}

/*
  inst = substring of instruction, address = address of instuction
*/
int Y86::writeMemory (std::string inst, int numBytes, uint64_t address) {
  uint64_t newAddr = address;
  //std::cout << '\n';
  //std::cout << "NumBytes: " << numBytes << '\n';
  for (int i = 0; i < (numBytes * 2); i += 2) {
    //std::cout << "Byte: " << inst.substr(i, 2) << '\n';
    //std::cout << "Byte val: " << Y86::getByte(inst.substr(i,2)) << '\n';
    //std::cout << "Byte Address: " << newAddr << '\n';
    //std::cout << '\n';
    memory.putByte(newAddr, Y86::getByte(inst.substr(i, 2)));
    newAddr += 1;
  }
  if (memory.isError()) {
    return 0;
  }
  return 1;
}

/*
void getLine (uint64_t *, uint64_t) {

}
*/

/*
    TODO: Fix
    takes a string representation of two hex characters and a byte address, 
    converts the string to a byte and stores the byte at the specified address.
*/
uint64_t Y86::getByte(std::string input) {
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