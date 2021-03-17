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
void ExecuteStage::reset(MemoryStage *pmemoryStage)
{
	memoryStage = pmemoryStage;
    stat.reset();               // sets stat to SBUB (0)
    icode.reset(INOP);          // sets icode to INOP (1)
    ifun.reset();               // sets ifun to FNONE (0)
    E_valC.reset();             // Reset the E_valC register to 0
    E_valA.reset();             // Reset the E_valA register to 0
    E_valB.reset();             // Reset the E_valB register to 0
    E_srcA.reset(RNONE);          // Reset the E_srcA register to RNONE (15)
    E_srcB.reset(RNONE);          // Reset the E_srcB register to RNONE (15)
    E_dstE.reset(RNONE);          // Reset the E_dstE register to RNONE (15)
    E_dstM.reset(RNONE);          // Reset the E_dstM register to RNONE (15)
}

/*---------------------------------------------------------------------------
    clockP0 - (pure virtual from PipeStage)
         Performs operations of clock Phase0 for this stage
-----------------------------------------------------------------------------*/
void ExecuteStage::clockP0()
{
  // Must implement clockP0 since it is declared pure-virtual 
    stat.clock();
    icode.clock();
    ifun.clock();
    E_valC.clock();
    E_valA.clock();      
    E_valB.clock();
    E_dstE.clock();
    E_dstM.clock();
    E_srcA.clock();
    E_srcB.clock();
    
}
/*---------------------------------------------------------------------------
    clockP1 - (pure virtual from PipeStage)
         Performs operations of clock Phase1 for this stage
-----------------------------------------------------------------------------*/
void ExecuteStage::clockP1()
{
    memoryStage->updateMRegister(); // fix params
}

void ExecuteStage::updateERegister(uint64_t D_stat, uint64_t D_icode, uint64_t D_ifun, uint64_t D_valC, 
    uint64_t d_valA, uint64_t d_valB, uint64_t d_dstE, uint64_t d_dstM, uint64_t d_srcA, uint64_t d_srcB) { // fix params
    
    stat.setInput(D_stat);
    icode.setInput(D_icode);
    ifun.setInput(D_ifun);
    E_valC.setInput(D_valC);
    E_valA.setInput(d_valA);
    E_valB.setInput(d_valB);
    E_dstE.setInput(d_dstE);
    E_dstM.setInput(d_dstM);
    E_srcA.setInput(d_srcA);
    E_srcB.setInput(d_srcB);

}