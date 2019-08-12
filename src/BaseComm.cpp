#include "BaseComm.h"


std::vector<std::vector<std::string>> BaseComm::messageBacklog; 

void BaseComm::Init()
{
	std::ifstream inf("config/nameIDs.txt"); 

	int id;
	std::string friendlyName; 
	int numAs;
	inf >> numAs; 
	
	while((inf>> id).good() && (inf>> friendlyName).good())
	{
	//	inf >> id; inf >> friendlyName;
		//std::cout << id << " " << friendlyName << std::endl << std::flush; 
		nameIDs.insert(std::make_pair(friendlyName,id));
	}
	inf.close(); 
}

bool BaseComm::CheckForMessage(int moduleId)
{
	if(messageBacklog[moduleId].size() > 0)
		return true;
	else
		return false; 
}

std::string BaseComm::GetMessage(int moduleId)
{
	return "false";
}

void BaseComm::UpdateMessageLog(std::string s)
{
	std::cout << "Pushing back another message" << std::endl; 
	messageBacklog[0].push_back(s);
}

void BaseComm::AddMessageQueue()
{
	
}

void BaseComm::UpdateMsgLogNum()
{
	
	// Create and add anothe vector to MessageBacklog
	std::vector<std::string> anotherMsgLog; 
	messageBacklog.push_back(anotherMsgLog);
}

void BaseComm::MutexLock()
{
	messageMutex.lock();
}

void BaseComm::MutexUnlock()
{
	messageMutex.unlock();
}

int BaseComm::GetMessageLogSize()
{
	return messageBacklog[0].size(); 
}

int BaseComm::GetId(std::string name)
{
	std::cout << "Name " << name << std::endl; 

	std::map<std::string,int>::iterator it = nameIDs.begin();

	for(int i = 0 ; i < nameIDs.size(); i++)
	{
		std::cout << it->first << std::endl; 
		if(it->first == name)
		{
			return it->second;
		}
		it++;
	}

	return -1; 
}
