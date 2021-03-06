
#define NELEMS(x)  (sizeof(x) / sizeof(x[0]))  // length of array
#define ADDRESS 128
#define	MASK 0X7F
#define CRC 0

// RoboClaw Specific Commands
#define	M1FORWARD 0
#define	M1BACKWARD 1
#define	SETMINMB 2
#define	SETMAXMB 3
#define	M2FORWARD 4
#define	M2BACKWARD 5
#define	M17BIT 6
#define	M27BIT 7
#define	MIXEDFORWARD 8
#define	MIXEDBACKWARD 9
#define	MIXEDRIGHT 10
#define	MIXEDLEFT 11
#define	MIXEDFB 12
#define	MIXEDLR 13
#define	GETM1ENC 16
#define	GETM2ENC 17
#define	GETM1SPEED 18
#define	GETM2SPEED 19
#define	RESETENC 20
#define	GETVERSION 21
#define	GETMBATT 24
#define	GETLBATT 25
#define	SETMINLB 26
#define	SETMAXLB 27
#define	SETM1PID 28
#define	SETM2PID 29
#define	GETM1ISPEED 30
#define	GETM2ISPEED 31
#define	M1DUTY 32
#define	M2DUTY 33
#define	MIXEDDUTY 34
#define	M1SPEED 35
#define	M2SPEED 36
#define	MIXEDSPEED 37
#define	M1SPEEDACCEL 38
#define	M2SPEEDACCEL 39
#define	MIXEDSPEEDACCEL 40
#define	M1SPEEDDIST 41
#define	M2SPEEDDIST 42
#define	MIXEDSPEEDDIST 43
#define	M1SPEEDACCELDIST 44
#define	M2SPEEDACCELDIST 45
#define	MIXEDSPEEDACCELDIST 46
#define	GETBUFFERS 47
#define	GETCURRENTS 49
#define	MIXEDSPEED2ACCEL 50
#define	MIXEDSPEED2ACCELDIST 51
#define	M1DUTYACCEL 52
#define	M2DUTYACCEL 53
#define	MIXEDDUTYACCEL 54
#define	GETERROR 90
#define	WRITENVM 94

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
