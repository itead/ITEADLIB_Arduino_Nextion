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
 * @param pop - pop event function pointer.   
 * @param pop_ptr - the parameter was transmitted to pop event function pointer.  
 * @param push - push event function pointer. 
 * @param push_ptr - the parameter was transmitted to push event function pointer.
 *   
 */
NexTouch::NexTouch(NexPid pid, NexCid cid, const char *name)
    :NexObject(pid, cid, name)
{
    this->cbPush = NULL;
    this->cbPop = NULL;
    this->__cbpop_ptr = NULL;
    this->__cbpush_ptr = NULL;
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

void NexTouch::iterate(NexTouch **list, NexPid pid, NexCid cid, NexEventType event)
{
    NexTouch *e = NULL;
    uint16_t i = 0;

    if (NULL == list)
    {
        return;
    }
    
    for(i = 0; (e = list[i]) != NULL; i++)
    {
        if (e->getObjPid() == pid && e->getObjCid() == cid)
        {
            e->printObjInfo();
            if (NEX_EVENT_PUSH == event)
            {
                e->push();
            }
            else if (NEX_EVENT_POP == event)
            {
                e->pop();
            }
            
            break;
        }
    }
}

