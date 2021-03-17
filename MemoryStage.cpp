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
    M_Cnd.reset();
    M_valE.reset();
    M_valA.reset();      
    M_dstE.reset(RNONE);
    M_dstM.reset(RNONE);    
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
    M_Cnd.clock();
    M_valE.clock();
    M_valA.clock();      
    M_dstE.clock();
    M_dstM.clock();    
}
/*---------------------------------------------------------------------------
    clockP1 - (pure virtual from PipeStage)
         Performs operations of clock Phase1 for this stage
-----------------------------------------------------------------------------*/
void MemoryStage::clockP1()
{
    writebackStage->updateWRegister(stat, icode, ifun, M_Cnd, M_valE, M_valA, M_dstE, M_dstM);
}

void MemoryStage::updateMRegister(uint64_t E_stat, uint64_t E_icode, uint64_t E_ifun, uint64_t E_Cnd, 
    uint64_t E_valA, uint64_t E_valB, uint64_t E_dstE, uint64_t E_dstM) 
{ // fix params
    stat.setInput(E_stat);
    icode.setInput(E_icode);
    ifun.setInput(E_ifun);
    M_Cnd.setInput(E_Cnd);
    M_valE.setInput(E_valA);
    M_valA.setInput(E_valB);
    M_dstE.setInput(E_dstE);
    M_dstM.setInput(E_dstM);

    
}