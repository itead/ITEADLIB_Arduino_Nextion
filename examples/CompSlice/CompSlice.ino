/**
 * @example CompSlice.ino
 *
 * @par Show how to use API of class NexSlice.  
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

#include "NexSlice.h"

NexSlice q0 = NexSlice(0, 1, "q0");

NexTouch *nexListenList[] = 
{
    &q0,
    NULL
};

void q0PopCallback(void *ptr)
{
    uint32_t number = 0;
    dbSerialPrintln("q0PopCallback");

    q0.getPic(&number);

    number += 1;
    number %= 2;
    
    q0.setPic(number);
}


void setup(void)
{
    dbSerialBegin(9600);
    nexInit();
    q0.attachPop(q0PopCallback);
    dbSerialPrintln("setup done");
}

void loop(void)
{
    dbSerialPrintln("nexLoop");
    nexLoop(nexListenList);
}

