/**
 * @file NexWaveform.cpp
 *
 * API of NexWaveform. 
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

#include "NexWaveform.h"

/**
 * Constructor,inherited NexTouch's constructor function.
 *
 */
NexWaveform::NexWaveform(NexPid pid, NexCid cid, char *name)
    :NexTouch(pid, cid, name)
{
}


/**
 * Add value to show. 
 *
 * param ch - channel of waveform(0-3). 
 * @param number - the value of waveform.  
 *
 * @retval true - success. 
 * @retval false - failed. 
 */
bool NexWaveform::addValue(uint8_t ch, uint8_t number)
{
    char buf[15] = {0};
    
    if (ch > 3)
    {
        return false;
    }
    
    sprintf(buf, "add %u,%u,%u", getCid(), ch, number);

    sendCommand(buf);
    return true;
}
 
