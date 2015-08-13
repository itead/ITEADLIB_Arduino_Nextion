/**
 * @file NexPage.cpp
 *
 * API of NexPage. 
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

#include "NexPage.h"

/**
 * Constructor,inherited NexTouch's constructor function.
 *
 */
NexPage::NexPage(NexPid pid, NexCid cid, const char *name, NexTouchEventCb pop, void *pop_ptr)
    :NexTouch(pid, cid, name, pop, pop_ptr)
{
}

/**
 * Change page.  
 * 
 * @retval true - success. 
 * @retval false - failed. 
 */
bool NexPage::show(void)
{
    uint8_t buffer[4] = {0};

    const char *name = getObjName();
    if (!name)
    {
        return false;
    }
    
    String cmd = String("page ");
    cmd += name;
    sendCommand(cmd.c_str());
    return recvRetCommandFinished();
}

/**
 * Register page pop callback function. 
 *
 * @param pop - the pointer to page pop callback function.
 * @param ptr - the parameter to be transmitted to page pop callback function. 
 */
void NexPage::attachPop(NexTouchEventCb pop, void *ptr)
{
    NexTouch::attachPop(pop, ptr);
}

/**
 * Unload page pop callback function.
 *
 */
void NexPage::detachPop(void)
{
    NexTouch::detachPop();   
}
