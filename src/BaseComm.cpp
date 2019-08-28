#include "BaseComm.h"


Message * BaseComm::getMsgFromId(int id)
{
	Message1 * msg1; 
	Message2 * msg2;
	switch(id)
	{
		case 0:
			msg1 = new Message1();
			return msg1;
			break;
		case 1:
			msg2 = new Message2(); 
			return msg2;
			break;
	}
}



std::vector<std::vector<Message*>> BaseComm::messageBacklog; 

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
	MutexLock();
	if(messageBacklog[moduleId].size() > 0)
		return true;
	else
		return false;
	MutexUnlock();  
}

Message * BaseComm::GetMessage(int moduleId)
{
	MutexLock();
	Message * newMsg = getMsgFromId(messageBacklog[moduleId].at(0)->GetTypeInt());


	newMsg = (Message *) malloc(sizeof(messageBacklog[moduleId].at(0)));
	std::memcpy(newMsg, messageBacklog[0].at(0), sizeof(messageBacklog[moduleId].at(0)));
	free(messageBacklog[moduleId].at(0));
	messageBacklog[moduleId].erase(messageBacklog[moduleId].begin());
	MutexUnlock();

	return newMsg;
}

void BaseComm::UpdateMessageLog(Message * msg, int moduleId)
{
	std::cout << "Pushing back another message" << std::endl; 
	
	messageBacklog[moduleId].push_back(msg);
	//std::cout << messageBacklog[moduleId].at(0)->data << std::endl;
}

void BaseComm::UpdateMsgLogNum()
{
	
	// Create and add anothe vector to MessageBacklog
	std::vector<Message *> anotherMsgLog; 
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

int BaseComm::GetMessageLogSize(int moduleId)
{
	return messageBacklog[moduleId].size(); 
}

int BaseComm::GetId(std::string name)
{
	//std::cout << "Name " << name << std::endl; 

	std::map<std::string,int>::iterator it = nameIDs.begin();

	for(int i = 0 ; i < nameIDs.size(); i++)
	{
		//std::cout << it->first << std::endl; 
		if(it->first == name)
		{
			return it->second;
		}
		it++;
	}

	return -1; 
}
