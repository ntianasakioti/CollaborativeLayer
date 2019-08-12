#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>
#include <vector>
#include <map>



class Message
{
public:
	Message();
	~Message(); 
	virtual void Serialize() = 0; 
	virtual void deSerialize() = 0; 
	virtual void setSize() = 0; 
	std::string getMessage();
	std::string getSender();

protected:

private:
	int * message;
	std::string sender;
};
#endif