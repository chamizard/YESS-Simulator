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
void MemoryStage::reset(WritebackStage *pwriteback, Memory *pmemory)
{
	writebackStage = pwriteback;
    memory = pmemory;
    stat.reset();
    icode.reset(INOP);
    ifun.reset();
    cnd.reset();
    valE.reset();
    valA.reset();      
    dstE.reset(RNONE);
    dstM.reset(RNONE);    
}

/*---------------------------------------------------------------------------
    clockP0 - (pure virtual from PipeStage)
         Performs operations of clock Phase0 for this stage
-----------------------------------------------------------------------------*/
void MemoryStage::clockP0()
{
  // Must implement clockP0 since it is declared pure-virtual 
    stat.clock();
    icode.clock();
    ifun.clock();
    cnd.clock();
    valE.clock();
    valA.clock();      
    dstE.clock();
    dstM.clock();    
}
/*---------------------------------------------------------------------------
    clockP1 - (pure virtual from PipeStage)
         Performs operations of clock Phase1 for this stage
-----------------------------------------------------------------------------*/
void MemoryStage::clockP1()
{
    writebackStage->updateWRegister(stat.getState(), icode.getState(), ifun.getState(), valE.getState(), valA.getState(), dstE.getState(), dstM.getState());
}

void MemoryStage::updateMRegister(uint64_t E_stat, uint64_t E_icode, uint64_t E_ifun, uint64_t E_Cnd, 
    uint64_t E_valA, uint64_t E_valB, uint64_t E_dstE, uint64_t E_dstM) 
{ 
    stat.setInput(E_stat);
    icode.setInput(E_icode);
    ifun.setInput(E_ifun);
    cnd.setInput(E_Cnd);
    valE.setInput(E_valA);
    valA.setInput(E_valB);
    dstE.setInput(E_dstE);
    dstM.setInput(E_dstM);

    
}