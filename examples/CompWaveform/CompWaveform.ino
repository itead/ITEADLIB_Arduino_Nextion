/**
 * @example CompWaveform.ino
 *
 * @par Show how to use API of class NexWaveform.  
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
 
#include "NexText.h"
#include "NexWaveform.h"

NexWaveform s0 = NexWaveform(0, 1, "s0");

static uint8_t data = 0;

void setup(void)
{
    nexInit();
    dbSerialPrintln("setup done");
}

void loop(void)
{
    data++;
    data += random(0, 5);
    if (data > 200)
    {
        data = 0;
    }
    s0.addValue(0, data);
    s0.addValue(1, data % 40 + 80);
}

