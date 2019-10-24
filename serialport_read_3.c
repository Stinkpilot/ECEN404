/*====================================================================================================*/
/* Sellecting the Serial port Number on Linux                                                         */
/* ---------------------------------------------------------------------------------------------------*/ 
/* /dev/ttyUSBx - when using USB to Serial Converter, where x can be 0,1,2...etc                      */
/* /dev/ttySx   - for PC hardware based Serial ports, where x can be 0,1,2...etc                      */
/*====================================================================================================*/

/*-------------------------------------------------------------*/
/* termios structure -  /usr/include/asm-generic/termbits.h    */ 
/* use "man termios" to get more info about  termios structure */
/*-------------------------------------------------------------*/

#include <stdio.h>
#include <fcntl.h>   /* File Control Definitions           	*/
#include <termios.h> /* POSIX Terminal Control Definitions 	*/
#include <unistd.h>  /* UNIX Standard Definitions 	   		*/ 
#include <errno.h>   /* ERROR Number Definitions           	*/
	
void main(void) {

  int fd;				/*File Descriptor*/

  /*------------------------------- Opening the Serial Port -------------------------------*/
  /* Change /dev/ttyUSB0 to the one corresponding to your system */

  /* ttyUSB0 is the FT232 based USB2SERIAL Converter   */
  /* O_RDWR   - Read/Write access to serial port       */
  /* O_NOCTTY - No terminal will control the process   */
  /* Open in blocking mode,read will wait              */
  fd = open("/dev/ttyUSB0", O_RDWR | O_NOCTTY);
                                                          
  /* Error Checking */							
  if (fd == -1) {
    printf("\n  Error! in Opening ttyUSB0  ");
  }
    
  /*---------- Setting the Attributes of the serial port using termios structure --------- 	*/
      
  struct termios SerialPortSettings;		/* Create the structure */

  tcgetattr(fd, &SerialPortSettings);		/* Get the current attributes of the Serial port */

  /* Setting the Baud rate */
  cfsetispeed(&SerialPortSettings,B4800); /* Set Read  Speed as 4800 */
  cfsetospeed(&SerialPortSettings,B4800); /* Set Write Speed as 4800 */

  /* 8N1 Mode */
  SerialPortSettings.c_cflag &= ~PARENB;   /* Disables the Parity Enable bit(PARENB), So No Parity  */
  SerialPortSettings.c_cflag &= ~CSTOPB;   /* CSTOPB = 2 Stop bits,here it is cleared so 1 Stop bit */
  SerialPortSettings.c_cflag &= ~CSIZE;	 /* Clears the mask for setting the data size             */
  SerialPortSettings.c_cflag |=  CS8;      /* Set the data bits = 8                                 */

  SerialPortSettings.c_cflag &= ~CRTSCTS;       /* No Hardware flow Control                         */
  SerialPortSettings.c_cflag |= CREAD | CLOCAL; /* Enable receiver,Ignore Modem Control lines       */ 


  SerialPortSettings.c_iflag &= ~(IXON | IXOFF | IXANY);          /* Disable XON/XOFF flow control both i/p and o/p */
  SerialPortSettings.c_iflag &= ~(ICANON | ECHO | ECHOE | ISIG);  /* Non Cannonical mode                            */

  SerialPortSettings.c_oflag &= ~OPOST;/*No Output Processing*/

  /* Setting Time outs */
  SerialPortSettings.c_cc[VMIN] = 232; /* Read at least 10 characters */
  SerialPortSettings.c_cc[VTIME] = 0; /* Wait indefinetly   */


  if((tcsetattr(fd,TCSANOW,&SerialPortSettings)) != 0) {/* Set the attributes to the termios structure*/
    printf("\n  ERROR ! in Setting attributes");
  }			
  /*------------------------------- Read data from serial port -----------------------------*/

  tcflush(fd, TCIFLUSH);   /* Discards old data in the rx buffer            */

  char read_buffer[128];   /* Buffer to store the data received              */
  int  bytes_read = 0;    /* Number of bytes read by the read() system call */

  int exit = 0;  
  //printf("\n");
  while (exit == 0) {
    bytes_read = read(fd,&read_buffer,128);  // Read the data
    if ((read_buffer[3] == 'G') && (read_buffer[4] == 'G') && (read_buffer[5] == 'A')) {
      for (size_t i = 0; i < bytes_read; i++) {
        //printf("%c", read_buffer[i]);
      }
      break; 
    } 
  }

  //printf("\n\n\n");

  char dummy_buffer[22] = {'3', '0', '3', '7', '.', '5', '8', '4', '1', 'N', '|', '0', '9', '6', '2', '0', '.', '5', '4', '8', '5', 'W'};
  char my_buffer[22];
  int comma_count = 0;


  if (read_buffer[19] == ',') {
    for (size_t i = 0; i < 22; i++) {
      my_buffer[i] = dummy_buffer[i];
    }
  } else {
    size_t j = 0;
    for (size_t i = 0; i < bytes_read; i++) { //bytes_read
      if (read_buffer[i] == ',') {
        comma_count += 1;
      } else if ((comma_count >= 2) && (comma_count < 7)) {
        if (j==10) {
          my_buffer[j] = '|';
          j += 1;
          i -= 1;
        } else {
          my_buffer[j] = read_buffer[i];
          j += 1;
        }
      } else {
        /*do nothing */
      }
    }
  }

  char output_buffer[11] = {my_buffer[0], my_buffer[1], my_buffer[2], my_buffer[3], my_buffer[9], my_buffer[10], my_buffer[12], my_buffer[13], my_buffer[14], my_buffer[15], my_buffer[21]};

  printf("\n");
  for (size_t i = 0; i <= 10; i++) {
    printf("%c", output_buffer[i]);
  }
  printf("\n\n");
  close(fd);
}
