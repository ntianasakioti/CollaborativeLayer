#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>
#include <vector>
#include <string>
#include <iostream>
#include <map>



class Message
{
public: 
	virtual void Serialize(int * dataAddress) = 0; 
	virtual void deSerialize(int * dataAddress) = 0; 
	virtual int getSize() = 0; 
	int * getBuffer();
	void CreateBuffer(int size); 
	std::string getMessage();
	std::string getSender();

protected:

private:
	int * messageData;
	std::string sender;
	int headerSize = 10;
	static std::map<int,int> id; 
};
#endif