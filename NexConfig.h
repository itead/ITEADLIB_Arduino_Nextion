/**
 * @file NexConfig.h
 *
 * Options for user can be found here. 
 *
 * @author  Wu Pengfei (email:<pengfei.wu@itead.cc>)
 * @date    2015/8/13
 * @author Jyrki Berg 2/17/2019 (https://github.com/jyberg)
 * 
 * @copyright 
 * Copyright (C) 2014-2015 ITEAD Intelligent Systems Co., Ltd. \n
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 */
#ifndef __NEXCONFIG_H__
#define __NEXCONFIG_H__

/**
 * @addtogroup Configuration 
 * @{ 
 */

/** 
 * Define DEBUG_SERIAL_ENABLE to enable debug serial. 
 * Comment it to disable debug serial. 
 */
//#define DEBUG_SERIAL_ENABLE

/**
 * Define dbSerial for the output of debug messages. 
 * it is resonsibility of main program to initialize debug serial port (begin(...)
 */
//#define dbSerial Serial

/**
 * Define nexSerial for communicate with Nextion touch panel. 
 * Define NEX_SOFTWARE_SERIAL if software serial used
 * NodeMcu/Esp8266 can use harware serial (Serial) but it uses same serial as usb communication and
 * during SW upload NodeMcu RX pin must be disconnected from Nextion
 */
//#define NEX_SOFTWARE_SERIAL
#ifndef NEX_SOFTWARE_SERIAL
// hardware Serial port
#define nexSerial Serial
#else
// NodeMcu / Esp8266 Softwareserial if usb port used for debug 
#define NEX_RX 13 // D5
#define NEX_TX 15 // D6
#endif


#ifdef DEBUG_SERIAL_ENABLE
#define dbSerialPrint(a)    dbSerial.print(a)
#define dbSerialPrintln(a)  dbSerial.println(a)
#define dbSerialBegin(a)    dbSerial.begin(a)
#else
#define dbSerialPrint(a)   do{}while(0)
#define dbSerialPrintln(a) do{}while(0)
#define dbSerialBegin(a)   do{}while(0)
#endif

/**
 * @}
 */

#endif /* #ifndef __NEXCONFIG_H__ */
