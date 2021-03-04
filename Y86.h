/*
    File:   Y86.h
    Desc:   Y86 constants 
    
    Author: efb
*/

#ifndef Y86_H
#define Y86_H

#include <iostream>
#include <cstdint>
#include <string>
#include "Memory.h"
#include "ProgRegisters.h"


//class PipeStage;  // Forward declare because of PipeStage reference array

class Y86 {

    Memory              memory;          
    ProgRegisters       regs;
	
    /* Private member functions */
	bool 		readFile		(std::ifstream& infile);
	int 		writeMemory		(std::string inst, uint64_t address);
    void 		getLine			(uint64_t * line, uint64_t address);
	
	std::string getFlagsString	(void); // in Y86trace.cpp
	
    /* Public member functions */
    public:
        Y86();
        void reset();
		void clockP0();
		void clockP1();
		bool load(char *fname);  // takes name of a file as a C string
		void dumpMemory();			
		void dumpProgramRegisters();
		void dumpProcessorRegisters();
		
        Memory& getMemory(){return memory;}  
        ProgRegisters& getProgRegisters(){return regs;}
};

#endif