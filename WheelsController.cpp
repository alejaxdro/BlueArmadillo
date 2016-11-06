/**  Motor Control Library
** 
** Commands for communicating with RoboClaw r3 sold by Pololu.com
**
** Written by: Alejandro Lepervanche
** For Engineers, By Engineers
** 
** This software is to be used
*/
 
#include "WheelsController.h"

class WheelsController
{
	private:
      int motorController_fd; // file descriptor
		void write_cmd( unsigned char data[]);
		void motorMove( unsigned char speed, int mode );
		
	public:
		WheelsController( char* filename );
		~WheelsController();
      void motor1Control( unsigned char speed, int mode );
		
};

WheelsController::WheelsController( char* filename ){
   // Opens motor serial hardware interface i.e. UART01
   motorController_fd = open(filename, O_RDWR|O_NOCTTY|O_NDELAY|O_NONBLOCK);
   if( motorController_fd < 0 ){
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
	write(motorController_fd, data, sizeof(data));
}

void WheelsController::motorMove( unsigned char speed, int mode ){
	unsigned char packet[4] = {ADDRESS, mode, speed, CRC};
	write_cmd(packet);
}

void WheelsController::motor1Control( unsigned char speed, int mode ){
   // Make more advanced or we'll refactor this.
   motorMove( speed, mode );
}
