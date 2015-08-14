/**
 * @file NexTouch.h
 *
 * The definition of class NexTouch. 
 *
 * @author Wu Pengfei (email:<pengfei.wu@itead.cc>)
 * @date 2015/8/13
 *
 * @copyright 
 * Copyright (C) 2014-2015 ITEAD Intelligent Systems Co., Ltd. \n
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 */

#ifndef __NEXTOUCH_H__
#define __NEXTOUCH_H__

#include <Arduino.h>
#include "NexConfig.h"
#include "NexObject.h"

typedef void (*NexTouchEventCb)(void *ptr);

typedef enum {
    NEX_EVENT_POP = 0x00,
    NEX_EVENT_PUSH = 0x01,
    NEX_EVENT_NULL
} NexEventType;

/**
 * Root Class of Nextion Components. 
 *
 */
class NexTouch: public NexObject
{
public: /* static methods */    
    static void iterate(NexTouch **list, uint8_t pid, uint8_t cid, NexEventType event);

public: /* methods */
    NexTouch(uint8_t pid, uint8_t cid, const char *name);

    void attachPush(NexTouchEventCb push, void *ptr = NULL);
    void detachPush(void);
    void attachPop(NexTouchEventCb pop, void *ptr = NULL);
    void detachPop(void);
    
private: /* methods */ 
    void push(void);
    void pop(void);
    
private: /* data */ 
    NexTouchEventCb cbPush;
    void *__cbpush_ptr;
    NexTouchEventCb cbPop;
    void *__cbpop_ptr;
};


#endif /* #ifndef __NEXTOUCH_H__ */
