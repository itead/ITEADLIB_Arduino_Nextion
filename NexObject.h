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
 * Root class of all Nextion components. 
 *
 * Provides the essential attributes of a Nextion component and the methods accessing
 * them. At least, Page ID(pid), Component ID(pid) and an unique name are needed for
 * creating a component in Nexiton library. 
 */
class NexObject 
{
public: /* methods */
    NexObject(uint8_t pid, uint8_t cid, const char *name);
    void printObjInfo(void);

protected: /* methods */
    uint8_t getObjPid(void);    
    uint8_t getObjCid(void);
    const char *getObjName(void);    
    
private: /* data */ 
    uint8_t pid; /* Page ID */
    uint8_t cid; /* Component ID */
    const char *name; /* An unique name */
};

#endif /* #ifndef __NEXOBJECT_H__ */
