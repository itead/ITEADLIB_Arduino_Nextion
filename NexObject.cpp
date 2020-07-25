/**
 * @file NexObject.cpp
 *
 * The implementation of class NexObject. 
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
#include "NexObject.h"
#include "NexHardware.h"

NexObject::NexObject(uint8_t pid, uint8_t cid, const char *name, const NexObject* page):
__pid{pid},__cid{cid},__name{name}, __page{page}
{
}

uint8_t NexObject::getObjPid(void)
{
    return __pid;
}

uint8_t NexObject::getObjCid(void)
{
    return __cid;
}

const char* NexObject::getObjName(void) const
{
    return __name;
}

const char* NexObject::getObjPageName(void)
{
    if(__page)
    {
        return __page->getObjName();
    }
    return nullptr;
}

void NexObject::getObjGlobalPageName(String &gName)
{
    if(__page)
    {
        gName += __page->getObjName();
        gName += ".";
    }
    gName +=__name;
}

bool NexObject::GetObjectWidth( uint32_t &width)
{
    String cmd;
    cmd = "get ";
    getObjGlobalPageName(cmd);
    cmd += ".w";
    sendCommand(cmd.c_str());
    return recvRetNumber(&width);
}

bool NexObject::GetObjectHeight( uint32_t &height)
{
    String cmd;
    cmd = "get ";
    getObjGlobalPageName(cmd);
    cmd += ".h";
    sendCommand(cmd.c_str());
    return recvRetNumber(&height);
}

void NexObject::printObjInfo(void)
{
    dbSerialPrint("[");
    dbSerialPrint((uint32_t)this);
    dbSerialPrint(":");
    dbSerialPrint(__pid);
    dbSerialPrint(",");
    dbSerialPrint(__cid);
    dbSerialPrint(",");
    if(__page)
    {
        dbSerialPrint(__page->getObjName());
    }
    else
    {
        dbSerialPrint("(null)");
    }    
    if (__name)
    {
        dbSerialPrint(__name);
    }
    else
    {
        dbSerialPrint("(null)");
    }
    dbSerialPrintln("]");
}

bool NexObject::setVisible(bool visible)
{
    String cmd = String("vis ");
    cmd += __name;
    cmd += ",";
    if (visible)
    {
        cmd += "1";
    } else
    {
        cmd += "0";
    }
    sendCommand(cmd.c_str());
    return recvRetCommandFinished();
}

