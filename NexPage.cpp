/**
 * @file NexPage.cpp
 *
 * The implementation of class NexPage. 
 *
 * @author  Wu Pengfei (email:<pengfei.wu@itead.cc>)
 * @date    2015/8/13
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
NexPage::NexPage(NexPid pid, NexCid cid, const char *name)
    :NexTouch(pid, cid, name)
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

