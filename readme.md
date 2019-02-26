@mainpage Home Page

# Nextion

--------------------------------------------------------------------------------

Jyrki Berg 2/17/2019 (https://github.com/jyberg)
Enhanced and corrected Nextion library version for Arduino/Esp8266/NodeMcu, based on original Nextion Arduino library

- Added support for NodeMcu/esp8266, Software serial, Software serial can be used with arduino also
- Added support for global Nextion objects. (Optional page parameter added in the components)
- NexVariable corrected to use int32_t data type
- NextText corrected to return tru/false, and string length is returned in len parameter
- NextText String object support added
- other small bug fixes done
- Added to support global Nextion events like CurrentPageIdCallback,systemStartUpCallback,...
- examples Nextion editor projects corrected

Nextion serial instruction set see: https://www.itead.cc/wiki/Nextion_Instruction_Set or https://nextion.itead.cc/resources/documents/instruction-set/

-For some reason I need to remove NexUpload.h & NexUpload.cpp when using the library in PlatformIO
  some platform header files not found spontaneously when building, adding the libray path in platformio.ini did not help.

# Introduction

Nextion Arduino library provides an easy-to-use way to manipulate Nextion serial
displays. Users can use the libarry freely, either in commerical projects or 
open-source prjects,  without any additional condiitons. 

For more information about the Nextion display project, please visit 
[the wiki。](http://wiki.iteadstudio.com/Nextion_HMI_Solution)  
The wiki provdies all the necessary technical documnets, quick start guide, 
tutorials, demos, as well as some useful resources.

To get your Nextion display, please visit 
[iMall.](http://imall.itead.cc/display/nextion.html)

To discuss the project?  Request new features?  Report a BUG? please visit the 
[Forums](http://support.iteadstudio.com/discussions/1000058038)

# Suppported Mainboards

**All boards, which has one or more hardware serial, can be supported.**

For example:

  - Iteaduino MEGA2560
  - Iteaduino UNO
  - Arduino MEGA2560
  - Arduino UNO
  - NodeMcu
  - Esp8266

# Configuration

In configuration file NexConfig.h, you can find two macros below:

  - dbSerial: Debug Serial (baudrate:9600), needed by beginners for debug your 
    nextion applications or sketches. If your complete your work, it will be a 
    wise choice to disable Debug Serial.

  - nexSerial: Nextion Serial, the bridge of Nextion and your mainboard.

## Redirect dbSerial and nexSerial

If you want to change the default serial to debug or communicate with Nextion ,
you need to modify the line in configuration file:

    #define dbSerial Serial    ---> #define dbSerial Serialxxx
    #define nexSerial Serial2  ---> #define nexSeria Serialxxx

## Disable Debug Serial

If you want to disable the debug information,you need to modify the line in 
configuration file:

    #define DEBUG_SERIAL_ENABLE ---> //#define DEBUG_SERIAL_ENABLE


# Useful Links

<http://blog.iteadstudio.com/nextion-tutorial-based-on-nextion-arduino-library/>

