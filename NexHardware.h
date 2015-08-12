/**
 * @file NexHardware.h
 *
 * Hardware Srial API. 
 *
 * @author  Wu Pengfei (email:<pengfei.wu@itead.cc>)
 * @date    2015/8/11
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
#include "NexSerialConfig.h"
#include "NexTouch.h"

bool recvRetNumber(uint32_t *number, uint32_t timeout = 100);
uint16_t recvRetString(char *buffer, uint16_t len, uint32_t timeout = 100);
void sendCommand(const char* cmd);
bool recvRetCommandFinished(uint32_t timeout = 100);

bool nexInit(void);
void nexLoop(NexTouch **nex_listen_list);

#endif /* #ifndef __NEXHARDWARE_H__ */
