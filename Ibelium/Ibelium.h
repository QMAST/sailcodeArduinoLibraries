/*  Ibelium 3G module library.  Allows for sending messages through text
messages, uploading log files to an ftp server, and receiving text messages.


*/
#ifndef Ibelium_h
#define Ibelium_h

#include <Arduino.h>
#include <SD.h>

#define onModulePin 2
#define led 13

class Ibelium
{
public:
	int init();
	int sendSMS(char* message);

private:
	int sendATCmd(char* cmd);
	void switchModule();
};


#endif