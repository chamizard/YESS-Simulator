/*
    File:   main.cpp
    Desc:   The main program. Accepts and verifies parameters and executes simulator
            on the specified object file. Other parameters are used to specify the stage or
            stages where trace outputs will be printed. Trace outputs may include the 
            stage register contents, memory contents, and/or register contents. Trace outputs
            are printed at the end of a cycle.
            
*/
#include <iostream>
#include <iomanip>
#include <string>
#include "Sim.h"
#include "Y86.h"
#include "Memory.h"
#include "ProgRegisters.h"

#define 	MEM_SIZE_BYTES		8192

using namespace std;

Y86 y86;  // Declare global Y86 object. 

//------------------------------------------------------------------
// functions
//------------------------------------------------------------------
void usage(void);

int main(int argc, char *argv[])
{
	if (argc < 2){
		usage();
		return 0;
	}
    
    y86.reset();
	y86.load(argv[1]);
	y86.dumpProcessorRegisters();
	y86.dumpProgramRegisters();
	y86.dumpMemory();
        
}

void usage(void)
{
    printf("Usage: yess <objectfile>\n"
          "<objectfile> must be created with the Y86 assembler 'yas' (has .yo extension.)\n");
    exit(0);
}

