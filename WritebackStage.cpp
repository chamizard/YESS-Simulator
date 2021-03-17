/*
    File:   Writeback Stage.cpp
    Desc:   Writeback Stage implementation for Y86-64 simulator
    
    Authors: Cameron Mann and Milton Barba
    
    Last update:  Spring 2021
    
*/
#include "Y86.h"
#include "WritebackStage.h"

/*---------------------------------------------------------------------------
    reset- used to connect to other Y86 components
     
-----------------------------------------------------------------------------*/
void WritebackStage::reset(ProgRegisters *pregs)
{
	regs = pregs;
}

/*---------------------------------------------------------------------------
    clockP0 - (pure virtual from PipeStage)
         Performs operations of clock Phase0 for this stage
-----------------------------------------------------------------------------*/
void WritebackStage::clockP0()
{
  // Must implement clockP0 since it is declared pure-virtual 
  
    
}
/*---------------------------------------------------------------------------
    clockP1 - (pure virtual from PipeStage)
         Performs operations of clock Phase1 for this stage
-----------------------------------------------------------------------------*/
void WritebackStage::clockP1()
{
    
}

void WritebackStage::updateWRegister() { // fix params


    
}