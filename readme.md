# HMI

A HMI library for Arduino providing an easy-to-use way to manipulate LCD touch screen. 

# How to get started

On the home page of API documentation, the tabs of Examples, Classes and Modules 
will be useful for Arduino lovers. 


# Mainboard Requires

  - RAM: not less than 2KBytes
  - Serial: one serial (HardwareSerial or SoftwareSerial) at least 

# Suppported Mainboards
  
  - Arduino UNO and its derivatives
  - Arduino MEGA and its derivatives
  
# Using SoftwareSerial

If you want to use SoftwareSerial to communicate with LCD touch screen, you need to modify
the line in file `hmi.h`: 

    //#define HMI_SOFTWARE_SERIAL

After modification, it should be:

    #define HMI_SOFTWARE_SERIAL

# Hardware Connection

HMI library only needs an uart for hardware connection. All communications are done via uart.
Before using this examples, you should ensure that your LCD touch screen have been connected. 
   
-------------------------------------------------------------------------------

# The End!

-------------------------------------------------------------------------------
