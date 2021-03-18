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
    stat.reset();
    icode.reset(INOP);
    ifun.reset();  
    valE.reset();
    valM.reset();      
    dstE.reset(RNONE);
    dstM.reset(RNONE);    
}

/*---------------------------------------------------------------------------
    clockP0 - (pure virtual from PipeStage)
         Performs operations of clock Phase0 for this stage
-----------------------------------------------------------------------------*/
void WritebackStage::clockP0()
{
  // Must implement clockP0 since it is declared pure-virtual 
    
    stat.clock();
    icode.clock();
    ifun.clock();  
    valE.clock();
    valM.clock();      
    dstE.clock();
    dstM.clock();    
  
    
}
/*---------------------------------------------------------------------------
    clockP1 - (pure virtual from PipeStage)
         Performs operations of clock Phase1 for this stage
-----------------------------------------------------------------------------*/
void WritebackStage::clockP1()
{
    
}

void WritebackStage::updateWRegister(uint64_t M_stat, uint64_t M_icode, uint64_t M_ifun, uint64_t M_valE, uint64_t M_valM, uint64_t M_dstE, uint64_t M_dstM) 
{

    stat.setInput(M_stat);
    icode.setInput(M_icode);
    ifun.setInput(M_ifun);
    valE.setInput(M_valE);
    valM.setInput(M_valM);
    dstE.setInput(M_dstE);
    dstM.setInput(M_dstM);


    
}

