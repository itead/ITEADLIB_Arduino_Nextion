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

/*Define debug serial*/
#define dbSerial Serial

/*Define Nextion serial*/

// To also support the growing community of Particle devices (www.particle.io)
#if defined(SPARK) || defined(PLATFORM_ID)
  #define nexSerial Serial1  // RX/TX pins
  //#define nexSerial Serial2  // D0/D1 pins on Core (on Photon not easily usable)
#elif
  #define nexSerial Serial2
#endif

#endif 
