/*
    File:   Decode Stage.cpp
    Desc:   Decode Stage implementation for Y86-64 simulator
    
    Authors: Cameron Mann and Milton Barba
    
    Last update:  Spring 2021
    
*/
#include "Y86.h"
#include "DecodeStage.h"
#include "Forward.h"

/*---------------------------------------------------------------------------
    reset- used to connect to other Y86 components
     
-----------------------------------------------------------------------------*/
void DecodeStage::reset(ExecuteStage *pexecute, ProgRegisters *pprogreg, Forward *pforward)
{
		executeStage = pexecute;    // "Connect" decode stage to execute stage with pointer to ExecuteStage
		regs = pprogreg;            // Provide pointer to ProgRegisters
        forward = pforward;         // Pointer to Forward object
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
    d_icode = icode.getState();
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
    getSrcA();
    getSrcB();
    valA = selectFwdA();
    valB = forwardB();
    getDstE();
    getDstM();
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

void DecodeStage::getSrcA() {
    if (d_icode == IRRMOVQ || d_icode == IRMMOVQ || d_icode == IOPX || d_icode == IPUSHQ) {
        srcA = rA.getState();
    }
    else if (d_icode == IPOPQ || d_icode == IRET) {
        srcA = RSP;
    } else {
        srcA = RNONE;
    }
}

void DecodeStage::getSrcB() {
    if (d_icode == IOPX || d_icode == IRMMOVQ || d_icode == IMRMOVQ) {
        srcB = rB.getState();
    }
    else if (d_icode == IPUSHQ || d_icode == IPOPQ || d_icode == ICALL || d_icode == IRET) {
        srcB = RSP;
    } else {
        srcB = RNONE;
    }
}

void DecodeStage::getDstE() {
    if (d_icode == IRRMOVQ || d_icode == IIRMOVQ || d_icode == IOPX) {
        dstE = rB.getState();
    } else if (d_icode == IPUSHQ || d_icode == IPOPQ || d_icode == ICALL || d_icode == IRET) {
        dstE = RSP;
    } else {
        dstE = RNONE;
    }
}

void DecodeStage::getDstM() {
    if (d_icode == IMRMOVQ || d_icode == IPOPQ) {
        dstM = rA.getState();
    } else {
        dstM = RNONE;
    }
}

uint64_t DecodeStage::selectFwdA() {
    uint64_t W_dstE = forward->getW_dstE();
    uint64_t W_valE = forward->getW_valE();
    if (d_icode == ICALL || d_icode == IJXX) {
        return valP.getState();
    } else if (srcA == W_dstE) {
        return W_valE;
    } else {
        if (srcA != RNONE) {
            return regs->getReg(srcA);
        }
        return 0;
    }
}

uint64_t DecodeStage::forwardB() {
    uint64_t W_dstE = forward->getW_dstE();
    uint64_t W_valE = forward->getW_valE();
    if (srcB == W_dstE) {
        return W_valE;
    } else {
        if (srcB != RNONE) {
            return regs->getReg(srcB);
        }
        return 0;
    }
}