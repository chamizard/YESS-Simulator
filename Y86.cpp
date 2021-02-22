/*
    Name:   Y86.cpp
    Desc:   Starting implementation of Y86 class
    Author: efb
    Date:   1/6/2016
*/
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

bool Y86::load(char *fname) {
  if (Y86Loader::isValidFileName(fname)) {
    ifstream file{fname};
    readFile(file);
  }

}

bool Y86::readFile (std::ifstream& infile) {
  Y86Loader::readFile(infile);
}

int writeMemory (std::string inst, uint64_t address) {

}

void getLine (uint64_t *, uint64_t) {

}
