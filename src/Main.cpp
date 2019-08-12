#include "CommInt.h"
#include <boost/date_time.hpp>
#include "Comm.h"
#include <cstdio>
#include <chrono>
#include <ctime>

int main()
{  
	CommInt * commint = new CommInt();


	// Getting time that broadcast message will be sent
	boost::posix_time::ptime timeLocal = boost::posix_time::second_clock::local_time();
//	std::string time_string;
	//strftime(time_string, 50, "Time %T", timeLocal.time_of_day());
	std::cout << "Time " << timeLocal.time_of_day() << std::endl; 
	std::string msg = "Broadcast from Leathrum at " + to_simple_string(timeLocal.time_of_day()); 

	// Sending Broadcast message
	std::cout << "Before send bd " << std::endl << std::flush; 
	commint->SendMessage(msg, "All");

	std::cout << "After Send Broadcast call " << std::endl << std::flush; 

	int counter = 0; 
	// Send 5 Point-to-Point Messages 
	while(counter < 5)	
	{
		timeLocal = boost::posix_time::second_clock::local_time();
		msg = "Point to Point from Leathrum at " + to_simple_string(timeLocal.time_of_day());

		commint->SendMessage(msg, rand() < RAND_MAX /2 ? "Ntiana" : "OldLeathrum");
		sleep(2);
	}

	return 0;
}