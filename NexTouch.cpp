/**
 * @file NexTouch.cpp
 *
 * API of Nextion. 
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

#include "NexTouch.h"


/**
 * Constructor of Nextouch. 
 * 
 * @param pid - page id. 
 * @param cid - component id.    
 * @param name - component name. 
 * @param pop - pop event function pointer.   
 * @param pop_ptr - the parameter was transmitted to pop event function pointer.  
 * @param push - push event function pointer. 
 * @param push_ptr - the parameter was transmitted to push event function pointer.
 *   
 */
NexTouch::NexTouch(NexPid pid, NexCid cid, char *name, 
    NexTouchEventCb pop, void *pop_ptr,
    NexTouchEventCb push, void *push_ptr)
{
    this->pid = pid;
    this->cid = cid;
    this->name = name;
    this->cbPush = push;
    this->cbPop = pop;
    this->__cbpop_ptr = pop_ptr;
    this->__cbpush_ptr = push_ptr;
}

/**
 * Get page id.
 *
 * @return the id of page.  
 */
NexPid NexTouch::getPid(void)
{
    return pid;
}

/**
 * Get component id.
 *
 * @return the id of component.  
 */
NexCid NexTouch::getCid(void)
{
    return cid;
}

/**
 * Get component name.
 *
 * @return the name of component. 
 */
const char* NexTouch::getObjName(void)
{
    return name;
}

/**
 * Print current object address,page id,component id,
 * component name,pop event function address,push event function address. 
 *  
 */
void NexTouch::print(void)
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
    dbSerialPrint(",");
    dbSerialPrint((uint32_t)cbPush);
    dbSerialPrint(",");
    dbSerialPrint((uint32_t)cbPop);
    dbSerialPrintln("]");
}

void NexTouch::attachPush(NexTouchEventCb push, void *ptr)
{
    this->cbPush = push;
    this->__cbpush_ptr = ptr;
}

void NexTouch::detachPush(void)
{
    this->cbPush = NULL;
    this->__cbpush_ptr = NULL;
}

void NexTouch::attachPop(NexTouchEventCb pop, void *ptr)
{
    this->cbPop = pop;
    this->__cbpop_ptr = ptr;
}

void NexTouch::detachPop(void)
{
    this->cbPop = NULL;    
    this->__cbpop_ptr = NULL;
}

void NexTouch::push(void)
{
    if (cbPush)
    {
        cbPush(__cbpush_ptr);
    }
}

void NexTouch::pop(void)
{
    if (cbPop)
    {
        cbPop(__cbpop_ptr);
    }
}

