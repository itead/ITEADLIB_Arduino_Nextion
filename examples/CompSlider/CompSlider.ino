/**
 * @example CompSlider.ino
 *
 * @par How to Use
 * Show how to use API of class NexSlider.  
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
 
#include "Nextion.h"


NexText t0 = NexText(0, 2, "t0");
NexSlider h0 = NexSlider(0, 1, "h0");

NexTouch *nex_listen_list[] = 
{
    &h0,
    NULL
};

void h0PopCallback(void *ptr)
{
    uint32_t number = 0;
    char temp[10] = {0};
    
    dbSerialPrintln("h0PopCallback");

    h0.getValue(&number);
    utoa(number, temp, 10);
    t0.setText(temp);
}


void setup(void)
{
    nexInit();
    h0.attachPop(h0PopCallback);
    dbSerialPrintln("setup done");
}

void loop(void)
{
    nexLoop(nex_listen_list);
}

