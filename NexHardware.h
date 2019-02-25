/**
 * @file NexHardware.h
 *
 * The definition of base API for using Nextion. 
 *
 * @author  Wu Pengfei (email:<pengfei.wu@itead.cc>)
 * @date    2015/8/11
 * @author Jyrki Berg 2/24/2019 (https://github.com/jyberg)
 * 
 * @copyright 
 * Copyright (C) 2014-2015 ITEAD Intelligent Systems Co., Ltd. \n
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 */
#ifndef __NEXHARDWARE_H__
#define __NEXHARDWARE_H__
#include <Arduino.h>
#include "NexConfig.h"
#include "NexTouch.h"

/**
 * @addtogroup CoreAPI 
 * @{ 
 */

/**
 * Current Page ID callback function
 * The device returns this data after receiving “sendme” instruction)
 * 
 *  uint8_t pageId
 */
extern std::function<void(uint8_t)> currentPageIdCallback;

/**
 * Touch Coordinate callback function
 * When the system variable “sendxy” is 1, return this data at TouchEvent occurring
 * 
 * uint16_t x
 * uint16_t y
 * uint8_t TouchEvent
 * 
 * Definition of TouchEvent: Press Event 0x01, Release Event 0X00 
 */
extern std::function<void(uint16_t,uint16_t,uint8_t)>  touchCoordinateCallback;

/**
 * Touch Event in sleep mode callback function
 * When the device enters sleep mode, return this data at TouchEvent occurring
 * 
 * uint16_t x
 * uint16_t y
 * uint8_t TouchEvent
 * 
 * Definition of TouchEvent: Press Event 0x01, Release Event 0X00 
 */
extern std::function<void(uint16_t,uint16_t,uint8_t)> touchEventInSleepModeCallback;

/**
 * Device automatically enters into sleep mode callback function
 * Only when the device automatically enters into sleep mode will return this data.
 * If execute serial command “sleep = 1” to enter into sleep mode, it will not return this data.
 */
extern std::function<void()> automaticSleepCallback;

/**
 * Device automatically wake up callback function
 * Only when the device automatically wake up will return this data.
 * If execute serial command “sleep=0” to wake up, it will not return this data. 
 */
extern std::function<void()> automaticWakeUpCallback;

/**
 * System successful start up callback function
 * This data is sent after a successful power-on initialization on the device
 */
extern std::function<void()> systemStartUpCallback;

/**
 * Start SD card upgrade callback function
 * This data is sent after the device power on and detect SD card, and then enter upgrade interface
 */
extern std::function<void()> startSdUpgradeCallback;

/**
 * Init Nextion.  
 * 
 * @return true if success, false for failure. 
 */
bool nexInit(void);

/**
 * Listen touch event and calling callbacks attached before.
 * 
 * Supports push and pop at present. 
 *
 * @param nex_listen_list - index to Nextion Components list. 
 * @return none. 
 *
 * @warning This function must be called repeatedly to response touch events
 *  from Nextion touch panel. Actually, you should place it in your loop function. 
 */
void nexLoop(NexTouch *nex_listen_list[]);

/**
 * @}
 */

bool recvRetNumber(uint32_t *number, uint32_t timeout = 100);
bool recvRetNumber(int32_t *number, uint32_t timeout = 100);
bool recvRetString(String &str, uint32_t timeout = 100);
bool recvRetString(char *buffer, uint16_t &len, uint32_t timeout = 100);

/* Send Command to device
*
* parameter command string
*/
void sendCommand(const char* cmd);

bool recvRetCommandFinished(uint32_t timeout = 100);

#endif /* #ifndef __NEXHARDWARE_H__ */
