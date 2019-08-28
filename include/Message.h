#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>
#include <vector>
#include <string>
#include <iostream>
#include <tuple>
#include <sstream>
#include <cstdio>
#include <stdio.h>
#include <math.h>
#include <cstring>

//enum messageType {0, 1, 2};
class Message
{
public: 
	virtual void Serialize(int * dataBuf) = 0; 
	virtual void DeSerialize(int * dataBuf) = 0; 
	virtual int GetSize() = 0; 
	int * GetBuffer();
	void CreateBuffer(int size, int ASid); 
	std::string GetMessage();
	std::string GetSender();
	void SetId(int id);
	int GetTypeInt();
	void SetMsgTypeString(std::string msgTypeString);
	void SetMsgTypeInt(int msgTypeInt);
	void SetBufHeader(int * buf);
	void SetHeaderAttr(char commType, int msgTypeInt, int msgDataSize,std::tuple<int, int> sourceId, std::tuple<int,int> destId);
	int GetHeaderSize();

   std::string data;

	static int _headerSize;																	// header size

protected:

	static int _id; 																		// message id for this rover
 

private:																				// buffer containing message data
	std::tuple<int,int> _sourceId;															// source ID : < AS id, module id>	
	std::tuple<int,int> _destId;  															// destination ID: <AS id, module id>
	char _commType; 																		// communication type (B for Bluetooth, R for Ros)	
	int _msgDataSize; 																	// message size  -> this would make the header size variable as the message size will be variable
	std::string _msgTypeString;																// will be a string of a class name so that we know the correct deserialize method to call
	int _msgTypeInt; 
};

#endif