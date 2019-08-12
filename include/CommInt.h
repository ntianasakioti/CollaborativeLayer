#ifndef COMMINT_H
#define COMMINT_H

#include "Comm.h"

class CommInt
{
public:
	CommInt();
	~CommInt();
	bool CheckForMessage();
	int SendMessage(std::string dest, std::string message);
	std::string GetMessage();
protected:

private:
	int moduleId; 
	//static int counter = 0;
}; 

#endif