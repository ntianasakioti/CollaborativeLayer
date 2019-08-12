# Makefile for Parent_Comm project

CXX := g++
CXXFLAGS := -Wall -g -std=c++11

EXECUTABLE 			:= test_comm
SOURCEFILES			:= src/Comm.cpp src/CommInt.cpp src/BaseComm.cpp src/BlueComm.cpp src/RosComm.cpp src/Main.cpp 
LIBS				:= -L /usr/include/bluetooth/bluetooth.h -L /usr/include/bluetooth/rfcomm.h \
						-L /usr/include/pthread.h
INCLUDE 			:= -I include 
LDFLAGS 			:= -pthread -lbluetooth
# *********************************
# Targets needed to bring executable up to date

${EXECUTABLE}: $(SOURCEFILES)
	${CXX} -o ${EXECUTABLE} ${LIBS} ${CXXFLAGS} ${SOURCEFILES} ${INCLUDE} ${LDFLAGS}
clean:
	-$(RM) $(EXECUTABLE)\
	*.0 *.*log
run:
	./test_comm