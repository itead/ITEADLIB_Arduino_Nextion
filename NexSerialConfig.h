/**
 * @file NexSerialConfig.h
 *
 * Serial configure. 
 *
 * @author  Wu Pengfei (email:<pengfei.wu@itead.cc>)
 * @date    2015/7/10
 * @copyright 
 * Copyright (C) 2014-2015 ITEAD Intelligent Systems Co., Ltd. \n
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 */

#ifndef __NexSerialConfig_H__
#define __NexSerialConfig_H__

/*enable debug serial*/
#define DEBUG_SERIAL_ENABLE 

#ifdef DEBUG_SERIAL_ENABLE
#define dbSerialPrint(a)    Serial.print(a)
#define dbSerialPrintln(a)  Serial.println(a)
#define dbSerialBegin(a)    Serial.begin(a)
#else
#define dbSerialPrint(a)
#define dbSerialPrintln(a)
#define dbSerialBegin(a)
#endif

/*Define Nextion serial*/
#define nexSerial Serial2
#endif 
