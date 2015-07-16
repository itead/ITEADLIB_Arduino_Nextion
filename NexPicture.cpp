/**
 * @file NexPicture.cpp
 *
 * API of NexPicture. 
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

#include "NexPicture.h"

/**
 * Constructor,inherited NexTouch's constructor function.
 *
 */
NexPicture::NexPicture(NexPid pid, NexCid cid, char *name, NexTouchEventCb pop, void *pop_ptr)
    :NexTouch(pid, cid, name, pop, pop_ptr)
{
}

/**
 * Get picture's number.
 * 
 * @param number - an output parameter to save picture number.  
 * 
 * @reval true - success. 
 * @retval false - failed. 
 */
bool NexPicture::getPic(uint32_t *number)
{
    String cmd = String("get ");
    cmd += getObjName();
    cmd += ".pic";
    sendCommand(cmd.c_str());
    return recvRetNumber(number);
}

/**
 * Set picture's number.
 * 
 * @param number -the picture number.
 *
 * @retval true - success.
 * @retval false - failed. 
 */
bool NexPicture::setPic(uint32_t number)
{
    char buf[10] = {0};
    String cmd;
    
    utoa(number, buf, 10);
    cmd += getObjName();
    cmd += ".pic=";
    cmd += buf;

    sendCommand(cmd.c_str());
    return recvRetCommandFinished();
}

/**
 * Register picture pop callback function. 
 *
 * @param pop - the pointer to picture pop callback function.
 * @param ptr - the parameter to be transmitted to picture pop callback function. 
 */
void NexPicture::attachPop(NexTouchEventCb pop, void *ptr)
{
    NexTouch::attachPop(pop, ptr);
}

/**
 * Unload picture pop callback function.
 *
 */
void NexPicture::detachPop(void)
{
    NexTouch::detachPop();   
}
 
