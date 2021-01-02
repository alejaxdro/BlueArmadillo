// Blue Armadillo Robot Control System using Beaglebone Black with Debian

using namespace std;
#include <iostream>
#include <fcntl.h>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <fstream>
#include <ctime>
#include <cmath>

#include "../include/log.h"
#include "../include/motorControl.h"
#include "../include/WheelsController.h"
#include "../include/IMUsensor.h"


int xy2deg(int x, int y);
int limit( int x, int min, int max );

int main (int argc, char* argv[])
{
	const string help = "--help";

	for(int i = 0; i < argc; ++i){
		if(help.compare(argv[i]) == 0){
			cout << "This program controls robot Blue Armadillo" << endl
				 << " use --test to use mock classes" << endl;
			return 0;
		}
	}

	ofstream myfile;
	myfile.open("armadillo.log");
	DEBUG_PRINT("Main: Log Created: armadillo.log\n");
	time_t start1, end1;

	char fd_mc[] = "/dev/ttyO4";
	// Init UART01 
	WheelsController motor( fd_mc );

	char fd_imu[] = "/dev/i2c-1";
	IMUsensor imuSensor( fd_imu );
	if(!imuSensor.connectedStatus){
		DEBUG_PRINT("Main: imuSensor Not Connected.\n");
	}

	bool search_bool = true;
	int angle = 0, lastAngle = 0;
	int motorSpeed = 0;
	double MAX_SPEED = 100.0;
	double MAX_ANGLE = 180.0;
	double MIN_SPEED = 0.0;

	DEBUG_PRINT("Main: Tracking 0 ...\n");
	time(&start1);
	while(search_bool){
		// TODO: use class call. SENSOR_BUF magn = getData();
		SENSOR_BUF magn = imuSensor.getDataMagn();
		angle = xy2deg(magn.data.x.val, magn.data.y.val);

		// Calculate motor speed
		motorSpeed = (double) angle * 270.0/MAX_ANGLE;
		motorSpeed = limit( motorSpeed, MIN_SPEED, MAX_SPEED );

		if(angle < 0){
			motor.motor1Control( motorSpeed, MIXEDLEFT );
		}else{
			motor.motor1Control( motorSpeed, MIXEDRIGHT );
		}
		
		if(angle > lastAngle || angle < lastAngle){
			DEBUG_PRINT("MotorSpeed: %d, Angle: %d\n", motorSpeed, angle);
			myfile << motorSpeed <<","<< angle << "\n";
			lastAngle = angle;
		}
		
		if(abs(angle) < 1){
			// Stop and exit
			motor.motor1Control( 0, MIXEDLEFT );
			//search_bool = false;
		}
	}
/*    for(int i = 0; i < 100; i++){
		if(i == 5){
			DEBUG_PRINT("Start Moving");
			motor.motor1Control( 100, MIXEDLEFT );
		}
		getData();
		magnData[i].data = magn.data;
		//DEBUG_PRINT("%d, %d, %d, %d \n", i,magnData[i].data.x.val,magnData[i].data.y.val, magnData[i].data.z.val);  
		myfile << i <<","<< xy2deg(magnData[i].data.x.val, magnData[i].data.y.val) << "\n";
   }
 */   
	time(&end1);
	DEBUG_PRINT("Time: Diff: %f\n", difftime( end1, start1 ));//CLOCKS_PER_SEC);
	// measured 57 seconds for 10000 reads of Magnetometer 
	// 	57/10000 = .0057 secs/sample ==> ~175 samples per second

	//motor.motor1Control( 100, MIXEDLEFT );
	//DEBUG_PRINT("Turn Left\n");
	//sleep(1);

	// Stop
	motor.motor1Control( 0, MIXEDFORWARD );

	DEBUG_PRINT("End of Program\n");
	cout << endl;
	myfile.close();
	return 0;
}


int xy2deg(int x, int y){
	// Convert x,y to Vector angle in radians and then convert
	int deg = ( atan2(y,x) * 180.0 ) / ( 3.14159 );
	return deg;
}


int limit( int x, int min, int max ){
	int tmp = abs(x);
	if( tmp > max ){
		return max;
	}else if( tmp < min ){
		return min;
	}else{
		return tmp;
	}
}
