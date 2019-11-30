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
#define PORT_A0   0   // Soil Moisture Sensor A0 - ADC.AIN0 - pin 40
 
 
//------------------------------------------------------------------------------------------------------------
//
// Read bit from the sensor
//
//------------------------------------------------------------------------------------------------------------
int read_sensor()
{
    int data_bit ; 

       data_bit = analogRead(PORT_A0) ; 

    return data_bit ; 
}


//------------------------------------------------------------------------------------------------------------
//
// Read the data from the sensor
//
//------------------------------------------------------------------------------------------------------------
void read_data(int *rain_data)
{
    int i ; 

    
    *rain_data = read_sensor() ; 
}

//------------------------------------------------------------------------------------------------------------
//
// Start Program
//
//------------------------------------------------------------------------------------------------------------
int main (int argc, char *argv[])
{ 

    int moisture_level ; // 1 means correct checksum, 0 means wrong checksum
    int prev_data ; 

    //printf("Staring the Moisture sensor...\n");
    
    static int timer = 0 ;
    int i ; 
 
    ////////////////////////////////////////////////////////////////////////////////
    //printf("Setting up Wiring Pi\n"); 
    wiringPiSetup ();
 
    //if (system_init() < 0)
    //{
    //    fprintf (stderr, "%s: System Init failed\n", __func__);     return -1;
    //}
 
    ////////////////////////////////////////////////////////////////////////////////
    //printf("Keep pinging the sensor every 2 sec\n");
    //printf("data read = %d", read_sensor(0)) ; 
    prev_data = 0 ; 
    //for(i=0;;)    {
    //    usleep(100000);  // sleep for 100 milli sec 
    //    if (millis () < timer)  continue ;
 
        //printf("Read the sensor data \n"); 
        read_data(&moisture_level);     // Reads the D0 and A0 data of the sensor

	//if (moisture_level != prev_data)
	{
        //moisture_level=moisture_level/1022*100;
		printf("%d", moisture_level) ; 
		prev_data = moisture_level ; 
	}
    //    timer = millis () + DATA_UPDATE_PERIOD;
	//i = i + 1 ; 
    //}
 
    return 0 ;
}
 
//------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------
