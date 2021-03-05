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
#include "Y86Loader.cpp"
#include <fstream>
#include "Y86Loader.h"


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

bool Y86::load(char *fname) {
  if (Y86Loader::isValidFileName(fname)) {
    std::ifstream file (fname, std::ifstream::in);
    readFile(file);
  }
  return true;
}

int Y86::writeMemory (std::string inst, uint64_t address) 
{
    int dataIndex = 0;
    uint64_t data = 0;
    for (int i = 25; i > 7; i -= 2) 
    {
        data = Y86Loader::getByte(inst.substr(i, 2));
        memory.putByte(address, data);
        dataIndex++;
    }
    return 1;
}

bool readFile (std::ifstream infile) 
{
    char* line;
    uint64_t address = -1;
    int byteNum = 0;
    while (infile) 
    {
        infile.getline(line, 28, '|');
        if (Y86Loader::checkLine(line) && Y86Loader::hasValidAddress(line) && Y86Loader::hasData(line)) 
        {
            address = Y86Loader::getAddress(line);
            byteNum = Y86Loader::hasValidData(line);
            if (byteNum > 0) 
            {
                int err = Y86::writeMemory(line, address);
                if (err == 1) 
                {
                  return true;
                }
                else 
                {
                  return false;
                }
            }
        }
        
    }
    return false;
}



void getLine (uint64_t *, uint64_t) {

}
