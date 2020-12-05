// Blue Armadillo Robot Control System using Beaglebone Black with Debian

using namespace std;
#include <iostream>
#include <fcntl.h>
#include <cstdio>
//#include <cstdint>
//#include <cstdbool>
#include <cstdlib>
//#include <cfcntl>
//#include <ctermios>
#include <cstring>
#include <algorithm>
#include <fstream>
#include <ctime>
#include <cmath>

#include "motorControl.cpp"
#include "WheelsController.cpp"
#include "getData.cpp"

#define DEBUG 1

#if defined(DEBUG) && DEBUG > 0
 #define DEBUG_PRINT(fmt, args...) fprintf(stderr, fmt, ##args)
 //fprintf(stderr, "DEBUG: %s:%d:%s(): " fmt, \
    __FILE__, __LINE__, __func__, ##args)
#else
 #define DEBUG_PRINT(fmt, args...) // Don't do anything in release builds
#endif

void graph(int arr[], int size);
int xy2deg(int x, int y);

int main (int argc, char* argv[])
{
   std::cout << argv[0] << std::endl;
   DEBUG_PRINT("Start of Program\n");
   char fd[] = "/dev/ttyO4";
   // Init UART01 
   WheelsController motor( fd );
   // Set mode - use default
   
	
   ofstream myfile;
   myfile.open("data1.txt");
   time_t start1, end1;
	
	
   SENSOR_BUF magnData[1000];
   init9axis();
	
	
   DEBUG_PRINT("Get Data...\n");
   time(&start1);
   for(int i = 0; i < 100; i++){
		if(i == 5){
			DEBUG_PRINT("Start Moving");
			motor.motor1Control( 100, MIXEDLEFT );
		}
		getData();
		magnData[i].data = magn.data;
		//DEBUG_PRINT("%d, %d, %d, %d \n", i,magnData[i].data.x.val,magnData[i].data.y.val, magnData[i].data.z.val);  
		myfile << i <<","<< xy2deg(magnData[i].data.x.val, magnData[i].data.y.val) << "\n";
   }
   time(&end1);
   DEBUG_PRINT("Time: Diff: %d\n", difftime( end1, start1 ));//CLOCKS_PER_SEC);
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

void minMax(int arr[], int size){
	int min, max;
	// Calculate endpoints
	min = *std::min_element(arr, arr+size);
	max = *std::max_element(arr, arr+size);
	DEBUG_PRINT("Min: %d \nMax: %d\n", min, max);

}

int xy2deg(int x, int y){
	// Convert x,y to Vector in radians and then convert
	int deg = ( atan2(y,x) * 180.0 ) / ( 3.14159 );
	return deg;
}




















