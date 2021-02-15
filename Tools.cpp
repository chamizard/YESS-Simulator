/*
    Utility functions (e.g., for bit/byte manipulations) used in Y86 simulator.
    
    Author:    
    version:    
*/
#include <cstdlib>
#include <iostream>
#include <cassert>
#include <cstdint>
#include "Tools.h"

#include <stdint.h>

namespace Tools {
    
/*-----------------------------------------------------------------------------------------------
    getBits
	Extracts bits 'low' to 'high' (inclusive) from 'source' and returns the result as
	an 64-bit integer. 
	Example:
	
	getBits(12,15,0x0123456789abcdef);
	
	would return the value:
	
	0x00000000000000c;
	
	(Bits 12-15 of the 64-bit word, counting from the right correspond to hex digit 'c' in the
	source word. Note that any number of bits from 1 to 64 could be specified depending on the values
	of 'low' and 'high'.
	The value of high must be greater than or equal to low and high must be in the range 0 to 63. 
------------------------------------------------------------------------------------------------*/
uint64_t getBits(unsigned low, unsigned high, uint64_t source)
{
    assert(high < 64 && (low <= high));
    uint64_t result = 0;
    
    int numBits = (high - low) + 1;
    int bitPos = (high - low); 
    for (int i = 1; i < numBits ; i++){
        result += 1;
        result = result << 1;
        if (i == bitPos) { result += 1; }
    }
    if (high == low){
        result = 1;
    }
    //printf("%lx\n", result);
    for (int i = bitPos; i < (int) high; i++){
        result = result << 1;
    }
    //printf("%lx\n", result);
    result = result & source;

    return result >> (int) low;
}
/*-----------------------------------------------------------------------------------------------
    setBits
	Sets (to 1) the bits from bit numbers 'low' to 'high' (inclusive) in 
	the source word and returns the resulting word.
	
	The value of high must be greater than or equal to low and high must be in the range 0 to 63. 
------------------------------------------------------------------------------------------------*/
uint64_t setBits(unsigned low, unsigned high, uint64_t source)
{
    assert(high < 64 && (low <= high));
    uint64_t result = 0;

    int numBits = (high - low) + 1;
    int bitPos = (high - low);
    if (high == low){
        result += 1;
    }
    for (int i = 1; i < numBits; i++){
        result += 1;
        result = result << 1;
        if (i == bitPos) { result += 1; }
    }
    for (int i = bitPos; i < (int) high; i++){
        result = result << 1;
    }
    result = result | source;
    return result;
}
/*-----------------------------------------------------------------------------------------------
    clearBits
	
	Clears (to 0) the bits from bit numbers 'low' to 'high' (inclusive) in 
	the source word and returns the resulting word.
	
	The value of high must be greater than or equal to low and high must be in the range 0 to 63. 
------------------------------------------------------------------------------------------------*/
uint64_t clearBits(unsigned low, unsigned high, uint64_t source)
{
    assert(high < 64 && (low <= high));
    uint64_t result = 0;

    int numBits = (high - low) + 1;
    int bitPos = (high - low);
    if (high == low){
        result += 1;
    }
    for (int i = 1; i < numBits; i++){
        result += 1;
        result = result << 1;
        if (i == bitPos) { result += 1; }
    }
    for (int i = bitPos; i < (int) high; i++){
        result = result << 1;
    }
    result = ~result;
    result = result & source;
    return result;
}

/*-----------------------------------------------------------------------------------------------
    assignOneBit
	Sets the bit number 'bitNum' to the binary value (0 or 1) specified by 'bitVal' in
	the source word and returns the resulting word.
	
	'bitNum' must be in the range 0 to 63 (inclusive) and 'bitVal' must be 0 or 1.
------------------------------------------------------------------------------------------------*/
uint64_t assignOneBit(unsigned bitNum, unsigned bitVal, uint64_t source)
{
    assert(bitNum < 64 && (bitVal == 1 || bitVal == 0));
    uint64_t result = 1;
    for (int i = 0; i < (int)bitNum; i++){
        result = result << 1;
    }
    //printf("%.16lx\n", result);
    if (bitVal == 1){
        result = result | source;
    } else if (bitVal == 0){
        result = ~result;
        result = result & source;
    }
    return result;
}

/*-----------------------------------------------------------------------------------------------
    getByteNumber
	Returns the specified byte number from the source word.
	
	Example:
	getByteNumber(3,0x0011223344556677);
	
	will return the single byte value:
	
	0x44
	
	(Note that the '3' refers to byte 3 of a 8-byte unsigned integer (bytes are numbered from
	the right starting at 0 when looking at a word value in hex). 
------------------------------------------------------------------------------------------------*/
uint8_t getByteNumber(unsigned byteNum, uint64_t source)
{
    assert(byteNum < 8 && byteNum >= 0);
    unsigned high = ((byteNum + 1) * 8 ) - 1;
    unsigned low = byteNum * 8;
    uint64_t result = getBits(low,high,source); 
    //uint64_t result = 0xff;
    /*printf("%x\n", (uint8_t)result);
    for (int i = 0; i < (int)byteNum; i++){
        result = result << 8;
    }
    printf("%x\n", (uint8_t)result);
    result =  result & source; */
    //printf("%lx\n", result);
    return  (uint8_t)result;
}
/*-----------------------------------------------------------------------------------------------
    putByteNumber
	Returns the source word after replacing the specified byte (byteNum) with a given 
	byte value (byteVal).
	
	Example:
	putByteNumber(3,0x00,0x0011223344556677);
	
	will return the value:
	
	0x0011223300556677
	
	(Note that the '3' refers to byte 3 of a 8-byte unsigned integer (bytes are numbered from
	the right starting at 0 when looking at a word value in hex). 
------------------------------------------------------------------------------------------------*/
uint64_t putByteNumber(unsigned byteNum, uint8_t byteVal, uint64_t source)
{
    assert(byteNum < 8 && byteNum >= 0 && byteVal <= 0xff && byteVal >= 0);
    unsigned high = ((byteNum + 1) * 8) - 1;
    unsigned low = byteNum * 8;
    source = clearBits(low,high,source);
    uint64_t result = (uint64_t)byteVal;
    //printf("%.16lx\n", (uint64_t)byteVal);
    for (int i = 0; i < (int)byteNum; i++){
        result = result << 8;
    }
    //printf("%.16lx\n", result);
    result = result | source; 
    return result;                  
}
/*-----------------------------------------------------------------------------------------------
    buildWord
	
	Returns a 64 bit word consisting of the 8 parameter bytes, where b0 is the least significant
	and b7 is the most significant byte.
------------------------------------------------------------------------------------------------*/
uint64_t buildWord(unsigned char b0, unsigned char b1,unsigned char b2, unsigned char b3,
                          unsigned char b4, unsigned char b5,unsigned char b6, unsigned char b7)
{
    //TODO: Add assertion?
    uint64_t result = 0;
    unsigned char values [8] = {b0,b1,b2,b3,b4,b5,b6,b7};
    for (int i = 0; i < 8; i++){
        result = putByteNumber(i,values[i],result);
    }
    return result;                     
}
/*-----------------------------------------------------------------------------------------------
    isNegative

	Returns true if the input parameter is negative when interpreted as a signed value.
------------------------------------------------------------------------------------------------*/
bool isNegative(uint64_t source)
{
    //TODO: Add assertion?
    if (getBits(60,63,source) > 7){
        return true;
    }
    return false;
}
/*-----------------------------------------------------------------------------------------------
    expandBits
	
	Reads the source and converts it to a character string consisting of 72 bytes--71 characters
	followed by a '\0' character (string terminator).
	Example usage: 
		char buf[72];
		expandBits(0xAABBCCDDEE001122UL,buf);

		Will cause the following string to be written to the buf[] array (not including quotes):
	
	"10101010 10111011 11001100 11011101 11101110 00000000 00010001 00100010"
	
	Note the space after every group of 8 digits except the last. The last byte of
	the string is the '\0' byte, that is not printable but used to indicate the end
	of a C string.
------------------------------------------------------------------------------------------------*/
void expandBits(uint64_t source, char *bits)
{
    assert(bits != NULL);
    int arrayIndex = 0;
    uint64_t compBit = 0x8000000000000000;
    for (int i = 64; i > 0; i--){
        //printf("%lx\n",bit);
        if (i != 64 && i % 8 == 0){
            bits[arrayIndex] = ' ';
            arrayIndex++;
        }
        if ((compBit & source) > 0){
            bits[arrayIndex] = '1';
        }else {
            bits[arrayIndex] = '0';
        }
        arrayIndex++;
        //printf("%lx\n", compBit);
        compBit = compBit >> 1;
    }
    bits[arrayIndex] = '\0';
}
/*-----------------------------------------------------------------------------------------------
    clearBuffer
	Treats pbuf as a pointer to an array of 'size' bytes and clears them all to zero.
------------------------------------------------------------------------------------------------*/
void clearBuffer(char * pbuf, int size)
{
    assert(pbuf != NULL && size >= 0 && size <= (2147486347));
    for (int i = 0; i < (size); i++){
        //if (pbuf[i] == ' '){i++;}
        pbuf[i] = 0;
    }
}

} // end namespace Tools
