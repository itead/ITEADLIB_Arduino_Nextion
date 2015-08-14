/**
 * @example CompGauge.ino
 *
 * @par How to Use
 * Show how to use API of class NexGauge.  
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

#include "Nextion.h"

NexGauge pointer  = NexGauge(0, 1, "pointer");
NexButton btn_up   = NexButton(0, 2, "btn_up");
NexButton btn_down = NexButton(0, 3, "btn_down");

NexTouch *nex_listen_list[] = 
{
    &btn_up,
    &btn_down,
    NULL
};

void buttonUpPopCallback(void *ptr)
{
    uint32_t number = 0;
    dbSerialPrintln("buttonUpPopCallback");

    pointer.getValue(&number);

    number += 5;
    if (number >= 360)
    {
        number = 0;
    }
    
    pointer.setValue(number);
}
void buttonDownPopCallback(void *ptr)
{
    uint32_t number = 0;
    dbSerialPrintln("buttonDownPopCallback");

    pointer.getValue(&number);

    if (number >= 5)
    {
        number -= 5;
    }
    
    pointer.setValue(number);
}



void setup(void)
{
    nexInit();
    btn_up.attachPop(buttonUpPopCallback);
    btn_down.attachPop(buttonDownPopCallback);
    dbSerialPrintln("setup done");
}

void loop(void)
{
    nexLoop(nex_listen_list);
}

