/**  Motor Control Library
** 
** Commands for communicating with RoboClaw r3 sold by Pololu.com
**
** Written by: Alejandro Lepervanche
** For Everyone, By Engineers
** 
** This software is to be used
*/
 
#include <fcntl.h>
#include <unistd.h>
#include <cstdlib>
#include <fstream> // for use of log.h?
#include "../include/log.h"
#include "../include/WheelsController.h"

WheelsController::WheelsController( char* filename ){
	// Opens motor serial hardware interface i.e. UART01
	motorController_fd = open(filename, O_RDWR|O_NOCTTY|O_NDELAY|O_NONBLOCK);
	if( motorController_fd <= 0 ){
		DEBUG_PRINT("Serial Port not opened. fd=%d\n", motorController_fd);
		exit(1);
	}
}

WheelsController::~WheelsController(){
	close( motorController_fd );
}

void WheelsController::write_cmd(unsigned char data[]){
	int n = NELEMS(data);
	unsigned char checksum = 0;
	int i;

	for(i = 0; i < n; i++){
		checksum += data[i];
	}
	data[n-1] = checksum & MASK;
	// Writes serial data of size data. Just in case it wasn't clear.
	int ret = write(motorController_fd, data, sizeof(data));
	if(ret <= 0){
		DEBUG_PRINT("WheelsController: WriteRetVal=%d",ret);
	}
}

void WheelsController::motorMove( unsigned char speed, int mode ){
	unsigned char packet[4] = {ADDRESS, mode, speed, CRC};
	write_cmd(packet);
}

void WheelsController::motor1Control( unsigned char speed, int mode ){
   // Make more advanced or we'll refactor this.
   motorMove( speed, mode );
}
