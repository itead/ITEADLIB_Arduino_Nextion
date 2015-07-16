/**
 * @file NexButton.cpp
 *
 * API of NexButton. 
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

/**
 * Constructor,inherited NexTouch's constructor function.
 *
 */
NexButton::NexButton(NexPid pid, NexCid cid, char *name, NexTouchEventCb pop, void *pop_ptr)
    :NexTouch(pid, cid, name, pop, pop_ptr)
{
}

/**
 * Get text value from button component.
 *
 * @param buffer - text buffer. 
 * @param len - text buffer length.
 *
 * @return the text buffer length
 */
uint16_t NexButton::getText(char *buffer, uint16_t len)
{
    String cmd;
    cmd += "get ";
    cmd += getObjName();
    cmd += ".txt";
    sendCommand(cmd.c_str());
    return recvRetString(buffer,len);
}

/**
 * Set text value of button component.
 *
 * @param buffer - text buffer. 
 * 
 * @retval true - success. 
 * @retval false - failed. 
 */
bool NexButton::setText(const char *buffer)
{
    String cmd;
    cmd += getObjName();
    cmd += ".txt=\"";
    cmd += buffer;
    cmd += "\"";
    sendCommand(cmd.c_str());
    return recvRetCommandFinished();    
}

/**
 * Register button pop callback function. 
 *
 * @param pop - the pointer to button pop callback function.
 * @param ptr - the parameter to be transmitted to button pop callback function. 
 */
void NexButton::attachPop(NexTouchEventCb pop, void *ptr)
{
    NexTouch::attachPop(pop, ptr);
}

/**
 * Unload button pop callback function.
 *
 */
void NexButton::detachPop(void)
{
    NexTouch::detachPop();   
}
 

