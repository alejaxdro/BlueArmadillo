using namespace std;
#include <iostream>
#include <fcntl.h>
#include "motorControl.cpp"

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
   int ser4 = open("/dev/ttyO4", O_RDWR|O_NOCTTY|O_NDELAY|O_NONBLOCK);
   
   cout << "Hello, the file descriptor is " << ser4 << endl;
   
   close( ser4 );
   return 0;
}