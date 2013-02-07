#include <"Ibelium.h">
//Each function returns 1 if successful, 0 otherwise.


int Ibelium::sendATCmd(char* cmd) {
	char* buff;
	int size;
	Serial.print(cmd);
	Serial.print((char)0xD);
	Serial.print((char)0xA);
	Serial.flush();
	delay(2000);
	if(Serial.available()>0)
	{
		size = Serial.available();
		buff= (char*) malloc(sizeof(char) * Serial.available());
		Serial.readBytes(buff, size);
	}

}

int Ibelium::sendATQuery(char* cmd, char* response) {

}

int Ibelium::sendSMS(char* message, char* response) {

}

int init() {
	//Initializes and tests the module. 
	Serial.begin(115200);
	delay(2000);
	pinMode(led, OUTPUT);
	pinMode(onModulePin, OUTPUT);
	switchModule(); //Switches the module on

	return sendATCmd("AT");
}

void switchModule() {
    digitalWrite(onModulePin,HIGH);
    delay(2000);
    digitalWrite(onModulePin,LOW);
}