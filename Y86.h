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
#include <stdint.h>
#include "FetchStage.h"
#include "DecodeStage.h" 
#include "ExecuteStage.h" 
#include "MemoryStage.h" 
#include "WritebackStage.h"


//class PipeStage;  // Forward declare because of PipeStage reference array

class Y86 {

    Memory              memory;          
    ProgRegisters       regs;
	
    FetchStage fetchStage;
    DecodeStage decodeStage;
    ExecuteStage executeStage;
    MemoryStage memoryStage;
    WritebackStage writebackStage;

    PipeStage *stage[5];  // an array of 5 PipeStage pointers

    int cycles;           // cycle count

    /* Private member functions */
    void 		getLine			(uint64_t * line, uint64_t address);
    uint64_t    getByte         (std::string input);
	
	std::string getFlagsString	(void); // in Y86trace.cpp
	
    /* Public member functions */
    public:
        Y86();
        void reset();
		void clock();
		bool load(char *fname);  // takes name of a file as a C string
		void dumpMemory();			
		void dumpProgramRegisters();
		void dumpProcessorRegisters();
		int writeMemory (std::string inst, int numBytes, uint64_t address);
        void setTrace(bool f, bool d, bool e, bool m, bool w);
        void trace(void);
        uint64_t getStat(void);
        int getCycles(){return cycles;}; //Note that this is implemented here
        Memory& getMemory(){return memory;}  
        ProgRegisters& getProgRegisters(){return regs;}
};

#endif