@mainpage Home Page

# Enhanced Nextion Library

--------------------------------------------------------------------------------

Jyrki Berg 2/17/2019 (https://github.com/jyberg)
Enhanced and corrected Nextion library version for Arduino/Esp8266/NodeMcu, based on original Nextion Arduino library.

- Added support for NodeMcu/esp8266, Software serial, Software serial can be used with arduino also
- Added support for global Nextion objects. (Optional page parameter added in the components)
- NexVariable corrected to use int32_t data type
- NextText corrected to return tru/false, and string length is returned in len parameter
- NextText String object support added
- other small bug fixes done
- Added to support global Nextion events like CurrentPageIdCallback,systemStartUpCallback,... see NexHardware.h
- examples Nextion editor projects corrected

Nextion serial instruction set see: <https://www.itead.cc/wiki/Nextion_Instruction_Set> or <https://nextion.itead.cc/resources/documents/instruction-set/>

-For some reason I need to remove NexUpload.h & NexUpload.cpp when using the library in PlatformIO
  some platform header files not found spontaneously when building, adding the libray path in platformio.ini did not help.

# Introduction

Nextion Arduino library provides an easy-to-use way to manipulate Nextion serial
displays. Users can use the libarry freely, either in commerical projects or 
open-source prjects,  without any additional condiitons.

Nextion easy to use UI Editor: <https://nextion.itead.cc/resources/download/nextion-editor/>
Enhanced easy to use Nextion Font Editor: <https://github.com/hagronnestad/nextion-font-editor>

For more information about the Nextion display project, please visit 
[the wiki。](http://wiki.iteadstudio.com/Nextion_HMI_Solution)  
The wiki provdies all the necessary technical documnets, quick start guide, 
tutorials, demos, as well as some useful resources.

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

In configuration file NexConfig.h, you can configure Hardware / software, debug serial usage

In case of Hardware serial comment/undefine "// #define NEX_SOFTWARE_SERIAL" line and
configure used Serial port on line "#define nexSerial Serial" by default Serial poirt used (NodeMcu/Esp8266 hardware serial)

Software serial used if "#define NEX_SOFTWARE_SERIAL" when NEX_SOFTWARE_SERIAL is defined use  NEX_RX and NEX_TX definitions to define used software serial ports. By default NodeMcu:
"#define NEX_RX 13 // D5"
"#define NEX_TX 15 // D6"
You need to remember that Software serial is not nessessary workin with out problmes at least when using NodeMcu/Esp8266 boards.

If you want activate Debug messages, uncomment "//#define DEBUG_SERIAL_ENABLE" line and define serial port used for debug messges using line "//#define dbSerial Serial", it is responsibiity of main program to initialize/open debug serial port.


# Useful Links
- <https://nextion.itead.cc/resources/download/nextion-editor/> 
- <https://github.com/hagronnestad/nextion-font-editor> 
- <http://blog.iteadstudio.com/nextion-tutorial-based-on-nextion-arduino-library/> 
- <https://www.itead.cc/wiki/Nextion_Instruction_Set> 
- <https://nextion.itead.cc/resources/documents/instruction-set/> 
- <http://wiki.iteadstudio.com/Nextion_HMI_Solution> 
