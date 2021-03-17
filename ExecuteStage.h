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
    Register <uint64_t> E_valC;
    Register <uint64_t> E_valA;
    Register <uint64_t> E_valB;
    Register <uint64_t> E_dstE;
    Register <uint64_t> E_dstM;
    Register <uint64_t> E_srcA;
    Register <uint64_t> E_srcB;

    /* Pointer to Memory Stage */
    MemoryStage *memoryStage;
	
	
    /* signals produced within the stage - Use names similar to Figure 4.57 p. 448 of text */
    uint64_t e_valE;
    uint64_t e_dstE;
    uint64_t e_Cnd;

	/* Private methods - These are internal to the Decode Stage */
       
	
	public:
		void reset(MemoryStage *);
        void updateERegister(); // fix params

		/* (Virtual) Functions of superclass */
		void clockP0();
		void clockP1();
		void trace();
    
    
};

#endif