/**
 * @example CompText.ino
 *
 * @par Show how to use API of class NexText.  
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

#include "NexButton.h"
#include "NexText.h"

void t0PopCallback(void *ptr);
void b0PopCallback(void *ptr);
void b1PopCallback(void *ptr);

NexText t0 = NexText(0, 1, "t0", t0PopCallback);
NexButton b0 = NexButton(0, 2, "b0", b0PopCallback);
NexButton b1 = NexButton(0, 3, "b1", b1PopCallback);

char buffer[100] = {0};

NexTouch *nexListenList[] = 
{
    &t0,
    &b0,
    &b1,
    NULL
};

void t0PopCallback(void *ptr)
{
    dbSerial.println("t0PopCallback");
    t0.setText("50");
}

void b0PopCallback(void *ptr)
{
    uint16_t len;
    uint16_t number;
    
    dbSerial.println("b0PopCallback");

    memset(buffer, 0, sizeof(buffer));
    t0.getText(buffer, sizeof(buffer));
    
    number = atoi(buffer);
    number += 1;

    memset(buffer, 0, sizeof(buffer));
    itoa(number, buffer, 10);
    
    t0.setText(buffer);
}

void b1PopCallback(void *ptr)
{
    uint16_t len;
    uint16_t number;
    
    dbSerial.println("b1PopCallback");

    memset(buffer, 0, sizeof(buffer));
    t0.getText(buffer, sizeof(buffer));
    
    number = atoi(buffer);
    number -= 1;

    memset(buffer, 0, sizeof(buffer));
    itoa(number, buffer, 10);
    
    t0.setText(buffer);
}

void setup(void)
{
    dbSerial.begin(9600);
    nexInit();
    dbSerial.println("setup done");
}

void loop(void)
{
    dbSerial.println("nexLoop");
    nexLoop(nexListenList);
}

