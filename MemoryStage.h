/*
    File:   MemoryStage.h
    Desc:   Declares MemoryStage class and associated constants
    
*/
#ifndef MEMORYSTAGE_H
#define MEMORYSTAGE_H


#include "Sim.h"
#include "PipeStage.h"
#include "Register.h"
#include "WritebackStage.h"


class MemoryStage : public PipeStage
{

    /* Register state */
    Register <uint64_t> cnd;
    Register <uint64_t> valE;
    Register <uint64_t> valA;
    Register <uint64_t> dstE;
    Register <uint64_t> dstM;

    /* Pointer to Writeback Stage and Memory object */
    WritebackStage *writebackStage;
    Memory *memory;
	
	
    /* signals produced within the stage - Use names similar to Figure 4.57 p. 448 of text */
    uint64_t m_valM;
    uint64_t m_stat;
    uint64_t dmem_error;

	/* Private methods - These are internal to the Memory Stage */
       
	
	public:
		void reset(WritebackStage *, Memory *);
        void updateMRegister(uint64_t E_stat, uint64_t E_icode, uint64_t E_ifun, uint64_t E_Cnd, 
                                uint64_t E_valA, uint64_t E_valB, uint64_t E_dstE, uint64_t E_dstM);

		/* (Virtual) Functions of superclass */
		void clockP0();
		void clockP1();
		void trace();
    
    
};

#endif