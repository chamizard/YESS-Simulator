/*
    File:   Memory Stage.cpp
    Desc:   Memory Stage implementation for Y86-64 simulator
    
    Authors: Cameron Mann and Milton Barba
    
    Last update:  Spring 2021
    
*/
#include "Y86.h"
#include "MemoryStage.h"

/*---------------------------------------------------------------------------
    reset- used to connect to other Y86 components
     
-----------------------------------------------------------------------------*/
void MemoryStage::reset(WritebackStage *pwriteback)
{
	writebackStage = pwriteback;
}

/*---------------------------------------------------------------------------
    clockP0 - (pure virtual from PipeStage)
         Performs operations of clock Phase0 for this stage
-----------------------------------------------------------------------------*/
void MemoryStage::clockP0()
{
  // Must implement clockP0 since it is declared pure-virtual 
  
    
}
/*---------------------------------------------------------------------------
    clockP1 - (pure virtual from PipeStage)
         Performs operations of clock Phase1 for this stage
-----------------------------------------------------------------------------*/
void MemoryStage::clockP1()
{
    
}

void MemoryStage::updateMRegister() { // fix params


    
}