#include "Arduino.h"
#include "Ibelium.h"
//Each function returns 1 if successful, 0 otherwise.

Ibelium::Ibelium() {
	//Empty Constructor
}

int Ibelium::init() {
	//Initializes and tests the module. 
	Serial.begin(115200);
	delay(2000);
	pinMode(led, OUTPUT);
	pinMode(onModulePin, OUTPUT);
	switchModule(); //Switches the module on
	return sendATCmd("AT");
}

int Ibelium::sendATCmd(char* cmd) {
	//Send an AT Command without returning the response
	char* resp;
	int s;
	s = sendATQuery(cmd, resp);
	free(resp);
	return s;
}

int Ibelium::sendATQuery(char* cmd, char* response) {
	//Send an AT command, and get the response from the board.

	free(response); //Avoid creating a memory leak.
	_error=0;
	_watchdog=0;

	int size=10;
	char* buff = (char*) calloc(size, sizeof(char)); //Allocate a 10 character buffer for the response
	int x=0;
	Serial.print(cmd);
	Serial.print((char)0xD);
	Serial.print((char)0xA);
	Serial.flush();
	delay(2000);
	//By now, the command should be sent completely.

	do {
		_watchdog=0;
		while(Serial.available()==0 && _watchdog<1000) _watchdog++;

		if(_watchdog>=1000) //No response received after a certain length of time
		{
			_error=2;
			break;
		}


		buff[x]=Serial.read(); //Read the next character
		x++;

		if(x>=size) { //Reallocate memory if message is getting longer.
			size *= 2;
			buff = (char*) realloc(buff, size);
		}

		if(size>256){ //Reponse too long
			_error = 1;
			break;
		}

	} while(!(buff[x-1]=='K' && buff[x-2]=='O'));//Keep Waiting for a response until the last two characters are 'OK'

	response = buff;

	if(_error!=0)
		return 1;
	else 
		return 0;	
}

int Ibelium::sendSMS(char* message, char* response) {
	
	
	return 1;
}


void Ibelium::switchModule() {
    digitalWrite(onModulePin,HIGH);
    delay(2000);
    digitalWrite(onModulePin,LOW);
}
