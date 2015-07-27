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

/*define serial for debug*/
#define dbSerial Serial

#ifdef DEBUG_SERIAL_ENABLE
#define dbSerialPrint(a)    dbSerial.print(a)
#define dbSerialPrintln(a)  dbSerial.println(a)
#define dbSerialBegin(a)    dbSerial.begin(a)
#else
#define dbSerialPrint(a)
#define dbSerialPrintln(a)
#define dbSerialBegin(a)
#endif

/*define serial for communicate with Nextion screen*/
#define nexSerial Serial2

#endif 
