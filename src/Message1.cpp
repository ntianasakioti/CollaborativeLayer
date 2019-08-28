#include "Message1.h"


Message1::Message1()
{
    // All messages need to have the following two set" 
    SetMsgTypeString("Message1");
    SetMsgTypeInt(0);


    _data = " ";
    _randomNum = 0;
    _character = ' ';
    _secondNum = 0.0;
}

Message1::~Message1()
{

}

std::string Message1::getData()
{
    return _data;
}

void Message1::Initialize(std::string msg, int num1, char char1, double num2)
{
    std::cout << "Initialize" << std::endl;
    _data = msg;
    _randomNum = num1;
    _character = char1;
    _secondNum = num2; 
}


int Message1::GetSize()
{
    // add and return all sizes ( 1 for integers and characters sinze they will be represented by 
    // one integer)
    return _data.length() + 1 + 1 + (sizeof(_secondNum)/sizeof(int));
}

void Message1::Serialize(int * dataBuf)
{
    int index = Message::_headerSize;
	int *dataRef;

    std::cout << "HeaderSize " << Message::_headerSize << std::endl; 
    // convert string to 8 element integer array
    int elementsInIndex = ceil(_data.length()/double((sizeof(_data)/sizeof(int))));
    int intArray[elementsInIndex];
    std::string tempString;
    int myArray[sizeof(_data)/sizeof(int)];
	int stringIndex = 0; 
    for(int i = 0; i < sizeof(_data)/sizeof(int); i++)
    {
		std::cout << i << std::endl; 
       
		for(int j = 0; j < elementsInIndex; j++)
		{
			if (_data.length() < sizeof(_data)/sizeof(int))
       		{
				if(stringIndex > _data.length())
				{
					std::cout << "Ending eh " << std::endl; 
                    tempString = tempString + " ";
					continue; 
				}                                            
        	}

			if(stringIndex > _data.length())
				tempString = tempString + " ";

			intArray[j] = int(_data[stringIndex++]);
			std::cout << "int " << intArray[j] << std::endl;
			tempString = tempString + std::to_string(intArray[j]);
		}

		if( stringIndex > _data.length())
		{
			myArray[i] = 0;
			continue; 
		}

		std::cout << "temp string " << tempString << std::endl; 
        myArray[i] = stoi(tempString);
        tempString = "\0";
    }
    

    dataRef = myArray; 
	for (int i = 0; i < sizeof(_data)/sizeof(int); ++i){
        std::cout << "index " << index <<  std::endl; 
        dataBuf[index++] = dataRef[i];}
    dataRef = (int*) (&_randomNum);
    for(int i = 0; i < sizeof(_randomNum)/sizeof(int); i++){
        dataBuf[index++] = dataRef[i];}
    int temp = (int) _character;
    dataRef = (int*) (&temp);
    for(int i = 0; i < sizeof(temp)/sizeof(int); i++){
        dataBuf[index++] = dataRef[i];}
    dataRef = (int*) (&_secondNum);
    for(int i = 0; i < sizeof(_secondNum)/sizeof(int); i++){
        dataBuf[index++] = dataRef[i];}

    std::cout << "Serialize:  " <<  ": buffersize = " << GetSize() << std::endl << std::flush;
	for (int i = 0; i < GetSize(); i++) {
		std::cout << dataBuf[i] << " "; }
	std::cout << std::endl << std::flush;
}

void Message1::DeSerialize(int * dataBuf)
{
    std::cout << "Deserialize: " << ": buffersize = " << GetSize() << std::endl << std::flush;
	for (int i = 0; i < GetSize(); i++) {
		std::cout << dataBuf[i] << " "; }
	std::cout << std::endl << std::flush;

    int index = Message::_headerSize;
    std::cout << "HeaderSize " << Message::_headerSize << std::endl; 
    int * dataRef;

    // get string from size 8 int array
    std::string temp;
	std::string temp2;
	int tempInt;
	std::string myString; 
	char character;
	char charArray[3];
    int stringIndex = 0; 
	int j  = 0;
	for(int i = Message::_headerSize; i < Message::_headerSize + 8; i++)
	{
        std::cout << "i " << i << std::endl; 
		std::cout << "In for loop" << std::endl; 
		temp = std::to_string(dataBuf[i]);
        std::cout << "temp " << temp << std::endl; 
		int tempIntArray[temp.length()];
		int elementSize = temp.length();
		int tempIndex = 0;

		while( stringIndex < temp.length())
		{
			std::cout << "In while loop " << temp[stringIndex] << std::endl; 
			if(temp[stringIndex] == '1')
			{
                std::cout << "first if " << std::endl; 
				temp2 = temp.substr(stringIndex, 3);

				std::cout << "my integer " << temp2 << std::endl; 
				tempInt = std::stoi(temp2);
				character = char (tempInt);
				myString = myString + character; 
				stringIndex = stringIndex + 3; 
			}
			else if(temp[i] == '0')
			{
                std::cout << "found a  null" << std::endl; 
				break;
			}
			else
			{
                std::cout << "else " << std::endl; 
				temp2 = temp.substr(stringIndex, 2);
                std::cout << "after" << std::endl; 
				tempInt = std::stoi(temp2);
				character = char (tempInt);
				myString = myString + character;
				stringIndex = stringIndex + 2; 
			}
		}

		stringIndex = 0; 
	}
	_data = myString; 
	std::cout << "MY STRING " << _data << std::endl; 

    // Continuing deserialization
     dataRef = (int*) (&_randomNum);
    for(int i = 0; i < sizeof(_randomNum)/sizeof(int); i++){
        dataRef[i] = dataBuf[index++];}
    int tempNum = (int) _character;
    dataRef = (int*) (&tempNum);
    for(int i = 0; i < sizeof(temp)/sizeof(int); i++){
        dataRef[i] = dataBuf[index++];}
    dataRef = (int*) (&_secondNum);
    for(int i = 0; i < sizeof(_secondNum)/sizeof(int); i++){
        dataRef[i] = dataBuf[index++];}
}