#include "BlueComm.h"

#include <boost/date_time.hpp>
BlueComm::BlueComm()
{
	std::cout << "Object created" << std::endl << std::flush; 
	InitComm(); 
}

BlueComm::~BlueComm()
{
}

void BlueComm::Setup()
{
	std::ifstream inf("config/bdAddresses.txt"); 

	// if can't open file
	if(!inf.is_open())
	{
		std::cerr << "Uh oh, file could not be opened for reading! " << std::endl;
		exit(1);
	}

	std::cout << "Opened bdAddresses correctly" << std::endl;

	int id;
	std::string address;
	
	while(!inf.eof())
	{
		inf >> id;
		inf >> address; 
		BdAddresses.insert(std::make_pair(id,address));
	}
	
}

void BlueComm::InitComm()
{
	// Set and Create separate thread
	Setup(); 

	std::cout<< "Creating listening thread " << std::endl << std::flush; 
	
	std::thread ltThread(&BlueComm::ListeningThread, this);

	ltThread.detach();
	
	std::cout << "Continuing " << std::endl << std::flush; 
}

void BlueComm::ListeningThread()
{

    bool terminate = false; 
    bool test = true; 
   // while(test == true)
    //{
	//std::cout<< "Launched my separate thread " << std::endl; 

	// Set up Bluetooth Socket and address parameters
	// to listen for a message 
	struct sockaddr_rc loc_addr = {0}, rem_addr = {0};
	char buf[1024] = {0};
	int t, client, bytes_read; 
	socklen_t opt = sizeof(rem_addr);

	// allocate a socket
    t = socket(AF_BLUETOOTH,SOCK_STREAM,BTPROTO_RFCOMM);

	// bind socket to port 1 of the first available //
	// local bluetooth adapter 
	bdaddr_t temp = {};
	loc_addr.rc_family = AF_BLUETOOTH;
	loc_addr.rc_bdaddr = temp; 
	loc_addr.rc_channel = (uint8_t) 1; 
	bind(t, (struct sockaddr *)&loc_addr, sizeof(loc_addr));

	// put socket to listen mode 
	listen(t,20);

	// Just for testing to keep track of the loop
	int counter = 0; 

	while (terminate == false)
	{
	    	//std::cout << "I AM IN THE WHILE LOOP " << std::endl; 
	    	//std::cout << "Counter " << counter << std::endl << std::flush; 

		    // accept one connection 
		    client = accept(t, (struct sockaddr *)&rem_addr, &opt);

		    //std::cout << "After I accepted connection " << std::endl; 
		    ba2str(&rem_addr.rc_bdaddr, buf );
		    fprintf(stderr,"accepted connection from %s\n", buf);
		    memset(buf, 0, sizeof(buf));

		    // read message
		    bytes_read = read(client, buf, sizeof(buf));
		    if(bytes_read > 0 )
		    {
		    	printf("received[%s]\n", buf);
		    	std::string s(buf);
		    	MutexLock(); 
		    	UpdateMessageLog(s);
		    	MutexUnlock(); 
		  //  	terminate = true; 
		    }
		counter++; 
	}

        terminate = false;   
		//shutdown(t, SHUT_RD);
        close(t);
   // }

	//// don't think I need the outer loop. As long as with this code it can accept enough connections 
	// to be determined upon testing to receive 6 messages. 
}

int BlueComm::SendPtoP(std::string message, std::string dest)
{

	//std::cout << "In bluecomm's sent p to p" << std::endl << std::flush; 
	// Find destination address //
	
	int id = GetId(dest);
	//std::cout << "Id i will send to " << id << std::endl << std::flush; 
	std::map<int, std::string>::iterator it = BdAddresses.begin();
	while(it->first != id)
		it++;

	//std::cout << "bluetooth address " << it->second << std::endl << std::flush;
	char destination[18];
	strcpy(destination,(it->second).c_str());

	std::cout << "destination " << destination << std::endl << std::flush;
	
	int s, status; 
	struct sockaddr_rc addr = {0};

	s = socket(AF_BLUETOOTH,SOCK_STREAM,BTPROTO_RFCOMM);

	addr.rc_family = AF_BLUETOOTH;
	addr.rc_channel = (uint8_t) 1; 
	str2ba(destination, &addr.rc_bdaddr);

	char char_array[message.length() + 1];
	strcpy(char_array, message.c_str()); 
	status = connect(s,(struct sockaddr*)&addr, sizeof(addr));

	if(status == 0)
	{
		write(s, char_array,message.length());
		//shutdown(s, SHUT_WR);
		close(s);
		std::cout << "Success in sending " << boost::posix_time::second_clock::local_time().time_of_day() << std::endl << std::flush;
		return 1; 
	}
	else if(status < 0 )
	{
		perror("uh oh");
		//shutdown(s, SHUT_WR);
		close(s);
		return 0; 
	}
	close(s);
	return 0;

}

int BlueComm::SendBd(std::string message)
{
	std::map<int, std::string>::iterator it = BdAddresses.begin();
	int returnV = 1; 

	for(int i = 0 ; i < BdAddresses.size(); i++)
	{
		std::cout << "Sendbd for loop Iteration " << i << std::endl << std::flush; 
		if(it->first != GetId(name))
		{
			std::cout << "Before Send to P to P " << std::endl << std::flush; 
			returnV = SendPtoP(message,it->second);
		} 
		std::cout << "After SendPtoPt" << std::endl << std::flush; 
	}
	return 0; 
}

