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
 
#define DATA_UPDATE_PERIOD  2000 // 2sec
 
//------------------------------------------------------------------------------------------------------------
//
// ADC:
//
//------------------------------------------------------------------------------------------------------------
#define PORT_D0   27   // Rain sensor D0 - GPIOX.BIT1 - pin 24
#define PORT_A0   0    // Rain Sensor A0 - ADC.AIN0 - pin 40
 
 
//------------------------------------------------------------------------------------------------------------
//
// Read bit from the sensor
//
//------------------------------------------------------------------------------------------------------------
int read_sensor(int pin)
{
    int data_bit ; 

    if (!pin)
    {
       if (digitalRead(PORT_D0) == LOW)
	   data_bit = 0 ;
       else data_bit = 1 ; 
    }
    else 
       data_bit = analogRead(PORT_A0) ; 

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
void read_data(int *rain_status, int *rain_data)
{
    int i ; 

    
    *rain_status = read_sensor(0) ;    // 0 - digital
    usleep(100000);  // sleep for 100 milli sec 
    *rain_data = read_sensor(1) ; // 1 - analog  
}

//------------------------------------------------------------------------------------------------------------
//
// Start Program
//
//------------------------------------------------------------------------------------------------------------
int main (int argc, char *argv[])
{ 

    int rain_status ; 
    int rain_data ; // 1 means correct checksum, 0 means wrong checksum
    int prev_status ; 

    //printf("Staring the Rain sensor...\n");
    
    static int timer = 0 ;
    int i ; 
 
    ////////////////////////////////////////////////////////////////////////////////
    //printf("Setting up Wiring Pi\n"); 
    wiringPiSetup ();
 
    if (system_init() < 0)
    {
        fprintf (stderr, "%s: System Init failed\n", __func__);     return -1;
    }
 
    ////////////////////////////////////////////////////////////////////////////////
    //printf("Keep pinging the sensor every 2 sec\n");
    //printf("data read = %d", read_sensor(0)) ; 
    prev_status = 1 ; // no rain
    //for(i=0;;)    {
    //    usleep(100000);  // sleep for 100 milli sec 
    //    if (millis () < timer)  continue ;
 
        //printf("Read the sensor data \n"); 
        read_data(&rain_status, &rain_data);     // Reads the D0 and A0 data of the sensor

	//printf(" --- %d --- \n", rain_data) ; 	
    //if (i%30 == 0) printf("\n") ;
	//if (rain_status != prev_status)
	//{
		if (rain_status) printf("0") ;
		else printf("1") ; 
		prev_status = rain_status ; 
	//}
    //    timer = millis () + DATA_UPDATE_PERIOD;
	//i = i + 1 ; 
    //}
 
    return 0 ;
}
 
//------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------
