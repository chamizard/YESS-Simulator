/*
    File:   Decode Stage.cpp
    Desc:   Decode Stage implementation for Y86-64 simulator
    
    Authors: Cameron Mann and Milton Barba
    
    Last update:  Spring 2021
    
*/
#include "Y86.h"
#include "DecodeStage.h"

/*---------------------------------------------------------------------------
    reset- used to connect to other Y86 components
     
-----------------------------------------------------------------------------*/
void DecodeStage::reset(ExecuteStage *pexecute, ProgRegisters *pprogreg)
{
		executeStage = pexecute;    // "Connect" decode stage to execute stage with pointer to ExecuteStage
		regs = pprogreg;            // Provide pointer to ProgRegisters
		stat.reset();               // sets stat to SBUB (0)
        icode.reset(INOP);          // sets icode to INOP (1)
        ifun.reset();               // sets ifun to FNONE (0)
        rA.reset(RNONE);          // Reset the D_rA register to RNONE (15)
        rB.reset(RNONE);          // Reset the D_rB register to RNONE (15)
        valC.reset();             // Reset the D_valC register to 0
        valP.reset();             // Reset the D_valP register to 0
}

/*---------------------------------------------------------------------------
    clockP0 - (pure virtual from PipeStage)
         Performs operations of clock Phase0 for this stage
-----------------------------------------------------------------------------*/
void DecodeStage::clockP0()
{
  // Must implement clockP0 since it is declared pure-virtual 

    stat.clock();
    icode.clock();
    ifun.clock();
    rA.clock();
    rB.clock();
    valC.clock();
    valP.clock();

    valA = 0;
    valB = 0;
    srcA = RNONE;
    srcB = RNONE;
    dstE = RNONE;
    dstM = RNONE;
}
/*---------------------------------------------------------------------------
    clockP1 - (pure virtual from PipeStage)
         Performs operations of clock Phase1 for this stage
-----------------------------------------------------------------------------*/
void DecodeStage::clockP1()
{
    executeStage->updateERegister(stat.getState(), icode.getState(), ifun.getState(), valC.getState(), valA, valB, dstE, dstM, srcA, srcB);
}

void DecodeStage::updateDRegister(uint64_t f_stat, uint64_t f_icode, uint64_t f_ifun, uint64_t f_rA,
    uint64_t f_rB, uint64_t f_valC, uint64_t f_valP) {

    stat.setInput(f_stat);
    icode.setInput(f_icode);
    ifun.setInput(f_ifun);
    rA.setInput(f_rA);
    rB.setInput(f_rB);
    valC.setInput(f_valC);
    valP.setInput(f_valP);
    
}