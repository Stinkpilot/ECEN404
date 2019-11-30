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
 
#define DATA_UPDATE_PERIOD  4000 // 5sec
 
//------------------------------------------------------------------------------------------------------------
//
// ADC:
//
//------------------------------------------------------------------------------------------------------------
#define PORT_HUMIDITY_SENSOR   5   // Humidity sensor connected at 
 
 
//------------------------------------------------------------------------------------------------------------
//
// Set the data pin input or output
//
//------------------------------------------------------------------------------------------------------------
int config_inout(int inout)
{
    if (inout == 1)
        pinMode (PORT_HUMIDITY_SENSOR, INPUT); 
    else if (inout == 0)
        pinMode (PORT_HUMIDITY_SENSOR, OUTPUT); 

    return  0;
 }
 
//------------------------------------------------------------------------------------------------------------
//
// Read bit from the sensor
//
//------------------------------------------------------------------------------------------------------------
int read_sensor(int set_inout)
{
    int data_bit ; 
    
    if (set_inout)
        config_inout(1) ;   // 1 means input ie., reading
        
    if (digitalRead(PORT_HUMIDITY_SENSOR) == LOW)
	   data_bit = 0 ;
    else 
	   data_bit = 1 ;  

    return data_bit ; 
}
 
//------------------------------------------------------------------------------------------------------------
//
// Write bit from the sensor
//
//------------------------------------------------------------------------------------------------------------
int write_sensor(int set_inout, int data_bit)
{
    if (set_inout)
        config_inout(0) ;   // 0 means output ie., writing
        
    digitalWrite(PORT_HUMIDITY_SENSOR, data_bit) ; 

    return 0 ; 
}

//------------------------------------------------------------------------------------------------------------
//
// Hanshake protocol with the sensor
//
//------------------------------------------------------------------------------------------------------------
int request_data(void)
{
    int data_bit;
    static int request_timer ; 
    int time1, time2, time3 ; 
    
    ////////////////////////////////////////////////////////////////////////////////
    //// odroid initiates the handshake protocol with the humidity sensor

    // wait till the data bus is high
    data_bit = read_sensor(1) ; 
    while (data_bit ==0) 
    {
        usleep(1000) ;  // wait for 1milli sec before reading again
        data_bit = read_sensor(0) ;   
    }


    write_sensor(1, 1) ;  // write 1 just in case
	
    usleep(3000); 

    // pull the data bus down to start the handshake
    write_sensor(0, 0) ;  
    
    // wait for 1-10 msec and pull up the bus wire to comlete the 
    // reques to the sensor
    usleep(5000) ; 
    write_sensor(0, 1); 
    // wait for 20-40us
    usleep(30); 
 
    ////////////////////////////////////////////////////////////////////////////////
    //// read the handshake response from the sensor

    // wait for sensor to pull down the bus wire
    request_timer = 0 ; 
    data_bit = read_sensor(1) ; 
    while (data_bit == 1) 
    {
        usleep(10); 
        data_bit = read_sensor(0) ;   
        request_timer = request_timer + 1 ; 
	if (request_timer == 13) {
	  return 1;
	}	
    }

    //time1 = request_timer ; 
    
    // wait for the sensor to pull up the bus wire
    while (data_bit == 0) 
    {
        usleep(10); 
        data_bit = read_sensor(0) ;   
        request_timer = request_timer + 1 ; 
	if (request_timer == 13) {
	  return 1;
	}
    }


    //time2 = request_timer ; 

    //// wait for sensor to pull down the bus wire
    //while (data_bit == 1) 
    //{
    //    usleep(10); 
    //    data_bit = read_sensor(0) ;   
    //    request_timer = request_timer + 1 ; 
    //}

    //printf("Data transmission started, time took = %d, %d, %d\n", time1, time2, request_timer) ; 

    return 0 ; 

}
 

//------------------------------------------------------------------------------------------------------------
//
// Complete the request to the sensor
//
//------------------------------------------------------------------------------------------------------------
void complete_request()
{

	write_sensor(1,1) ; 
}
 

//------------------------------------------------------------------------------------------------------------
//
// Binary to Decimal
//
//------------------------------------------------------------------------------------------------------------
int bin_to_dec(int *bin_data, int no_bits)
{
	int ans = 0;
        int factor = 128; 	

	//printf("\nin converter\n"); 

	for (int i=0; i<no_bits;i++)
	{
	    if (bin_data[i]) 
	    {
		   ans = ans + factor ; 
	    }
	   //printf("%d \n", bin_data[i]); 
	   factor = factor/2 ;  
	}
	//printf("%d \n", ans);
	return ans ; 
}



//------------------------------------------------------------------------------------------------------------
//
// Hanshake protocol with the sensor
//
//------------------------------------------------------------------------------------------------------------
void read_data(double *temp, double *humid, int *valid_data, int *error)
{
    int i ; 
    int data_bit ; 
    int serial_data[2][40] ; 
    static int data_timer ; 
    int hex[5]; 
    
    //printf("beginnging\n");
    // Receive the 40 bit data
    data_bit = read_sensor(1) ; 
    // wait for sensor to pull down the bus wire 
    while (data_bit == 1) 
    {
        usleep(5); 
        data_bit = read_sensor(0) ;
    }
    for (i=0; i<40; i++)
    {
	data_timer = 0 ; 
        // wait for sensor to pull up the bus wire 
        while (data_bit == 0) 
        {
            //usleep(5); 
            data_bit = read_sensor(0) ;   
        }

        // wait for sensor to pull down the bus wire 
        while (data_bit == 1) 
        {
           // usleep(5); 
            data_bit = read_sensor(0) ;  
	    data_timer = data_timer + 1 ; 
	    if (data_timer > 1000) {
              *error = 1;
              break;
	    	
	    }
        }
		
	serial_data[0][i] = data_timer ; 
    }
    usleep(10) ; 
    complete_request();  // raises the data bit to '1' to finish the request
    //printf("end request\n");
    for (i=0; i<40; i++)
    {
	 //printf("data time %d = %d\n", i, serial_data[0][i]) ; 
	 if (serial_data[0][i] < 200) 
		 serial_data[1][i] = 0; // received '0' from sensor
	 else 
		 serial_data[1][i] = 1; // received '1' from sensor
    }

    //printf("Humidity data = ") ; 
    //for (i=0;i<16;i++)
    //{
    //   if (!(i%4))
    //   	  printf("_") ; 	       
    //    printf("%d", serial_data[1][i]) ;
    //}

    //printf("\nTemperature data = ") ; 
    //for (i=16;i<32;i++)
    //{
    //   if (!(i%4))
    //   	  printf("_") ; 	       
    //    printf("%d", serial_data[1][i]) ; 
    //}

    //printf("\nChecksum data = ") ; 
    //for (i=32;i<40;i++)
    //{
    //   if (!(i%4))
    //   	  printf("_") ; 	       
    //    printf("%d", serial_data[1][i]) ; 
    //}

    // printf("\nserial data = %x %x", &serial_data[1][0], &serial_data[1][8]); 

    hex[0] = bin_to_dec(&serial_data[1][0], 8) ; 
    hex[1] = bin_to_dec(&serial_data[1][8], 8) ; 
    hex[2] = bin_to_dec(&serial_data[1][16], 8) ; 
    hex[3] = bin_to_dec(&serial_data[1][24], 8) ; 
    hex[4] = bin_to_dec(&serial_data[1][32], 8) ; 

    //printf("\n data : %d %d %d %d %d\n", hex[0], hex[1], hex[2], hex[3], hex[4]) ;
    
    *temp = (hex[2] * 256) + hex[3] ; 
    *temp = *temp / 10 ; 

    *humid = (hex[0] * 256) + hex[1] ; 
    *humid = *humid / 10 ; 

    *valid_data = (hex[0] + hex[1] + hex[2] + hex[3]) % 256 ; 
    *valid_data = (*valid_data == hex[4]) ; 


}

//------------------------------------------------------------------------------------------------------------
//
// Start Program
//
//------------------------------------------------------------------------------------------------------------
int main (int argc, char *argv[])
{ 

    double temperature ; 
    double humidity ; 
    int valid_data ; // 1 means correct checksum, 0 means wrong checksum

	//printf("Staring the Humidity sensor...\n");
    static int timer = 0 ;
    int i ;
    int error = 0; 
 
    ////////////////////////////////////////////////////////////////////////////////
    //printf("Setting up Wiring Pi\n"); 
    wiringPiSetup ();
 
    //if (system_init() < 0)
    //{
    //    fprintf (stderr, "%s: System Init failed\n", __func__);     return -1;
    //}
 
    ////////////////////////////////////////////////////////////////////////////////
	//printf("Keep pinging the sensor every 4 sec\n");
	//printf("data read = %d", read_sensor(0)) ; 
    for(i=0;i<1;)    {
        usleep(10);  // sleep for 100 milli sec 
        //if (millis () < timer)  continue ;
 
 
        //printf("\n\nStarting the handshake\n"); 
	//printf("data read = %d", read_sensor(0)) ;        
        error = request_data();  // performs the initial handshake required to request data 
                         // from the sensor 
			 //
	  if (error == 1) {
	    printf("00.00|00.00");
	    return 0;
	  }

        read_data(&temperature, &humidity, &valid_data, &error);     // performs the serial read and outputs the temp, humid and 
                                                        // valid data 
      if (error == 1) {
	    printf("00.00|00.00");
	    return 0;
      }


        //printf("Read the data from the sensor\n"); 
	//if (valid_data) 
	//else 	
        	//printf("Checksum did not match!,  Temperature = %.2f C, Humidity = %.2f \%\n", temperature, humidity);
	  i = i+1; 
      timer = millis () + DATA_UPDATE_PERIOD;
    }
    printf("%.2f|%.2f", temperature, humidity);
    return 0 ;
}
 
//------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------
