/**
 * @file Nexpointer.cpp
 *
 * API of Nexpointer. 
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

#include "NexPointer.h"

/**
 * Constructor,inherited NexTouch's constructor function.
 *
 */
NexPointer::NexPointer(NexPid pid, NexCid cid, char *name)
    :NexTouch(pid, cid, name)
{
}

/**
 * Get the value of pointer.
 * 
 * @param number - an output parameter to save pointer's value.
 * 
 * @retval true - success. 
 * @retval false - failed. 
 */
bool NexPointer::getValue(uint32_t *number)
{
    String cmd = String("get ");
    cmd += getObjName();
    cmd += ".val";
    sendCommand(cmd.c_str());
    return recvRetNumber(number);
}

/**
 * Set the value of pointer. 
 *
 * @param number - the value of pointer.  
 *
 * @retval true - success. 
 * @retval false - failed. 
 */
bool NexPointer::setValue(uint32_t number)
{
    char buf[10] = {0};
    String cmd;
    
    utoa(number, buf, 10);
    cmd += getObjName();
    cmd += ".val=";
    cmd += buf;

    sendCommand(cmd.c_str());
    return recvRetCommandFinished();
}
 
