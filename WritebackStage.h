/*
    File:   WritebackStage.h
    Desc:   Declares WritebackStage class and associated constants
    
*/
#ifndef WRITEBACKSTAGE_H
#define WRITEBACKSTAGE_H


#include "Sim.h"
#include "PipeStage.h"
#include "Register.h"
#include "Forward.h"


class WritebackStage : public PipeStage
{

    /* Register state */
    Register <uint64_t> valE;      // 
    Register <uint64_t> valM;
    Register <uint64_t> dstE;
    Register <uint64_t> dstM;
    
    
    /* Pointer to ProgRegisters object and Forward object*/
    ProgRegisters   *regs;
    Forward         *forward;
	
	
    /* signals produced within the stage - Use names similar to Figure 4.57 p. 448 of text */
    

	/* Private methods - These are internal to the Writeback Stage */
       
	
	public:
		void reset(ProgRegisters *, Forward *);
        void updateWRegister(uint64_t M_stat, uint64_t M_icode, uint64_t M_ifun, uint64_t M_valE, uint64_t M_valM, uint64_t M_dstE, uint64_t M_dstM);

		/* (Virtual) Functions of superclass */
		void clockP0();
		void clockP1();
		void trace();
    
    
};

#endif