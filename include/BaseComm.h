#ifndef BASECOMM_H
#define BASECOMM_H

#include <iostream>
#include <vector>
#include <mutex>
#include <fstream>
#include <map>
#include <unistd.h>

class BaseComm
{
public:
	//virtual ~BaseComm(){ }; 								/// saw on a forum that abstact classes should have a virtual destructor 
															/// so that derived classes can free up resources
	void Init();
	virtual void Setup() = 0;  
	virtual int SendPtoP(std::string message, std::string dest) = 0;
	virtual int SendBd(std::string message) = 0;
	bool CheckForMessage(int moduleId);
	std::string GetMessage(int moduleId);
	void UpdateMessageLog(std::string s); 
	void AddMessageQueue();
	void UpdateMsgLogNum();
	void MutexLock();
	void MutexUnlock(); 
	
	int GetMessageLogSize();
	int GetId(std::string name); 

private:
	static std::vector<std::vector<std::string>> messageBacklog;
	std::mutex messageMutex; 
};

#endif