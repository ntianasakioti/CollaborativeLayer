#include "CommInt.h"

CommInt::CommInt()
{
	//TO DO: read module id from file
	moduleId = 0; 

	Comm::GetInstance()->Init(); 
	// Create singular Comm instance if it hasn't been 
	// created already
	Comm::GetInstance()->AddMsgQueue();
}

CommInt::~CommInt()
{

}

bool CommInt::CheckForMessage(int moduleId)
{
	return Comm::GetInstance()->CheckForMessage(moduleId);
}

int CommInt::SendMessage(std::string dest, int * dataBuffer)
{
	if(dest == "All")
	{
		return Comm::GetInstance()->SendBd(dataBuffer);
		std::cout << "Done sending Bd at CommInt" << std::endl; 
	}
	else
	{
		return Comm::GetInstance()->SendPtoP(dataBuffer, dest);
		std::cout << "Done Sending PtP at CommInt" << std::endl; 
	}
	return 0;
}

Message * CommInt::GetMessage(int moduleId)
{
	return Comm::GetInstance()->GetMessage(moduleId);
}

