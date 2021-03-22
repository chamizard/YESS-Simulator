/*
    File:   Forward.h
    Desc:   Declares Forward class and associated constants
    
*/
#ifndef FORWARD_H
#define FORWARD_H

#include <cstdint>


class Forward
{

    /* Register state */
    // Predicted PC value stored in F Register
	
    /* Pointers to Decode Stage and Memory object */

	
	
    /* signals produced within the stage - Use names similar to Figure 4.57 p. 448 of text */
    uint64_t W_dstE;
    uint64_t W_valE;

	/* Private methods - These are internal to the Fetch Stage */
    uint64_t getW_dstE()
    {
        return W_dstE;
    }

    uint64_t getW_valE()
    {
        return W_valE;
    }

    void setW_dstE(uint64_t val)
    {
        W_dstE = val;
    }

    void setW_valE(uint64_t val)
    {
        W_valE = val;
    }

};

#endif