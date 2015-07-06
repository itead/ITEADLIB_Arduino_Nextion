# Nextion Library for Arduino 
Nextion Arduino library provides an easy-to-use way to manipulate Nextion serial displays. 
Users can use the libarry freely, either in commerical projects or open-source prjects,  without any additional condiitons. 

For more information about the Nextion display project, please visit [the wiki。](http://wiki.iteadstudio.com/Nextion_HMI_Solution)  
The wiki provdies all the necessary technical documnets, quick start guide, tutorials, demos, as well as some useful resources.

To get your Nextion display, please visit [iMall.](http://imall.itead.cc/display/nextion.html)
To discuss the project?  Request new features?  Report a BUG? please visit the [Forums](http://support.iteadstudio.com/discussions/1000058038)

​
# Source 

Latest source code can be download at https://github.com/itead/ITEADLIB_Arduino_Nextion.

You can clone it by:

    git clone https://github.com/itead/ITEADLIB_Arduino_Nextion


# Hareware requirement 

  - RAM: not less than 2KBytes
  - Serial: one serial (HardwareSerial or SoftwareSerial) at least 

Suppported Mainboards: Arduino family and it's derivatives.
We test this library with Iteaduino UNO and Iteaduino Mega2560.


# Using SoftwareSerial

If you want to use SoftwareSerial to communicate with Nextion display, you need to modify
the line in file `hmi.h`: 

    //#define HMI_SOFTWARE_SERIAL

After modification, it should be:

    #define HMI_SOFTWARE_SERIAL

Nextion library only requires an uart for hardware connection. All communications are done via uart.   
-------------------------------------------------------------------------------

# The End!

-------------------------------------------------------------------------------
