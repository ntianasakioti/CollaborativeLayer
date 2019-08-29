#ifndef COMMINT_H
#define COMMINT_H

#include "Comm.h"

class CommInt
{
public:
	CommInt();
	~CommInt();
	bool CheckForMessage(int moduleId);
	int SendMessage(std::string dest, int * dataBuffer);
	Message * GetMessage(int moduleId);
protected:

private:
	int moduleId; 
	//static int counter = 0;
}; 

#endif