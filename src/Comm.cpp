#include "Comm.h"
#include <fstream>

Comm* Comm::instance = NULL;

Comm::Comm()
{
	//terminate = false; 
}

Comm::~Comm()
{
	std::cout << "Terminating " << std::endl << std::flush; 
}

Comm * Comm::GetInstance()
{
	// Initialization on first use
	if( instance == NULL)
		instance = new Comm();
	return instance; 
}

void Comm::Init()
{
	std::ifstream inf("config/nameIDs.txt"); 

	// if can't open file
	if(!inf.is_open())
	{
		std::cerr << "Uh oh, file could not be opened for reading! " << std::endl;
		exit(1);
	}

	std::cout << "Opened nameIDs correctly" << std::endl;

	// read number of autonomous systems to create comm table 
	int numAS = 0;
	inf >> numAS; 

	// populate container that maps friendly names to ID used by the framework
	int id;
	std::string friendlyName; 
	while((inf>> id).good() && (inf>> friendlyName).good())
	{
		std::cout << "Am I stuck here " << std::endl;
		std::cout << "Excuse me " << std::endl; 
		//inf >> id; inf >> friendlyName;
		std::cout << id << " " << friendlyName << std::endl << std::flush;
		nameIdMap.insert(std::make_pair(friendlyName,id));
	}

	std::cout << "Read and made pairs for ID maps" << std::endl; 
	// create 2D Communications Table that will show the type of communication
	// needed for two AS systems to communicate.
	commTable = new char *[numAS];

	for(int i = 0; i < numAS; i++)
	{
		commTable[i] = new char [numAS];
	}

	inf.close();

	std::cout << "Created my commtable " << std::endl;

	// read comunication table file (commTable) to populate the commTable container

	std::ifstream inf2("config/commTable.txt");
	char temp;

	// if can't open file
	if(!inf2.is_open())
	{
		std::cerr << "Uh oh, file could not be opened for reading! " << std::endl;
		exit(1);
	}

	std::cout << "Am i advancing? " << std::endl; 
	// populate communication table 
	// maybe we should be grabbing just the row that has to do with this AS system 
	for(int i = 0; i < numAS; i++)
	{
		//std::cout << "Am I in the first loop " << std::endl;
		for(int j = 0; j < numAS; j++)
		{
			//std::cout << "Am I in the second loop" << std::endl; 
			inf2 >> temp; 
			std::cout << temp << std::endl;
			while(temp < 57)
			{
				inf2 >> temp; 
			}
			commTable[i][j] = temp; 
		}
		//std::cout << "Am I stuck" << std::endl; 
	}

	inf2.close(); 

	std::cout << "Populated commTable correctly " << std::endl; 

	std::map<std::string, int>::iterator it = nameIdMap.begin();
	while(it != nameIdMap.end())
	{
		if(it->first == systemName)
		{
			id = it->second;
			break; 
		}
		it++;
	}

	std::cout << "Found system name id: " << id << std::endl; 

	//bool Rflag = false;
	//bool Bflag = false;  


// Hard-coded testing code.

	AddMsgQueue(); 
	BaseCommPtrs.insert(std::make_pair('B', new BlueComm()));

///Code below will be used in actual implementation ///
/*	for(int i = 0; i < numAS; i++)
	{
		if(commTable[id][i] == 'R' && Rflag == false)
		{
			std::cout << "Creating RosComm" << std::endl; 
			BaseCommPtrs.insert(std::make_pair('R', new RosComm()));
		//	BaseCommPtrs.push_back(new RosComm());
			Rflag = true; 
		}
		else if(commTable[id][i] == 'B' && Bflag == false)
		{
			std::cout << "Creating BlueComm" << std::endl; 
			BaseCommPtrs.insert(std::make_pair('B', new BlueComm()));
			//BaseCommPtrs.push_back(new BlueComm());
			Bflag = true; 
		}
	}*/

	std::cout << "DONE INITIALIZING" << std::endl; 

/*
	std::cout << "CHECKING IF THINGS WERE DONE CORRECTLY" << std::endl; 
	std::cout << "Number of autonomous systems " << numAS << std::endl;
	std::cout<< "Checking NameIdMap" << std::endl;
	it = nameIdMap.begin();
	while(it != nameIdMap.end())
	{
		std::cout << it->first << " " << it->second << std::endl;
		it++;
	}

	std::cout << "Checking Communication Table " << std::endl; 
	for(int i = 0; i < numAS; i++)
	{
		//std::cout << "Am I in the first loop " << std::endl;
		for(int j = 0; j < numAS; j++)
		{
			std::cout << i << " " << j << " " << commTable[i][j] << std::endl;
		}

	}*/
}
int Comm::SendPtoP(std::string msg, std::string dest)
{	
	std::cout << "In send p to p " << std::endl << std::flush; 
	std::map<char, BaseComm *>::iterator it = BaseCommPtrs.begin();
	int sourceId = GetId(systemName);
	int destId = GetId(dest);

	for(int i = 0; i < BaseCommPtrs.size(); i++)
	{
		return (getPtr(commTable[sourceId][destId])->SendPtoP(msg,dest)); 
	}

	return -1; 
}

int Comm::SendBd(std::string msg)
{
	std::cout << "In send Bd " << std::endl; 
	bool success = true; 

	int id = getPtr('B')->GetId(systemName); 
	std::cout << "id " << id << std::endl; 
	std::map<std::string,int>::iterator it = nameIdMap.begin();

	for(int i = 0; i < nameIdMap.size(); i++)
	{
		if(i == id)
		{
			it++;
			continue;
		}		
		success = success == getPtr(commTable[id][i])->SendPtoP(msg, it->first);
		it++; 
	}
	return success; 
}

bool Comm::CheckForMessage()
{
	//if( messageBacklog.size() != 0)
	//	return true; 
	//else 
	std::map<char, BaseComm *>::iterator it = BaseCommPtrs.begin();
	return it->second->CheckForMessage(0); 
	
}

std::string Comm::GetMessage()
{
	return "blah";
}

void Comm::AddMsgQueue()
{
	std::map<char, BaseComm *>::iterator it = BaseCommPtrs.begin();
	it->second->UpdateMsgLogNum(); 

}

BaseComm * Comm::getPtr(char type)
{
	std::map<char, BaseComm *>::iterator it = BaseCommPtrs.begin();
	std::cout << "type " << type << std::endl; 
	std::cout << BaseCommPtrs.size() << std::endl;
	for(unsigned int i = 0; i < BaseCommPtrs.size(); i++)
	{	
		std::cout << it->first << std::endl; 
		if(it->first == type)
		{
			BaseComm * ptr = it->second;
			return ptr;
		}
		it++;
	}
	std::cout << "failure " << std::endl; 

	exit(EXIT_FAILURE);
	BaseComm * ptr = nullptr; 
	return ptr; 
}

int Comm::GetId(std::string name)
{
	std::map<std::string,int>::iterator it = nameIdMap.begin();

	for(int i = 0 ; i < nameIdMap.size(); i++)
	{
		if(it->first == name)
		{
			return it->second;
		}
	}

	return -1; 
}