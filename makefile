CXX=g++
CXXFLAGS = -Wall -g -std=c++11

# Put object files in next line
OBJS = Sim.o Memory.o ProgRegisters.o Tools.o Y86.o

# The OBJTEST macro is same as 'OBJS' above except replace Sim.o with testSim.o 
OBJTEST =  testSim.o Memory.o ProgRegisters.o Tools.o Y86.o

#complete the following targets with appropriate dependencies and commands
yess:	$(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o yess

ytest:  $(OBJTEST)
	$(CXX) $(CXXFLAGS) $(OBJTEST) -o ytest


#your object file targets below here...

Sim.o: Sim.h Sim.cpp Y86.cpp Y86.h Memory.h ProgRegisters.h 

Memory.o: Memory.cpp Memory.h Tools.cpp Tools.h

ProgRegisters.o: ProgRegisters.cpp ProgRegisters.h

Tools.o: Tools.cpp Tools.h

Y86.o: Y86.cpp Y86.h

# clean target
# Remeber, you don't want to delete your testSim.o file
# The following target preserves testSim.o
clean:
	cp testSim.o testSim-tmp
	rm *.o yess
	cp testSim-tmp testSim.o

