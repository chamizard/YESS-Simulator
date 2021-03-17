/*
    File:   DecodeStage.h
    Desc:   Declares DecodeStage class and associated constants
    
*/
#ifndef DECODESTAGE_H
#define DECODESTAGE_H


#include "Sim.h"
#include "PipeStage.h"
#include "Register.h"
#include "ExecuteStage.h"


class DecodeStage : public PipeStage
{

    /* Register state */
    Register <uint64_t> D_rA;      // 
    Register <uint64_t> D_rB;
    Register <uint64_t> D_valC;
    Register <uint64_t> D_valP;

    /* Pointers to Execute Stage and Memory object */
    ExecuteStage *executeStage;
    ProgRegisters 		*regs;
	
	
    /* signals produced within the stage - Use names similar to Figure 4.57 p. 448 of text */
    uint64_t d_valA;
    uint64_t d_valB;
    uint64_t d_srcA;
    uint64_t d_srcB;
    uint64_t d_dstE;
    uint64_t d_dstM;

	/* Private methods - These are internal to the Decode Stage */
       
	
	public:
		void reset(ExecuteStage *, ProgRegisters *);
        void updateDRegister();

		/* (Virtual) Functions of superclass */
		void clockP0();
		void clockP1();
		void trace();
    
    
};

#endif