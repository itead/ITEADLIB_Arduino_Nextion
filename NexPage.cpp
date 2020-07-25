/**
 * @file NexPage.cpp
 *
 * The implementation of class NexPage. 
 *
 * @author  Wu Pengfei (email:<pengfei.wu@itead.cc>)
 * @date    2015/8/13
 * @author Jyrki Berg 2/17/2019 (https://github.com/jyberg)
 * 
 * @copyright 
 * Copyright (C) 2014-2015 ITEAD Intelligent Systems Co., Ltd. \n
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 */

#include "NexPage.h"

NexPage::NexPage(uint8_t pid, uint8_t cid, const char *name)
    :NexTouch(pid, cid, name, nullptr)
{
}

bool NexPage::show(void)
{
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

bool NexPage::setVisibleAll(bool visible)
{
    String cmd = String("vis ");
    cmd += "255,";
    if (visible)
    {
        cmd += "1";
    }
    else
    {
        cmd += "0";
    }
    sendCommand(cmd.c_str());
    return recvRetCommandFinished();
}

