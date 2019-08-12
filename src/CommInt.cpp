#include "CommInt.h"

CommInt::CommInt()
{
	moduleId = 0; 

	Comm::GetInstance()->Init(); 
	// Create singular Comm instance if it hasn't been 
	// created already
	Comm::GetInstance()->AddMsgQueue();
}

CommInt::~CommInt()
{

}

bool CommInt::CheckForMessage()
{
	return Comm::GetInstance()->CheckForMessage();
}

int CommInt::SendMessage(std::string message, std::string dest)
{
	if(dest == "All")
		Comm::GetInstance()->SendBd(message);
	else
		Comm::GetInstance()->SendPtoP(message, dest);

	return 0;
}

std::string CommInt::GetMessage()
{
	return Comm::GetInstance()->GetMessage();
}

