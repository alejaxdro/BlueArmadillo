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

class IMUsensor
{
   private:
      int IMUsensor_fd; // file descriptor
      SENSOR_BUF accel;
      SENSOR_BUF magn;
      SENSOR_BUF gyro;

   public:
      bool connectedStatus;
      IMUsensor( char* filename );
      ~IMUsensor();
      int init( void );
      void read_sensor( unsigned char data[], unsigned char addr, unsigned char reg);
      SENSOR_BUF getDataMagn( void );
      void displayprompt( void );      
};