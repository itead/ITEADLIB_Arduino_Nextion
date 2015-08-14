/**
 * @file NexObject.cpp
 *
 * The implementation of class NexObject. 
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
#include "NexObject.h"

/**
 * Constructor
 * 
 * @param pid - page id. 
 * @param cid - component id.    
 * @param name - component name. 
 */
NexObject::NexObject(uint8_t pid, uint8_t cid, const char *name)
{
    this->pid = pid;
    this->cid = cid;
    this->name = name;
    dbSerialPrintln("NexObject called");
}

/**
 * Get page id.
 *
 * @return the id of page.  
 */
uint8_t NexObject::getObjPid(void)
{
    return pid;
}

/**
 * Get component id.
 *
 * @return the id of component.  
 */
uint8_t NexObject::getObjCid(void)
{
    return cid;
}

/**
 * Get component name.
 *
 * @return the name of component. 
 */
const char* NexObject::getObjName(void)
{
    return name;
}

/**
 * Print current object address,page id,component id,
 * component name,pop event function address,push event function address. 
 *  
 */
void NexObject::printObjInfo(void)
{
    dbSerialPrint("[");
    dbSerialPrint((uint32_t)this);
    dbSerialPrint(":");
    dbSerialPrint(pid);
    dbSerialPrint(",");
    dbSerialPrint(cid);
    dbSerialPrint(",");
    if (name)
    {
        dbSerialPrint(name);
    }
    else
    {
        dbSerialPrint("(null)");
    }
    dbSerialPrintln("]");
}

