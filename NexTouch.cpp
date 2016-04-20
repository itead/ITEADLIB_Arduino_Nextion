/**
 * @file NexTouch.cpp
 *
 * The implementation of class NexTouch. 
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
#include "NexTouch.h"


NexTouch::NexTouch(uint8_t pid, uint8_t cid, const char *name, void *value)
    :NexObject(pid, cid, name, value)
{
    this->__cb_push = NULL;
    this->__cb_pop = NULL;
    this->__cb_value = NULL;
    this->__cbpop_ptr = NULL;
    this->__cbpush_ptr = NULL;
    this->__cbvalue_ptr = NULL;
}

void NexTouch::attachPush(NexTouchEventCb push, void *ptr)
{
    this->__cb_push = push;
    this->__cbpush_ptr = ptr;
}

void NexTouch::detachPush(void)
{
    this->__cb_push = NULL;
    this->__cbpush_ptr = NULL;
}

void NexTouch::attachPop(NexTouchEventCb pop, void *ptr)
{
    this->__cb_pop = pop;
    this->__cbpop_ptr = ptr;
}

void NexTouch::detachPop(void)
{
    this->__cb_pop = NULL;    
    this->__cbpop_ptr = NULL;
}

void NexTouch::attachValue(NexTouchEventCb value, void *ptr)
{
    this->__cb_value = value;
    this->__cbvalue_ptr = ptr;
}

void NexTouch::detachValue(void)
{
    this->__cb_value = NULL;    
    this->__cbvalue_ptr = NULL;
}

void NexTouch::push(void)
{
    if (__cb_push)
    {
        __cb_push(__cbpush_ptr);
    }
}

void NexTouch::pop(void)
{
    if (__cb_pop)
    {
        __cb_pop(__cbpop_ptr);
    }
}

void NexTouch::value(uint8_t type, void *value)
{
    ((NexObject *)__cbvalue_ptr)->setObjValue(type, value);

    if (__cb_value)
    {
        __cb_value(__cbvalue_ptr);
    }
}
void NexTouch::iterate(NexTouch **list, uint8_t pid, uint8_t cid, int32_t event, void *value)
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
            else if (NEX_EVENT_VALUE == event)
            {
                e->value(NEX_EVENT_VALUE, value);
            }
            else if (NEX_EVENT_STRING == event)
            {
                e->value(NEX_EVENT_STRING, value);
            }
            
            break;
        }
    }
}

