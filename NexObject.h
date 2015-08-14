/**
 * @file NexObject.h
 *
 * The definition of class NexObject. 
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
#ifndef __NEXOBJECT_H__
#define __NEXOBJECT_H__
#include <Arduino.h>
#include "NexConfig.h"

/**
 * Page ID 
 * 
 * Actually, Page is also a component which can contain other components such as 
 * Button, Text, etc. 
 */
typedef uint8_t NexPid; 

typedef uint8_t NexCid; /**< Component ID */

/**
 * Root class of all Nextion components. 
 *
 * Provides the essential attributes of a Nextion component and the methods accessing
 * them. At least, Page ID(pid), Component ID(pid) and an unique name are needed for
 * creating a component in Nexiton library. 
 */
class NexObject 
{
public: /* methods */
    NexObject(NexPid pid, NexCid cid, const char *name);
    void printObjInfo(void);

protected: /* methods */
    NexPid getObjPid(void);    
    NexCid getObjCid(void);
    const char *getObjName(void);    
    
private: /* data */ 
    NexPid pid; /* Page ID */
    NexCid cid; /* Component ID */
    const char *name; /* An unique name */
};

#endif /* #ifndef __NEXOBJECT_H__ */
