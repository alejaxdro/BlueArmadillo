/*get9axisData_v3r0.c 
  
This code has the basic i2c operating functions that opens the bus, reads, 
and writes from specified adresses on each device. 

	// accel - addr = 0x1d 0x6b gyro is the same 28-2d
	// 0x28-0x2d which are as follows:
	// 28 - XL	// 29 - XH
	// 2a - YL	// 2b - YH
	// 2c - ZL	// 2d - ZH
	
	// mag - addr = 0x1d
	// 0x05-0x0d which are as follows:
	//	05 - TempL	// 06 - TempH
	// 07 - Status_M
	// 08 - XL	// 09 - XH
	// 0a - YL	// 0b - YH
	// 0c - ZL	// 0d - ZH

*/

#include <stdlib.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h> // read/write/close
#include <fstream>

#include "../include/log.h"
//#include "../include/getData.h"
#include "../include/IMUsensor.h"

IMUsensor::IMUsensor( char* filename ){
      // Opens motor serial hardware interface i.e. UART01
   IMUsensor_fd = open(filename, O_RDWR|O_NOCTTY|O_NDELAY|O_NONBLOCK);
   if( IMUsensor_fd <= 0 ){
      DEBUG_PRINT("Serial Port not opened. fd=%d\n", IMUsensor_fd);
      this->connectedStatus = false;
   }
   this->connectedStatus = false;
   DEBUG_PRINT("IMUsensor::Serial Port Opened.\n");
   IMUsensor::init();
}

IMUsensor::~IMUsensor(){
   DEBUG_PRINT("Close Serial Port\n");
}

int IMUsensor::init( void ){
   int ret = 0;
   DEBUG_PRINT("IMUsensor::Init() Passed.\n");
   return ret;
}


SENSOR_BUF IMUsensor::getDataMagn(){
   // Local Declarations
   unsigned char addr, reg;
   unsigned char data[9];// Read 9 bytes of data
   		
   // Get Magnetometer XYZ Data from I2C port
   //DEBUG_PRINT("************** MAGNETOMETER DATA *************\n");
   addr = 0x1d;// accel_mag
   reg = 0x05; // Device register to access mag data
   read_sensor( data , addr, reg ); //send device address and register to start read from (data= 8 bytes read)	
   for ( int i = 0; i < 6; i++ ){
      // Copy xyz data from buffer to struct
      magn.byt[i] = data[i+3];
      //DEBUG_PRINT(":%X", magn.byt[i]);	
   }
   //DEBUG_PRINT(":\n");
   // convert from two's complement
   magn.data.x.val = ~magn.data.x.val + 1;
   magn.data.y.val = ~magn.data.y.val + 1;
   magn.data.z.val = ~magn.data.z.val + 1;
   return  magn;
// Display Data
      //DEBUG_PRINT(" X val = %d\n Y val = %d\n Z val = %d \n",magn.data.x.val,magn.data.y.val, magn.data.z.val);      
}


void IMUsensor::read_sensor( unsigned char data[], unsigned char addr, unsigned char reg){
	/* opens the i2c bus 1 */
	int file;
	char filename[40];
	char buf[256] = {0};
	
	sprintf(filename,"/dev/i2c-1");
	if ((file = open(filename,O_RDWR)) < 0) {
		DEBUG_PRINT("Failed to open the bus.");
		/* ERROR HANDLING; you can check errno to see what went wrong */
		exit(1);
	}
	if (ioctl(file,I2C_SLAVE,addr) < 0) {
		printf("Failed to acquire bus access and/or talk to slave.\n");
		/* ERROR HANDLING; you can check errno to see what went wrong */
		exit(1);
	}
   
	/*writes to i2c device*/
	for (int i = 0; i<9; i++){
		buf[0] = reg;
		reg++;
		if (write(file,buf,1) != 1) {
			/* ERROR HANDLING: i2c transaction failed */
			printf("Failed to write to the i2c bus. Errno = %d\n", errno);
			printf("\n\n");
      }
      if (read(file,buf,1) != 1) {
         /* ERROR HANDLING: i2c transaction failed */
         printf("Failed to read from the i2c bus. Errno = %d\n", errno);         
         printf("\n\n");
      } else {
         data[i]=buf[0];
         //DEBUG_PRINT("buf %d: %x\n", i, data[i]);
      }
   }
   close(file);
}

void IMUsensor::displayprompt(){
      printf("********************* Control Blue Armadillo Prototype *********************\n");
      printf("**                                                                        **\n");
      printf("**     Select one of the following:                                       **\n");
      printf("**             1. Type w and hit enter to add speed                       **\n");
      printf("**             2. Type s and hit enter to subtract speed                  **\n");
      printf("**             3. Type a and hit enter to add to turn left                **\n");
      printf("**             4. Type d and hit enter to add to turn right               **\n");
      printf("**                                                                        **\n");
      printf("**             5. Type r and hit enter to reset turn coefficient          **\n");
      printf("**             6. Type q and hit enter to stop motors                     **\n");
      printf("**                                                                        **\n");
      printf("**             7. Type z and hit enter to end program                     **\n");
      printf("**                                                                        **\n");
      printf("****************************************************************************\n");
      printf("-->");

}// end displayprompt()

