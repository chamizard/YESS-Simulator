CXX=g++
CXXFLAGS = -Wall -g -std=c++11

# Put object files in next line
OBJS = 

# The OBJTEST macro is same as 'OBJS' above except replace Sim.o with testSim.o 
OBJTEST =  

#complete the following targets with appropriate dependencies and commands
yess:	$(OBJS)

ytest:  $(OBJTEST)


#your object file targets below here...



# clean target
# Remeber, you don't want to delete your testSim.o file
# The following target preserves testSim.o
clean:
	cp testSim.o testSim-tmp
	rm *.o yess
	cp testSim-tmp testSim.o

