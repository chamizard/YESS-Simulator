/*
    File:   ExecuteStage.h
    Desc:   Declares ExecuteStage class and associated constants
    
*/
#ifndef EXECUTESTAGE_H
#define EXECUTESTAGE_H


#include "Sim.h"
#include "PipeStage.h"
#include "Register.h"
#include "MemoryStage.h"


class ExecuteStage : public PipeStage
{

    /* Register state */
    Register <uint64_t> valC;
    Register <uint64_t> valA;
    Register <uint64_t> valB;
    Register <uint64_t> dstE;
    Register <uint64_t> dstM;
    Register <uint64_t> srcA;
    Register <uint64_t> srcB;
    Register <bool> cnd;

    /* Pointer to Memory Stage */
    MemoryStage     *memoryStage;
    Forward         *forward;
	
	
    /* signals produced within the stage - Use names similar to Figure 4.57 p. 448 of text */
    uint64_t valE;
    uint64_t e_dstE;

	/* Private methods - These are internal to the Execute Stage */
       
	
	public:
		void reset(MemoryStage *, Forward *);
        void updateERegister(uint64_t D_stat, uint64_t D_icode, uint64_t D_ifun, uint64_t D_valC, 
                                uint64_t d_valA, uint64_t d_valB, uint64_t d_dstE, uint64_t d_dstM, 
                                uint64_t d_srcA, uint64_t d_srcB);

		/* (Virtual) Functions of superclass */
		void clockP0();
		void clockP1();
		void trace();
    
    
};

#endif