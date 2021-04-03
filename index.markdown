---
layout: default
title: "Main Page"
---
Introduction
===========

This project was written as a part of a systems course with the intent of furthering the understanding of computer's underlying systems and their interactions.  

This project is a work-in-progress and not fully completed. Forwarding, stalling, and bubbling have yet to be implemented.  

Currently the only working instruction are: NOP and HALT.

***

Requirements
===========

1. Understand how the Y86-64 operates.  

2. Either:  
a. Have access to assembled .yo files  
*OR*  
b. Be able to write assembly files using the Y86-64 instruction set and assemble them into .yo files  

3. Be able to use a command line and command line arguments
4. Have access to a Unix environment (as currently the project does not support Windows or MacOS operating systems)


***

Installation
===========

1. Clone the repository:  
![clone](assets/images/clone.png "clone")

2. Compile the project.  
Use the make command or see the 'makefile' for dependancies.

![make](assets/images/make.png "make")

A yess executable should be produced.

![yess.exe](assets/images/exe.png "yess.exe")

Once you have a yess executable you are ready to begin use.

***

Instructions for Use
===========

The yess executable is invoked from the command line as so:

`./yess [OPTIONS] [PATH/FILE]`

Where `[OPTIONS]` denotes the following flags:

- `-f` : print the trace output of the fetch stage 
- `-d` : print the trace output of the decode stage
- `-e` : print the trace output of the execute stage
- `-m` : print the trace output of the memory stage
- `-w` : print the trace output of the writeback stage

And `[PATH/FILE]` is the path to the file.

An example:

`./yess -fdemw sumabs.yo`  

runs the yess executable on the file 'sumabs.yo' and prints the trace output of each stage.  

*NOTE: the above command assumes the 'sumabs.yo' file is in the same directory as the yess executable*

If the file being used is incorrectly formatted then an error will be produced and execution terminated.

***

Example File
===========
Below is the example file 'sumabs.yo' used above:

                                | # 
                                | # Calculates the sum of the absolute values of all elements in list.
                                | #
    0x000:                      | 			.pos 0
    0x000: 30f40002000000000000 | main:		irmovq	stack,%rsp
    0x00a: 30f69000000000000000 | 			irmovq	count,%rsi
    0x014: 50660000000000000000 | 			mrmovq	(%rsi),%rsi
    0x01e: 30f79800000000000000 | 			irmovq	list,%rdi
    0x028: 803200000000000000   | 			call	sumabs
    0x031: 00                   | 			halt
                                | 
    0x032:                      | sumabs:
                                | 			
    0x032: 30f2ffffffffffffffff | 		    irmovq  -1, %rdx
    0x03c: 30f30800000000000000 | 		    irmovq  8, %rbx
    0x046: 50170000000000000000 |             mrmovq  (%rdi), %rcx      # put list value in rcx
    0x050: 6211                 |             andq    %rcx, %rcx        # check if negative
    0x052: 727300000000000000   |             jl      neg               # jump to negative
    0x05b: 6010                 |             addq    %rcx, %rax        # positive add to rax
    0x05d: 6026                 |             addq    %rdx, %rsi        # decrement count
    0x05f: 738f00000000000000   |             je      done              # done if list empty
    0x068: 6037                 |             addq    %rbx, %rdi        # increment list pointer
    0x06a: 703200000000000000   |             jmp     sumabs            # if not back to top
    0x073:                      | neg:    
    0x073: 6321                 |             xorq    %rdx, %rcx
    0x075: 6121                 |             subq    %rdx, %rcx        # invert negative
    0x077: 6010                 |             addq    %rcx, %rax        # add to rax
    0x079: 6026                 |             addq    %rdx, %rsi        # decrement count
    0x07b: 738f00000000000000   |             je      done              # done if list empty
    0x084: 6037                 |             addq    %rbx, %rdi        # increment list pointer
    0x086: 703200000000000000   |             jmp     sumabs
    0x08f:                      | done:
    0x08f: 90                   | 			ret     #return--result should be in %rax
                                | 
    0x090:                      | 			.align	8
    0x090: 0c00000000000000     | count:		.quad	12
    0x098:                      | list:
    0x098: fcffffffffffffff     | 			.quad	-4
    0x0a0: 0700000000000000     | 			.quad	7
    0x0a8: f6ffffffffffffff     | 			.quad	-10
    0x0b0: faffffffffffffff     | 			.quad	-6
    0x0b8: 0f00000000000000     | 			.quad	15
    0x0c0: 0100000000000000     | 			.quad	1
    0x0c8: f8ffffffffffffff     | 			.quad	-8
    0x0d0: eaffffffffffffff     | 			.quad	-22
    0x0d8: 1100000000000000     | 			.quad	17
    0x0e0: f2ffffffffffffff     | 			.quad	-14
    0x0e8: fbffffffffffffff     | 			.quad	-5
    0x0f0: 0d00000000000000     | 			.quad	13
                                | 	
    0x200:                      | 			.pos	0x200
    0x200:                      | stack:












***

FAQs
===========

> When will this projected be completed?

This project is apart of my current coursework and should be completed by mid-May at the latest.

> Will this project ever recieve a Windows/MacOS port?

Perhaps, but it certainly wouldn't be until after the project is completed.

> Where can I find an assembler for the Y86-64?

I cannot provide one. However, there are many out there on the internet available for use. It would be my recommendation to obtain one so that your .yo files may be formatted correctly.

***

Y86-64 Resources
===========

Familiarize yourself with the Y86-64 with these resources:

[General Instruction Set Architecture Overview (Video)](https://www.youtube.com/watch?v=1KTW32xSs_k)

[Y86-64 Instruction Set Overview](https://csit.kutztown.edu/~schwesin/fall20/csc235/lectures/Instruction_Set_Architecture.html)

[More In-Depth look at the Y86-64](http://kedizheng.com/2018/08/08/chapter-4/)

##### *Disclaimer: these resources are not my own and may contain incorrect information*

***

Troubleshooting / Support
===========

Create an issue on GitHub and/or email me at: <manncp@appstate.edu>

***

How to Contribute
===========

Create a new fork of the repository and submit a pull request.

***

Licensing
===========

Copyright (c) 2021 Cameron Mann

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.