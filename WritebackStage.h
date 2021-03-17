/*
    File:   WritebackStage.h
    Desc:   Declares WritebackStage class and associated constants
    
*/
#ifndef WRITEBACKSTAGE_H
#define WRITEBACKSTAGE_H


#include "Sim.h"
#include "PipeStage.h"
#include "Register.h"


class WritebackStage : public PipeStage
{

    /* Register state */
    

    /* Pointer to ProgRegisters object */
    ProgRegisters *regs;
	
	
    /* signals produced within the stage - Use names similar to Figure 4.57 p. 448 of text */
    

	/* Private methods - These are internal to the Decode Stage */
       
	
	public:
		void reset(ProgRegisters *);
        void updateWRegister(); // fix params

		/* (Virtual) Functions of superclass */
		void clockP0();
		void clockP1();
		void trace();
    
    
};

#endif