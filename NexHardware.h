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
 * Nextion Startup callback function
 * Returned when Nextion has started or reset
 * 
 */
extern void (*nextionStartupCallback)();
//extern std::function<void()> nextionStartupCallback;


/**
 * Current Page ID callback function
 * The device returns this data after receiving “sendme” instruction)
 * 
 *  uint8_t pageId
 */
extern void (*currentPageIdCallback)(uint8_t);
//extern std::function<void(uint8_t)> currentPageIdCallback;

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
extern void (*touchCoordinateCallback)(uint16_t,uint16_t,uint8_t);
//extern std::function<void(uint16_t,uint16_t,uint8_t)>  touchCoordinateCallback;

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
extern void (*touchEventInSleepModeCallback)(uint16_t,uint16_t,uint8_t);
//extern std::function<void(uint16_t,uint16_t,uint8_t)> touchEventInSleepModeCallback;

/**
 * Device automatically enters into sleep mode callback function
 * Only when the device automatically enters into sleep mode will return this data.
 * If execute serial command “sleep = 1” to enter into sleep mode, it will not return this data.
 */
extern void (*automaticSleepCallback)();
//extern std::function<void()> automaticSleepCallback;

/**
 * Device automatically wake up callback function
 * Only when the device automatically wake up will return this data.
 * If execute serial command “sleep=0” to wake up, it will not return this data. 
 */
extern void (*automaticWakeUpCallback)();
//extern std::function<void()> automaticWakeUpCallback;

/**
 * Nextion Ready callback function
 * Returned when Nextion has powered up and is now initialized successfully
 */
extern void (*nextionReadyCallback)();
//extern std::function<void()> nextionReadyCallback;

/**
 * Start SD card upgrade callback function
 * This data is sent after the device power on and detect SD card, and then enter upgrade interface
 */
extern void (*startSdUpgradeCallback)();
//extern std::function<void()> startSdUpgradeCallback;

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

/* Send Raw data to device
*
* parameter raw data buffer
*/
#ifdef STD_SUPPORT
void sendRawData(const std::vector<uint8_t> &data);
#endif

/* Send Raw data to device
*
* @param buf - raw data buffer poiter
* @param len - raw data buffer pointer
*/
void sendRawData(const uint8_t *buf, uint16_t len);


/* Send Raw byte to device
*
* parameter raw byte
*/
void sendRawByte(const uint8_t byte);

/* read Bytes from device
 * @brief 
 * 
 * @param buffer - receive buffer
 * @param size  - bytes to read
 * @param timeout  timeout ms
 * @return size_t read bytes can be less that size (timeout case) 
 */
size_t readBytes(uint8_t* buffer, size_t size, size_t timeout=1000);


/* Receive command
*
* @param command - command to be received / checked
* @param timeout - set timeout time.
*
* @retval true - success.
* @retval false - failed. 
*/
bool recvCommand(const uint8_t command, uint32_t timeout);

/*
 * Command is executed successfully. 
 *
 * @param timeout - set timeout time.
 *
 * @retval true - success.
 * @retval false - failed. 
 *
 */
bool recvRetCommandFinished(uint32_t timeout = 200);

/*
 * Transpared data mode setup successfully 
 *
 * @param timeout - set timeout time.
 *
 * @retval true - success.
 * @retval false - failed. 
 *
 */
bool RecvTransparendDataModeReady(uint32_t timeout = 400);

/*
 * Transpared data mode finished 
 *
 * @param timeout - set timeout time.
 *
 * @retval true - success.
 * @retval false - failed. 
 *
 */
bool RecvTransparendDataModeFinished(uint32_t timeout = 200);

/**
 * Init Nextion.  
 * 
 * @param paud (2400, 4800, 9600, 19200, 38400, 57600, 115200 )
 * 
 * @return true if success, false for failure. 
 */
bool nexInit(const uint32_t baud=9600);

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

#endif /* #ifndef __NEXHARDWARE_H__ */
