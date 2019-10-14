# ECEN404
ECEN 404 Wildfire Project

9/16/19 Update:

Kelli Templeton:
1. Tested the UART retrieval and parsing code for the MCU-GSM integration (uploaded code today 9/16/19)
2. Finalized the web application (will upload code today 9/16/19)
3. Created the initial physical container 
4. Began the design of the mobile PCB. 

Joshua Hornsey:
1. Worked on the camera4
2. Finished tutorial on Mask R-CNN object detection models
3. Finished tutorial on YOLO object detection models

Mevin Ansa:

1.Begun to program UART data frames to GSM module

2.Begun to program GPS module to microcontroller

3.Begun design of PCB for power supply




9/23/19 Update:

Kelli Templeton:
1. Integrated GSM module with ODROID successfully which invovled:
  1.1 Integrating GSM module with Arduino for communication testing
  1.2 Testing viable types of messages (strings, dictionaries, byte arrays)
  1.3 Integrating message receiving and parsing code with MQTT code
  1.4 Validating message accuracy


9/26/19 Update:

Kelli Templeton:
1. Validated connection of ODROID and GSM module
2. Wrote initial camera integration code
3. Wrote initial code to pull sensor data and format it into expected string



10/3/19 Update:

Kelli Templeton:
1. Tested and improved camera integration code

10/14/19 Update:

Kelli Templeton:
1. Installed all correct image processing dependencies on ODROID
2. Succesfully ran image processing model on ODROID
3. Wrote, tested, and finalized code to pull data from main module sensors every 5 minutes
4. Wrote initial code to pull data from gps module and remote module
5. Wrote initial code for camera - image processing model integration
