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
    Register <uint64_t> rA;      // 
    Register <uint64_t> rB;
    Register <uint64_t> valC;
    Register <uint64_t> valP;

    /* Pointers to Execute Stage and Memory object */
    ExecuteStage *executeStage;
    ProgRegisters 		*regs;
	
	
    /* signals produced within the stage - Use names similar to Figure 4.57 p. 448 of text */
    uint64_t valA;
    uint64_t valB;
    uint64_t srcA;
    uint64_t srcB;
    uint64_t dstE;
    uint64_t dstM;

	/* Private methods - These are internal to the Decode Stage */
       
	
	public:
		void reset(ExecuteStage *, ProgRegisters *);
        void updateDRegister(uint64_t f_stat, uint64_t f_icode, uint64_t f_ifun, uint64_t f_rA,
                                uint64_t f_rB, uint64_t f_valC, uint64_t f_valP); // fix params

		/* (Virtual) Functions of superclass */
		void clockP0();
		void clockP1();
		void trace();
    
    
};

#endif