#include <stdlib.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>

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
typedef union sensor_buf{
      SENSOR_XYZ data;
      unsigned char byt[6];
   } SENSOR_BUF;

// Declare User Functions
extern int init9axis( void );
void read_sensor( unsigned char data[], unsigned char addr, unsigned char reg);
extern SENSOR_BUF getData( void );
void displayprompt( void );
