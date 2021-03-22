/*
    File:   Execute Stage.cpp
    Desc:   Execute Stage implementation for Y86-64 simulator
    
    Authors: Cameron Mann and Milton Barba
    
    Last update:  Spring 2021
    
*/
#include "Y86.h"
#include "ExecuteStage.h"
#include "Forward.h"

/*---------------------------------------------------------------------------
    reset- used to connect to other Y86 components
     
-----------------------------------------------------------------------------*/
void ExecuteStage::reset(MemoryStage *pmemoryStage, Forward *pforward)
{
	memoryStage = pmemoryStage;
    forward = pforward;
    stat.reset();               // sets stat to SBUB (0)
    icode.reset(INOP);          // sets icode to INOP (1)
    ifun.reset();               // sets ifun to FNONE (0)
    valC.reset();             // Reset the E_valC register to 0
    valA.reset();             // Reset the E_valA register to 0
    valB.reset();             // Reset the E_valB register to 0
    srcA.reset(RNONE);          // Reset the E_srcA register to RNONE (15)
    srcB.reset(RNONE);          // Reset the E_srcB register to RNONE (15)
    dstE.reset(RNONE);          // Reset the E_dstE register to RNONE (15)
    dstM.reset(RNONE);          // Reset the E_dstM register to RNONE (15)
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
    valC.clock();
    valA.clock();      
    valB.clock();
    dstE.clock();
    dstM.clock();
    srcA.clock();
    srcB.clock();
    cnd.clock();
    
}
/*---------------------------------------------------------------------------
    clockP1 - (pure virtual from PipeStage)
         Performs operations of clock Phase1 for this stage
-----------------------------------------------------------------------------*/
void ExecuteStage::clockP1()
{
    memoryStage->updateMRegister(stat.getState(), icode.getState(), ifun.getState(), true, valA.getState(), valB.getState(), dstE.getState(), dstM.getState());
}

void ExecuteStage::updateERegister(uint64_t D_stat, uint64_t D_icode, uint64_t D_ifun, uint64_t D_valC, 
    uint64_t d_valA, uint64_t d_valB, uint64_t d_dstE, uint64_t d_dstM, uint64_t d_srcA, uint64_t d_srcB) {
    
    stat.setInput(D_stat);
    icode.setInput(D_icode);
    ifun.setInput(D_ifun);
    valC.setInput(D_valC);
    valA.setInput(d_valA);
    valB.setInput(d_valB);
    dstE.setInput(d_dstE);
    dstM.setInput(d_dstM);
    srcA.setInput(d_srcA);
    srcB.setInput(d_srcB);

}