/*
    File:   Execute Stage.cpp
    Desc:   Execute Stage implementation for Y86-64 simulator
    
    Authors: Cameron Mann and Milton Barba
    
    Last update:  Spring 2021
    
*/
#include "Y86.h"
#include "ExecuteStage.h"
#include "Forward.h"
#include "ProgRegisters.h"

/*---------------------------------------------------------------------------
    reset- used to connect to other Y86 components
     
-----------------------------------------------------------------------------*/
void ExecuteStage::reset(MemoryStage *pmemoryStage, ProgRegisters *preg, Forward *pforward)
{
	memoryStage = pmemoryStage;
    regs = preg;
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

    // Initialize internal signals to default values
    valE = 0;
    e_dstE = 0;
    e_icode = 0;
    aluA = 0;
    aluB = 0;
    aluFun = 0;
    set_cc = false;
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
    e_icode = icode.getState();
    ifun.clock();
    valC.clock();
    valA.clock();      
    valB.clock();
    dstE.clock();
    dstM.clock();
    srcA.clock();
    srcB.clock();
    cnd.clock();
    
    getALUA();
    getALUB();
    getALUFunction();
    isSetCC();
    selectDstE();
    if (aluFun == FADDQ) {
        valE = aluA + aluB;
        setFlags(valE);
    } else if (aluFun == FSUBQ) {
        valE = aluA - aluB;
        setFlags(valE);
    } else if (aluFun == FANDQ) {
        valE = aluA & aluB;
        setFlags(valE);
    } else if (aluFun == FXORQ) {
        valE = aluA ^ aluB;
        setFlags(valE);
    }
}
/*---------------------------------------------------------------------------
    clockP1 - (pure virtual from PipeStage)
         Performs operations of clock Phase1 for this stage
-----------------------------------------------------------------------------*/
void ExecuteStage::clockP1()
{
    memoryStage->updateMRegister(stat.getState(), icode.getState(), ifun.getState(), true, valE, valA.getState(), dstE.getState(), dstM.getState());
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

void ExecuteStage::isSetCC() {
    if (e_icode == IOPX) {
        set_cc = true;
    } else {
        set_cc = false;
    }
}

void ExecuteStage::getALUA() {
    if (e_icode == IRRMOVQ || e_icode == IOPX) {
        aluA = valA.getState();
    } else if (e_icode == IIRMOVQ || e_icode == IRMMOVQ || e_icode == IMRMOVQ) {
        aluA = valC.getState();
    } else if (e_icode == ICALL || e_icode == IPUSHQ) {
        aluA = -8;
    } else if (e_icode == IRET || e_icode == IPOPQ) {
        aluA = 8;
    }
}

void ExecuteStage::getALUB() {
    if (e_icode == IRMMOVQ || e_icode == IMRMOVQ || e_icode == IOPX || e_icode == ICALL || e_icode == IPUSHQ || e_icode == IRET || e_icode == IPOPQ) {
        aluB = valB.getState();
    } else if (e_icode == IRRMOVQ || e_icode == IIRMOVQ) {
        aluB = 0;
    }
}

void ExecuteStage::getALUFunction() {
    if (e_icode == IOPX) {
        aluFun = ifun.getState();
    } else {
        aluFun = FADDQ;
    }
}

void ExecuteStage::selectDstE() {
    if (e_icode == IRRMOVQ && !cnd.getState()) {
        e_dstE = RNONE;
    } else {
        e_dstE = dstE.getState();
    }
}

void ExecuteStage::setFlags(uint64_t val) {
    if (val < 0) {
            regs->setCC(SF, 1);
        } else if (val > 0) {
            regs->setCC(OF, 1);
        } else {
            regs->setCC(ZF, 1);
        }
}