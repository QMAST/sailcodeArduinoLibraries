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
	pinMode(LED, OUTPUT);
	pinMode(ON_MODULE_PIN, OUTPUT);
	switchModule(); //Switches the module on

	//Send SMS mode to Text
	return sendATCmd("AT+CMGF=1");
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
			Serial.println("Watchdog timer gone");
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
			//Serial.println(size);
			break;
		}

	} while(x<2 || !(buff[x-1]=='K' && buff[x-2]=='O')  );//Keep Waiting for a response until the last two characters are 'OK'

	buff[x]=0x0;
	response = buff;

	if(_error==0)
		return x;
	else 
		return 0;	
}

int Ibelium::sendSMS(char* number, char* message, char* response) {
	//Sends an AT Command to send an SMS message
	//AT+CMGS="number"<CR> message <ESC>
	 //Initial attempt, ugly as fuck
/*	free(response); //Avoid creating a memory leak.
	_error=0;
	_watchdog=0;

	int size=10;
	char* buff = (char*) calloc(size, sizeof(char)); //Allocate a 10 character buffer for the response
	int x=0;
	Serial.print("AT+CMGS=\"");
	Serial.print(number);
	Serial.print("\"");
	Serial.print((char)0xD);
	Serial.print(message);
	Serial.print((char)0x1B);
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
			Serial.println("Watchdog timer gone");
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
			Serial.println(size);
			break;
		}

	} while(x<2 || !(buff[x-1]=='K' && buff[x-2]=='O')  );//Keep Waiting for a response until the last two characters are 'OK'

	buff[x]=0x0;
	response = buff;

	if(_error==0)
		return x;
	else 
		return 0;

		*/

	//Cleaner attempt
	char* cmd = appendStrings("AT+CMGS=\"", number);
	cmd = appendStrings(cmd, "\"\r");
	cmd = appendStrings(cmd, message);
	cmd = appendStrings(cmd, "\x1b");

	return sendATQuery(cmd, response);
}

int Ibelium::readSMS(char* ) {
	//Reads the most recent SMS and 
	//char*


	return 0; 
}

void Ibelium::switchModule() {
    digitalWrite(ON_MODULE_PIN,HIGH);
    delay(2000);
    digitalWrite(ON_MODULE_PIN,LOW);
}

char* appendStrings(char* a, char* b) {
	int lenA, lenB;
	char* newString;
	lenA=0;
	lenB=0;
	//Find the length of the two strings;
	while(a[lenA]!='\0') lenA++;
	while(b[lenB]!='\0') lenB++;

	newString = (char*) malloc(sizeof(char)*(lenA+lenB+1));

	for(int i=0; i<lenA; i++) {
		newString[i] = a[i];
	}
	for(int i=0; i<lenB; i++) {
		newString[lenA+i] = b[i];
	}
	newString[lenA+lenB]='\0';
	free(a);
	free(b);

	return newString;
}
