/**
 * @example CompButton.ino
 *
 * @par Show how to use API of class NexButton.  
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

#include "NexTouch.h"

void setup(void)
{   
    uint8_t temp;
    dbSerial.begin(9600);
    nexInit();  

    setDeviceDelay(100); 
    #if 0
    sendCurrentPageId(&temp,500);
    touchCalibration(500);
    disableTouchFocus(500);
    pauseSerialCommand(500);
    recoverySerialCommand(500);
    setCurrentBrightness(50);
    setDefaultDim(60);
    sleepMode(0);
    setDeviceDelay(200);
    setCurrentBaudrate(9600);
    setDefaultBaudrate(12400);
    #endif 

    dbSerial.println("setup done");  
}

void loop(void)
{
    dbSerial.println("nexLoop");
    while(1);
}
