/**
 * @file NexTouch.h
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

#ifndef __NEXTOUCH_H__
#define __NEXTOUCH_H__
#ifdef __cplusplus
#include <Arduino.h>
#include "NexSerialConfig.h"

typedef uint8_t NexPid;
typedef uint8_t NexCid;

typedef void (*NexTouchEventCb)(void *ptr);

/**
 * Root Class of Nextion Components. 
 *
 */
class NexTouch 
{
public: /* methods */
    NexTouch(NexPid pid, NexCid cid, char *name, 
        NexTouchEventCb pop = NULL, void *pop_ptr = NULL,
        NexTouchEventCb push = NULL, void *push_ptr = NULL);

    NexPid getPid(void);    
    NexCid getCid(void);
    const char *getObjName(void);
    void print(void);

protected: /* methods */    
    void attachPush(NexTouchEventCb push, void *ptr = NULL);
    void detachPush(void);
    void attachPop(NexTouchEventCb pop, void *ptr = NULL);
    void detachPop(void);
    
private: /* methods */ 
    void push(void);
    void pop(void);
    
private: /* data */ 
    NexPid pid; /* Page ID */
    NexCid cid; /* Component ID */
    char *name; /* An unique name */
    NexTouchEventCb cbPush;
    void *__cbpush_ptr;
    NexTouchEventCb cbPop;
    void *__cbpop_ptr;
};

#endif /* #ifdef __cplusplus */
#endif /* #ifndef __NEXTOUCH_H__ */
