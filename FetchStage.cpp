/*
    File:   FetchStage.cpp
    Desc:   Fetch Stage implementation for Y86-64 simulator
    Notes:  This is partially implemented. You are to fill in the incomplete methods and study
            the implementation to learn how other stages will be implemented.
    
    Authors: Cameron Mann and Milton Barba
    
    Last update:  Spring 2021
    
*/
#include "Y86.h"
#include "FetchStage.h"

/*---------------------------------------------------------------------------
    reset- used to connect to other Y86 components
     
-----------------------------------------------------------------------------*/
void FetchStage::reset(DecodeStage *pdecode, Memory *pmem)
{
		decodeStage = pdecode;  // "Connect" fetch stage to decode stage with pointer to DecodeStage
		memory = pmem;          // Provide pointer to Memory
		predPC.reset();         // Reset the predPC register
}

/*---------------------------------------------------------------------------
    clockP0 - (pure virtual from PipeStage)
         Performs operations of clock Phase0 for this stage
-----------------------------------------------------------------------------*/
void FetchStage::clockP0()
{
  // Must implement clockP0 since it is declared pure-virtual 

	// In Phase0 we (will in the future):
	//     Check for STALL or BUBBLE condition, update Register variable inputs
	//     		stall/bubble come from conditions in E, M, W stages (see HCL)
	//     Call the clock method on all Register variables
	//     Perform all Phase0 actions:
	//          For fetch, since selectPC uses outputs from other stages
	//			all stage operations happen during clock Phase1 (clockP1 method)
	//	
    predPC.clock();
  
	// Initialize internal signals to default values
    f_stat = SAOK;
    f_icode = INOP;
    f_ifun = FNONE;
    f_rA = RNONE;
    f_rB = RNONE;
    f_valC = 0;
    f_valP = 0;	
}
/*---------------------------------------------------------------------------
    clockP1 - (pure virtual from PipeStage)
         Performs operations of clock Phase1 for this stage
-----------------------------------------------------------------------------*/
void FetchStage::clockP1()
{
     
   // For fetch stage, all work done here (since we only know fetch address
   // when forwarding conditions are known (Memory and Writeback stages)
   // uint64_t opcode = memory->getByte(predPC.getState());
   // check for memory error after each memory access
   // check for illegal opcode
   f_PC = selectPC();

   // Get first byte of instruction (split into f_icode and f_ifun)
   // Check for any address errors, and if so, update the Decode register with status
   //
   if (!getByte0()) {
     //Generate SADR error status and NOP if memory error detected, set predPC to f_PC+1
     decodeStage->updateDRegister(SADR,INOP,FNONE,RNONE,RNONE,0UL,f_PC+1);
     predPC.setInput(f_PC+1);
	   return;
   }

   instrValid = checkInstrValid();
   if(!instrValid) {
     //Generate SINS error status and NOP if invalid instruction detected, set predPC to f_PC+1
     // Pass the bad icode on (f_icode) because it will be marked as <bad> in the trace output
     decodeStage->updateDRegister(SINS,f_icode,FNONE,RNONE,RNONE,0UL,f_PC+1);
     predPC.setInput(f_PC+1);
	   return;
   }
  
   needsRegs = checkNeedsRegs();
   
   needsValC = checkNeedsValC();
   
   // Uses needsRegs to fetch reg byte (rA and rB) and valC if needed
   if (!align()) {
     //Generate error status and NOP if memory error detected, set predPC to f_PC+1
     decodeStage->updateDRegister(SADR,INOP,FNONE,RNONE,RNONE,0UL,0UL);
     predPC.setInput(f_PC+1);
	   return;
   }

   // Determine f_valP 
   f_valP = f_PC + getPCIncrement();
   

   // Check for HALT instruction to update f_stat
   if (f_icode == IHALT)
     f_stat = SHLT;
   
   // Predict next PC and update Decode stage register
   predictPC();
	 decodeStage->updateDRegister(f_stat,f_icode,f_ifun, f_rA, f_rB, f_valC, f_valP);
	
}
/*----------------------------------------------------------------------------
   getByte0 - Gets first instruction byte and splits into icode and ifun 
            - checks for memory error and returns true if no memory error,
               false otherwise
------------------------------------------------------------------------------
*/
bool FetchStage::getByte0(){
   
   // TODO:  Your code here...



   return true;   // Might return false if memory error detected
}
/*----------------------------------------------------------------------------
   checkInstrValid - returns true if valid instruction, false otherwise
------------------------------------------------------------------------------*/
bool FetchStage::checkInstrValid(){

  if (f_icode == INOP || f_icode == IHALT || f_icode == IRRMOVQ || f_icode == IIRMOVQ
    || f_icode == IRMMOVQ || f_icode == IMRMOVQ || f_icode == IOPX || f_icode == IJXX ||
    f_icode == ICALL || f_icode == IRET || f_icode == IPUSHQ || f_icode == IPOPQ) {
      return true;
    } else {
      return false;
    }
}

/*-----------------------------------------------------------------------------------------------------
    checkNeedsRegs - returns true if instruction requires a register byte, false otherwise
-----------------------------------------------------------------------------------------------------*/
bool FetchStage::checkNeedsRegs(){

  // TODO:  Your code here

}
/*-----------------------------------------------------------------------------------------------------
    checkNeedsValC - returns true if instruction requires valC, false otherwise
-----------------------------------------------------------------------------------------------------*/
bool FetchStage::checkNeedsValC(){

  // TODO:  Your code here

}
/*-----------------------------------------------------------------------------------------------------
    align - Models the align function in the PIPE diagram. 
            Uses needsRegs and needsValC booleans to determine what bytes are needed.
            Reads memory and assigns values to f_rA, f_rB, f_valC as needed. 
            Returns true if memory access OK, false if memory error
-----------------------------------------------------------------------------------------------------*/
bool FetchStage::align(){

  if (needsRegs) {
    uint64_t byteAddress = f_PC + 1;
    byte regByte = memory.getByte(regByte);
    f_rA = (((~regByte) ^ 0xF0) & 0xF0);
    f_rB = (((~regByte) ^ 0xF) & 0xF);
  }
  if (needsValC) {
    uint64_t valC = memory.getWord(f_PC);
    f_valC = (((~valC) ^ 0x00FFFFFFFF) & 0x00FFFFFFFF)
  }
  if (memory.isError()) {
    return true;
  }
  return false;
}
/*-----------------------------------------------------------------------------------------------------
    getPCIncrement - returns the size of the instruction in Fetch stage
-----------------------------------------------------------------------------------------------------*/
int FetchStage::getPCIncrement(){

  if (needsRegs && !needsValC) {
    return 2;
  } else if (needsValC) {
    return 10;
  } else if (icode == JXX || icode == ICALL) {
    return 9;
  }
  return 1; // This is not correct--depends on needsRegs and needsValC (either 1, 2, 9, or 10)
}
/*----------------------------------------------------------------------------
   predictPC - updates predPC based on f_icode, f_valC and f_valP
----------------------------------------------------------------------------*/
void FetchStage::predictPC()
{
    // For now we use f_valP as predicted PC. Later we'll update for
    // Jxx and CALL instructions to fully implement HCL
    predPC.setInput(f_valP);
}
/*----------------------------------------------------------------------------
   selectPC - select next PC 
----------------------------------------------------------------------------*/
uint64_t FetchStage::selectPC()
{
	// For now, selectPC returns predicted PC
  // Later will have to add logic to select from forwarded values based on JXX and RET
    return predPC.getState();
}
