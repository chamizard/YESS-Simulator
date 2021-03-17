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
    Register <uint64_t> M_Cnd;
    Register <uint64_t> M_valE;
    Register <uint64_t> M_valA;
    Register <uint64_t> M_dstE;
    Register <uint64_t> M_dstM;

    /* Pointer to Writeback Stage and Memory object */
    WritebackStage *writebackStage;
    Memory *memory;
	
	
    /* signals produced within the stage - Use names similar to Figure 4.57 p. 448 of text */
    uint64_t m_valM;
    uint64_t m_stat;
    uint64_t dmem_error;

	/* Private methods - These are internal to the Decode Stage */
       
	
	public:
		void reset(WritebackStage *, Memory *);
        void updateMRegister();

		/* (Virtual) Functions of superclass */
		void clockP0();
		void clockP1();
		void trace();
    
    
};

#endif