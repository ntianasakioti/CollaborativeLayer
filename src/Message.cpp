#include "Message.h"

int Message::_id = 0;
int Message::_headerSize = 8; 

std::string Message::GetMessage()
{
    return "hi";
}

std::string Message::GetSender()
{
    return "who";
}

void Message::SetId(int id)
{
    _id = id; 
}

int Message::GetTypeInt()
{
    return _msgTypeInt;
}
void Message::SetMsgTypeString(std::string msgTypeString)
{
    _msgTypeString = msgTypeString;
}

void Message::SetMsgTypeInt(int msgTypeInt)
{
    _msgTypeInt = msgTypeInt; 
}

void Message::CreateBuffer(int size, int ASid)
{
    if(std::get<0>(_sourceId) == ASid)
    {
        _id++;//
        _msgDataSize = size; 
    }

   // _buf = new int[size + Message::_headerSize];
    std::cout << "End of create buffer" << std::endl;
}

int * Message::GetBuffer()
{
    int * address = new int[5];
   // int * address = &(_buf[0+ Message::_headerSize]);
    return address; 
}

void Message::SetBufHeader(int * buf)
{

   buf[0] = _id;   
   buf[1] = _commType;
   buf[2] = _msgTypeInt;  
   buf[3] = _msgDataSize;                                  
   buf[4] = std::get<0>(_sourceId);
   buf[5] = std::get<1>(_sourceId);
   buf[6] = std::get<0>(_destId);
   buf[7] = std::get<1>(_destId);
}

void Message::SetHeaderAttr(char commType, int msgTypeInt, int msgDataSize, std::tuple<int, int> sourceId, std::tuple<int,int> destId)
{
    _commType = commType;
    _msgTypeInt = msgTypeInt;
    _msgDataSize = msgDataSize;
    _sourceId = sourceId;
    _destId = destId; 
}

int Message::GetHeaderSize()
{
    return Message::_headerSize;
}
