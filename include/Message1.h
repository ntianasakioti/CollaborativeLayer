#ifndef MESSAGE1_H
#define MESSAGE1_H
#include "Message.h"


class Message1 : public Message
{
public:
    Message1(int a, std::string msg);
    ~Message1();
    void Serialize(int * dataAddress);
    void deSerialize(int * dataAddress);
    int getSize(); 



private:
    int id;
    std::string data; 
};

#endif; 