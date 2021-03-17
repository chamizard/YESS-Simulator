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
        D_rA.reset(RNONE);          // Reset the D_rA register to RNONE (15)
        D_rB.reset(RNONE);          // Reset the D_rB register to RNONE (15)
        D_valC.reset();             // Reset the D_valC register to 0
        D_valP.reset();             // Reset the D_valP register to 0
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
    D_rA.clock();
    D_rB.clock();
    D_valC.clock();
    D_valP.clock();
}
/*---------------------------------------------------------------------------
    clockP1 - (pure virtual from PipeStage)
         Performs operations of clock Phase1 for this stage
-----------------------------------------------------------------------------*/
void DecodeStage::clockP1()
{
    executeStage->updateERegister(stat, icode, ifun, D_valC, d_valA, d_valB, d_dstE, d_dstM, d_srcA, d_srcB);
}

void DecodeStage::updateDRegister(uint64_t f_stat, uint64_t f_icode, uint64_t f_ifun, uint64_t f_rA,
    uint64_t f_rB, uint64_t f_valC, uint64_t f_valP) {

    stat.setInput(f_stat);
    icode.setInput(f_icode);
    ifun.setInput(f_ifun);
    D_rA.setInput(f_rA);
    D_rB.setInput(f_rB);
    D_valC.setInput(f_valC);
    D_valP.setInput(f_valP);
    
}