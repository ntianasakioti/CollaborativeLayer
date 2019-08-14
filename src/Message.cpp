#include "Message.h"

std::string Message::getMessage()
{
    return "hi";
}

std::string Message::getSender()
{
    return "who";
}

void Message::CreateBuffer(int size)
{
    messageData = new int[size + headerSize];
}

int * Message::getBuffer()
{
    int * address = &(messageData[0+ headerSize]);
    return address; 
}