@mainpage Home Page

# Nextion

--------------------------------------------------------------------------------

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

# Download Source Code 

Latest version is unstable and a mass of change may be applied in a short time 
without any notification for users. Commonly, it is for developers of this 
library. 

**Release version is recommanded for you, unless you are one of developers of this 
library.**

**Release notes** is at
<https://github.com/itead/ITEADLIB_Arduino_Nextion/blob/master/release_notes.md>.

## Latest(unstable)

Latest source code(master branch) can be downloaded:
  <https://github.com/itead/ITEADLIB_Arduino_Nextion/archive/master.zip>. 

You can also clone it via git:

    git clone https://github.com/itead/ITEADLIB_Arduino_Nextion

## Releases(stable)

  - https://github.com/itead/ITEADLIB_Arduino_Nextion/archive/v0.7.0.zip
  - https://github.com/itead/ITEADLIB_Arduino_Nextion/archive/v0.7.0.tar.gz

All releases can be available from:
<https://github.com/itead/ITEADLIB_Arduino_Nextion/releases>.

# Documentation

[Latest Online Documentation](http://docs.iteadstudio.com/ITEADLIB_Arduino_Nextion/index.html)
contains Configuration, Get Started, Reference of API and Examples, etc.

Offline Documentation's entry `doc/Documentation/index.html` shiped with source code
can be open in your browser such as Chrome, Firefox or any one you like. 

# Suppported Mainboards

**All boards, which has one or more hardware serial, can be supported.**

For example:

  - Iteaduino MEGA2560
  - Iteaduino UNO
  - Arduino MEGA2560
  - Arduino UNO

# Configuration

In configuration file NexConfig.h, you can find two macros below:

  - dbSerial: Debug Serial (baudrate:9600), needed by beginners for debug your 
    nextion applications or sketches. If your complete your work, it will be a 
    wise choice to disable Debug Serial.

  - nexSerial: Nextion Serial, the bridge of Nextion and your mainboard.

**Note:** the default configuration is for MEGA2560.

## Redirect dbSerial and nexSerial

If you want to change the default serial to debug or communicate with Nextion ,
you need to modify the line in configuration file:

	#define dbSerial Serial    ---> #define dbSerial Serialxxx
    #define nexSerial Serial2  ---> #define nexSeria Serialxxx

## Disable Debug Serial

If you want to disable the debug information,you need to modify the line in 
configuration file:

    #define DEBUG_SERIAL_ENABLE ---> //#define DEBUG_SERIAL_ENABLE

# UNO-like Mainboards

If your board has only one hardware serial, such as UNO, you should disable 
dbSerial and redirect nexSerial to Serial(Refer to section:`Serial configuration`). 

# Useful Links

<http://blog.iteadstudio.com/nextion-tutorial-based-on-nextion-arduino-library/>

# License

-------------------------------------------------------------------------------


    DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE 
        Version 2, December 2004 

    Copyright (C) 2014 ITEAD Studio

    Everyone is permitted to copy and distribute verbatim or modified 
    copies of this license document, and changing it is allowed as long 
    as the name is changed. 

        DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE 
        
    TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION 

    0. You just DO WHAT THE FUCK YOU WANT TO.


-------------------------------------------------------------------------------
