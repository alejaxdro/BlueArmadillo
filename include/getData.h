#include <stdlib.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>

#define DEBUG 1

#if defined(DEBUG) && DEBUG > 0
 #define DEBUG_PRINT(fmt, args...) fprintf(stderr, fmt, ##args)
 //fprintf(stderr, "DEBUG: %s:%d:%s(): " fmt, \
    __FILE__, __LINE__, __func__, ##args)
#else
 #define DEBUG_PRINT(fmt, args...) // Don't do anything in release builds
#endif

// Global Declarations
typedef union{
      short val;
      unsigned char byte[2];
   } SH_CH2;
typedef struct{
      SH_CH2 x;
      SH_CH2 y;
      SH_CH2 z;
   } SENSOR_XYZ; 
typedef union{
      SENSOR_XYZ data;
      unsigned char byt[6];
   } SENSOR_BUF;

// Global Variables
SENSOR_BUF accel;
SENSOR_BUF magn;
SENSOR_BUF gyro;

// Declare User Functions
extern void init9axis( void );
void read_sensor( unsigned char data[], unsigned char addr, unsigned char reg);
extern void getData( void );
void displayprompt( void );
