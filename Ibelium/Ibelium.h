/*  Ibelium 3G module library.  Allows for sending messages through text
messages, uploading log files to an ftp server, and receiving text messages.




*/
#ifndef Ibelium_h
#define Ibelium_h

#include "Arduino.h"

#define onModulePin 2
#define led 13

class Ibelium
{
public:
	Ibelium();
	int init();
	int sendSMS(char* message, char* response);
	int sendATCmd(char* cmd);
	//char* checkError(); Not implemented yet
private:
	int sendATQuery(char* cmd, char* response);
	void switchModule();

	int _error; //An error code
	int _watchdog; //A watchdog counter, for responses
};


/*
Error code mapping:
1 - Invalid or null response

2 - Response overflow

*/
#endif