/**  MiniIMU-9 v3 Gyro, Accelerometer, and Compass (L3GD20H and LSM303D Carrier)
** 
** https://www.pololu.com/product/2468
**
** Written by: Alejandro Lepervanche
** For Everyone, By Engineers
** 
** Starting with LSM303D 3D accelerometer and 3D magnetometer
** Both are compliant with 400kHz fast mode and normal mode i2c
*/

#include <stdlib.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>

//#include "i2c_imu.h"

#define accelMagn_ADDRESS 	0x1d // 0x1e when pin SA0 is driven low
#define gyro_ADDRESS 		0x6b // 0x6a when pin SA0 is driven low

imu::imu( char* filename ){
	// Open i2c file port
	imu_fd = open(filename, );
	if( imu_fd < 0){
		exit(1);
	}
}

imu::~imu(){
	close( imu_fd );
}

