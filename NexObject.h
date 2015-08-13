/**
 * @file NexObject.h
 *
 * The root of all classes in Nextion library. 
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

#ifndef __NEXOBJECT_H__
#define __NEXOBJECT_H__
#ifdef __cplusplus
#include <Arduino.h>
#include "NexSerialConfig.h"

typedef uint8_t NexPid;
typedef uint8_t NexCid;

/**
 * Root Class of Nextion Components. 
 */
class NexObject 
{
public: /* methods */
    NexObject(NexPid pid, NexCid cid, const char *name);

    NexPid getObjPid(void);    
    NexCid getObjCid(void);
    const char *getObjName(void);
    void printObjInfo(void);
    
private: /* data */ 
    NexPid pid; /* Page ID */
    NexCid cid; /* Component ID */
    const char *name; /* An unique name */
};

#endif /* #ifdef __cplusplus */
#endif /* #ifndef __NEXOBJECT_H__ */
