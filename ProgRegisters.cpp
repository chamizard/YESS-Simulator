/*
    Name:       ProgRegisters.cpp
    
    Desc:       Implements functions for the program register file.
    
    Author:     Cameron Mann and Milton Barba
    
    Date:       2/15/2021 Spring 2021
*/
#include <iostream>
#include <cstdlib>
#include <cstdint>
#include <assert.h>

#include "ProgRegisters.h"
#include "Tools.h"


/*-------------------------------------------------------------------------------------------------
    ProgRegisters constructor  
--------------------------------------------------------------------------------------------------*/
ProgRegisters::ProgRegisters()
{
    reset();
}

/*-------------------------------------------------------------------------------------------------
    clock  - calls clock method of each register and also the CC register
--------------------------------------------------------------------------------------------------*/
void ProgRegisters:: clock()
{
	// your code here
    for (uint64_t i = 0; i < NUM_REGISTERS; i++) {
        reg[i].clock();
    }
    CC.clock();
} 

/*-------------------------------------------------------------------------------------------------
    setReg - sets the INPUT of the specified register
--------------------------------------------------------------------------------------------------*/
void ProgRegisters:: setReg(unsigned regNum, uint64_t rval)
{
    assert(regNum < NUM_REGISTERS && regNum >= 0);
    reg[regNum].setInput(rval);
}
/*-------------------------------------------------------------------------------------------------
    getReg - returns STATE of specified register
--------------------------------------------------------------------------------------------------*/
uint64_t ProgRegisters:: getReg(unsigned regNum)
{
    assert(regNum < NUM_REGISTERS && regNum >= 0);
	return reg[regNum].getState();
}       
/*-------------------------------------------------------------------------------------------------
    setCC - Sets the INPUT of the specified CC bit to the specified value (0 or 1)
--------------------------------------------------------------------------------------------------*/
void ProgRegisters:: setCC(unsigned bitNumber, unsigned val)
{
    assert((bitNumber == 0 || bitNumber == 1 || bitNumber == 2) && (val == 0 || val == 1));
    CC.setInput(Tools::assignOneBit(bitNumber, val, CC.getInput()));
}

/*-------------------------------------------------------------------------------------------------
    getCC - returns the STATE of the specified CC bit
--------------------------------------------------------------------------------------------------*/
unsigned ProgRegisters:: getCC(unsigned bitNumber)
{
	assert(bitNumber == 0 || bitNumber == 1 || bitNumber == 2);
    unsigned val = 1;
    val <<= bitNumber;
    val &= CC.getState();
    return val;
}
          
/*-------------------------------------------------------------------------------------------------
    reset - resets registers and CC flags
--------------------------------------------------------------------------------------------------*/
void ProgRegisters:: reset(void)
{
<<<<<<< HEAD
	// your code here
=======
>>>>>>> 5c1c013a85491d734add4776b8cfd32b6e7fa059
    for (int i = 0; i < NUM_REGISTERS; i++) {
        reg[i].reset();
    }
    CC.reset();
<<<<<<< HEAD
    //setCC(OF, 0);
    //setCC(ZF, 1);
    //setCC(SF, 0);
=======
    setCC(2, 1);
>>>>>>> 5c1c013a85491d734add4776b8cfd32b6e7fa059
} 