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

#include "motorControl.cpp"
#include "WheelsController.cpp"

#define DEBUG 0

#if defined(DEBUG) && DEBUG > 0
 #define DEBUG_PRINT(fmt, args...) fprintf(stderr, fmt, ##args)
 //fprintf(stderr, "DEBUG: %s:%d:%s(): " fmt, \
    __FILE__, __LINE__, __func__, ##args)
#else
 #define DEBUG_PRINT(fmt, args...) // Don't do anything in release builds
#endif

int main ()
{
   char fd[] = "/dev/ttyO4";
   // Init UART01
   WheelsController motor( fd );
   // Set mode - use default
   
   // Move motor
   motor.motor1Control( 40, M1FORWARD );
   DEBUG_PRINT()
   sleep(1);
   motor.motor1Control( 0, M1FORWARD );
   
   cout << endl;
   return 0;
}