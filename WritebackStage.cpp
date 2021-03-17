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
    W_valE.reset();
    W_valM.reset();      
    W_dstE.reset(RNONE);
    W_dstM.reset(RNONE);    
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
    W_valE.clock();
    W_valM.clock();      
    W_dstE.clock();
    W_dstM.clock();    
  
    
}
/*---------------------------------------------------------------------------
    clockP1 - (pure virtual from PipeStage)
         Performs operations of clock Phase1 for this stage
-----------------------------------------------------------------------------*/
void WritebackStage::clockP1()
{
    
}

void WritebackStage::updateWRegister(uint64_t M_stat, uint64_t M_icode, uint64_t M_ifun, uint64_t M_valE, uint64_t M_valM, uint64_t M_dstE, uint64_t M_dstM) 
{ // fix params

    stat.setInput(M_stat);
    icode.setInput(M_icode);
    ifun.setInput(M_ifun);
    W_valE.setInput(M_valE);
    W_valM.setInput(M_valM);
    W_dstE.setInput(M_dstE);
    W_dstM.setInput(M_dstM);


    
}

