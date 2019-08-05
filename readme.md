@mainpage Home Page

# Enhanced Nextion Library

--------------------------------------------------------------------------------
Jyrki Berg 6/12/2019 (https://github.com/jyberg)

Nextion display communication stabilization, now serial communication is more stable and delay agnostic.
corrected waveform AddValues error schenario.

Jyrki Berg 3/20/2019
Enhanced and corrected Nextion library version for Arduino/Esp8266/NodeMcu, based on original Nextion Arduino library.

- Added support for NodeMcu/esp8266, Software serial, Software serial can be used with arduino
- Added support to define communication baud rate in nexInit functiono
- Added support for global Nextion objects. (Optional page parameter added in the components)
- NexVariable corrected to use int32_t data type
- NextText corrected to return tru/false, and string length is returned in len parameter
- NextText String object support added
- other small bug fixes done
- Added to support global Nextion events like CurrentPageIdCallback,systemStartUpCallback,... see NexHardware.h
- Waveform corrections:
  - Inheritance to support toutch events
  - return values corrected
  - set/get channel colour corrected to support all channels
- Waveform enhancedments:
  - Suport scaled values:
   - define min and max values + coponent height in pixels (component support 255 pixel max height). When value is added to changell it is automatically scaled to component size and min/max value definitions.
  - Add multiple values to line
  - Clear component
- Added get component height/width function calls to NexObject  
- examples Nextion editor projects corrected
- C++ std library usage made optional, (e.g std::vector) See NexConfig.h #define STD_SUPPORT
- C style versions added for functions that uses std::vector etc..

Nextion serial instruction set see: https://www.itead.cc/wiki/Nextion_Instruction_Set or https://nextion.itead.cc/resources/documents/instruction-set/

-For some reason I need to remove NexUpload.h & NexUpload.cpp when using the library in PlatformIO
  some platform header files not found spontaneously when building, adding the libray path in platformio.ini did not help.

# Introduction

Nextion Arduino library provides an easy-to-use way to manipulate Nextion serial<br />
displays. Users can use the libarry freely, either in commerical projects or <br />
open-source prjects,  without any additional condiitons.<br />
<br />
Nextion easy to use UI Editor: https://nextion.itead.cc/resources/download/nextion-editor/<br />
Enhanced easy to use Nextion Font Editor: https://github.com/hagronnestad/nextion-font-editor<br />

For more information about the Nextion display project, please visit<br /> 
[the wiki。](http://wiki.iteadstudio.com/Nextion_HMI_Solution)<br />

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

In configuration file NexConfig.h, you can configure Hardware / software, debug serial usage<br />

In case of Hardware serial comment/undefine "// #define NEX_SOFTWARE_SERIAL" line and<br />
configure used Serial port on line "#define nexSerial Serial"<br />
by default Serial poirt used (NodeMcu/Esp8266 hardware serial)  

Software serial used if "#define NEX_SOFTWARE_SERIAL" when NEX_SOFTWARE_SERIAL is defined<br />
use  NEX_RX and NEX_TX definitions to define used software serial ports.<br />
By default NodeMcu:<br />
  "#define NEX_RX D2"  
  "#define NEX_TX D1"  
NodeMcu board pin numbers not match with Esp8266 pin numbers. So use D<x> pin number definitions from pins_arduino.h  
You need to remember that Software serial is not nessessary workin with out problmes at least when using NodeMcu/Esp8266 boards (See power tips...).<br />

If you want activate Debug messages, uncomment "//#define DEBUG_SERIAL_ENABLE" line and define serial port used for debug messges using line:<br />
"//#define dbSerial Serial", it is responsibiity of main program to initialize/open debug serial port.  

# Power tips

Nextion and NodeMcu/Esp8266 is sensitive with power quality and current. Especially when Software serial is used, (Serial message quality can be bad and then functionality is not stable...). Don't power Nextion display from NodeMcu board, because Nextion takes guite mutch of current, and NodeMcu internal power requlator is not good. Use separate power to power Nextion and connect Nextion and NodeMcu/Esp8266 board gnd to commond gnd point.  


# Useful Links
- https://unofficialnextion.com/
- https://nextion.itead.cc/resources/download/nextion-editor/ 
- https://github.com/hagronnestad/nextion-font-editor 
- http://blog.iteadstudio.com/nextion-tutorial-based-on-nextion-arduino-library/ 
- https://www.itead.cc/wiki/Nextion_Instruction_Set 
- https://nextion.itead.cc/resources/documents/instruction-set/  
- http://wiki.iteadstudio.com/Nextion_HMI_Solution 
