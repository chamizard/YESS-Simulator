/*
    Name:   Memory.cpp
    Desc:   Implementation of the Memory class
    Auth:   Cameron Mann & Milton Barba
    Date:   2/8/2021 Spring 2021
*/
#include <iostream>
#include <iomanip>
#include <cstdint>
#include <stdint.h>

#include "Memory.h"
#include "Tools.h"

/*-------------------------------------------------------------------------
  Constructor:  Memory 
  Description:  Store 64-bit value to a word address in memory. Set
                memError if address out of bounds.
--------------------------------------------------------------------------*/
Memory::Memory()
{
    reset(); 
}
/*-------------------------------------------------------------------------
  Function:     store 
  Description:  Store 64-bit value to a word address in memory. Set
                memError if address out of bounds.
--------------------------------------------------------------------------*/
void   Memory::store	(uint64_t waddr, uint64_t val) // takes word address
{
   if (waddr >= MEMORY_SIZE) {
      memError = true;
   } else {
      memError = false;
      mem[waddr] = val;
   }
   
}
/*-------------------------------------------------------------------------
  Function:     fetch 
  Description:  Fetch a 64-bit value from a word address in memory. Set
                memError if address out of bounds.
--------------------------------------------------------------------------*/
uint64_t  Memory::fetch	(uint64_t waddr) // takes word address
{
   if (waddr >= MEMORY_SIZE) 
   {
      memError = true;
      return 0;
   }
   else 
   {
      memError = false;
      return mem[waddr];
   }
}
/*--------------------------------------------------------------------
   Function:   getByte

   Description:  Returns a byte from the specified byte address
                 of Y86 memory array. 
                 If address is out of range the error status is set.
--------------------------------------------------------------------*/
unsigned char   Memory::getByte	(uint64_t byteAddress) // takes byte address
{
	if (byteAddress >= (MEMORY_SIZE * 8)) 
   {
      memError = true;
      return 0;
   }
   else
   {
      memError = false;
      uint64_t waddr = byteAddress / 8;
      uint64_t value = fetch(waddr);
      uint64_t byteVal = byteAddress %8;
      byte b = Tools::getByteNumber(byteVal, value);
      return b;
   }
}
/*--------------------------------------------------------------------
   Function:     putByte

   Description:  Write a single byte into the Y86 simulated memory
                 at the byte address specified by 'address'.
                 If address is out of range the error status is set.                 
--------------------------------------------------------------------*/
void  Memory::putByte(uint64_t byteAddress, uint8_t value) // takes byte address
{
   if (byteAddress >= (MEMORY_SIZE * 8))  
   {
      memError = true;
   }
   else
   {
      memError = false;
	   uint64_t waddr = byteAddress / 8;
      uint64_t word = fetch(waddr);
      uint64_t edit = Tools::putByteNumber(byteAddress % 8, value, word);
      store(waddr, edit);
   }
}
/*--------------------------------------------------------------------
   Function:   getWord

   Description:  Returns word starting from the specified byte address.
                 No part of the word must lie outside memory range.
--------------------------------------------------------------------*/
uint64_t   Memory::getWord	(uint64_t byteAddress)	
{
   if (byteAddress >= (MEMORY_SIZE * 8))  
   {
      memError = true;
   }
   memError = false;
   byte values[8];
   for (int i = 0; i < 8; i++) 
   {
      values[i] = getByte(byteAddress + i);
   }
   uint64_t result = Tools::buildWord(values[0], values[1], values[2], values[3], values[4], values[5], values[6], values[7]);
   return result;
}
/*----------------------------------------------------------------------------------------------
   Function:   putWord

   Description:  Writes a word to memory starting at the specified byte address.
                 No part of the word must lie outside memory range. If there is
				 a memory error (out of range) the memory should not be changed.
------------------------------------------------------------------------------------------------*/
void Memory::putWord	(uint64_t byteAddress, uint64_t wordValue) 
{
   if (byteAddress >= (MEMORY_SIZE * 8)) 
   {
      memError = true;
   }
   else
   {
      memError = false;
      byte values[8];
      for (int i = 0; i < 8; i++) {
         values[i] = Tools::getByteNumber(i, wordValue);
         putByte(byteAddress + i, values[i]);
      }
   }
}

/*--------------------------------------------------------------------
   Function:   reset

   Description:  Clears memory to all zero. Clears error status.
                 
--------------------------------------------------------------------*/
void  Memory::reset	(void) // clears memory to all zero
{
   for (int i = 0; i < MEMORY_SIZE - 1; i++) {
      store(i, 0);
   }
   memError = false;
}
