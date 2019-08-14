#include "Message1.h"


Message1::Message1(int a, std::string msg)
{
    id = a; 
    data = msg;
    std::cout << " data " << data << std::endl;  
}

Message1::~Message1()
{

}

int Message1::getSize()
{
    return 1 + data.length(); 
}

void Message1::Serialize(int * dataAddress)
{
    *dataAddress = id; 
    std::cout << " address " << dataAddress << std::endl;
    std::cout << " value " << *dataAddress << std::endl; 
    dataAddress++;

    for(int i =0; i < data.length(); i++)
    {
        std:: cout << "integer of data " << int(data[i]) << std::endl; 
        *dataAddress = int(data[i]);
        dataAddress++;
        std::cout << " address " << dataAddress << std::endl;
    std::cout << " value " << *dataAddress << std::endl;
    }
}

void Message1::deSerialize(int * dataAddress)
{
    int k = *dataAddress;
    std::cout << " integer " << k << std::endl; 
    dataAddress++;
    char c ;
    for(int i = 0; i < getSize() -1; i++)
    {
        c = *dataAddress;
        dataAddress++;
        std::cout << "character " << c << std::endl; 
    }
}