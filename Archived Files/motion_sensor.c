//------------------------------------------------------------------------------------------------------------
//
// ODROID-C GPIO(LED) / ADC Test Application.
//
// Defined port number is wiringPi port number.
//
// Compile : gcc -o <create excute file name> <source file name> -lwiringPi -lwiringPiDev -lpthread
// Run : sudo ./<created excute file name>
//
//------------------------------------------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
 
#include <unistd.h>
#include <string.h>
#include <time.h>
 
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <wiringSerial.h>
#include <lcd.h>
 
//------------------------------------------------------------------------------------------------------------
//
// Global handle Define
//
//------------------------------------------------------------------------------------------------------------
 
#define DATA_UPDATE_PERIOD  1000 // 2sec
 
//------------------------------------------------------------------------------------------------------------
//
// ADC:
//
//------------------------------------------------------------------------------------------------------------
#define PORT_D0   10   // Motion sensor D0 - GPIOX.BIT1 - pin 24
 
 
//------------------------------------------------------------------------------------------------------------
//
// Read bit from the sensor
//
//------------------------------------------------------------------------------------------------------------
int read_sensor()
{
    int data_bit ; 

       if (digitalRead(PORT_D0) == LOW)
	   data_bit = 0 ;
       else data_bit = 1 ; 

    return data_bit ; 
}

//------------------------------------------------------------------------------------------------------------
//
// system init
//
//------------------------------------------------------------------------------------------------------------
int system_init(void)
{
    pinMode (PORT_D0, INPUT);
    return 0 ; 
 
 }

//------------------------------------------------------------------------------------------------------------
//
// Read the data from the sensor
//
//------------------------------------------------------------------------------------------------------------
void read_data(int *motion_data)
{
    int i ; 

    
    *motion_data = read_sensor() ; 
}

//------------------------------------------------------------------------------------------------------------
//
// Start Program
//
//------------------------------------------------------------------------------------------------------------
int main (int argc, char *argv[])
{ 

    int motion_data ; // 1 means correct checksum, 0 means wrong checksum
    int prev_status ; 

    printf("Staring the Motion sensor...\n");
    
    static int timer = 0 ;
    int i ; 
 
    ////////////////////////////////////////////////////////////////////////////////
    printf("Setting up Wiring Pi\n"); 
    wiringPiSetup ();
 
    if (system_init() < 0)
    {
        fprintf (stderr, "%s: System Init failed\n", __func__);     return -1;
    }
 
    ////////////////////////////////////////////////////////////////////////////////
    printf("Keep pinging the sensor every 2 sec\n");
    //printf("data read = %d", read_sensor(0)) ; 
    prev_status = 1 ; // no motion
    for(i=0;;)    {
        usleep(100000);  // sleep for 100 milli sec 
        if (millis () < timer)  continue ;
 
        //printf("Read the sensor data \n"); 
        read_data(&motion_data);     // Reads the D0 and A0 data of the sensor

	if (motion_data != prev_status)
	{
		if (!motion_data) printf("\n\n\nNo Motion detected\n") ;
		else printf("\n\n\nMotion detected !! \n") ; 
		prev_status = motion_data ; 
	}
        timer = millis () + DATA_UPDATE_PERIOD;
	i = i + 1 ; 
    }
 
    return 0 ;
}
 
//------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------
