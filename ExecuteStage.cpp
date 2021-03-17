/*
    File:   Execute Stage.cpp
    Desc:   Execute Stage implementation for Y86-64 simulator
    
    Authors: Cameron Mann and Milton Barba
    
    Last update:  Spring 2021
    
*/
#include "Y86.h"
#include "ExecuteStage.h"

/*---------------------------------------------------------------------------
    reset- used to connect to other Y86 components
     
-----------------------------------------------------------------------------*/
void ExecuteStage::reset(MemoryStage *pmemory)
{
	memoryStage = pmemory;
}

/*---------------------------------------------------------------------------
    clockP0 - (pure virtual from PipeStage)
         Performs operations of clock Phase0 for this stage
-----------------------------------------------------------------------------*/
void ExecuteStage::clockP0()
{
  // Must implement clockP0 since it is declared pure-virtual 
  
    
}
/*---------------------------------------------------------------------------
    clockP1 - (pure virtual from PipeStage)
         Performs operations of clock Phase1 for this stage
-----------------------------------------------------------------------------*/
void ExecuteStage::clockP1()
{
    
}

void ExecuteStage::updateERegister() { // fix params
    
}