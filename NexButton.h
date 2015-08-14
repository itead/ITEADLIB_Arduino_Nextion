/**
 * @file NexButton.h
 *
 * The definition of class NexButton. 
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

#ifndef __NEXBUTTON_H__
#define __NEXBUTTON_H__

#include "NexTouch.h"
#include "NexHardware.h"

/**
 * NexButton,subclass of NexTouch,provides simple methods to control button component. 
 *
 */
class NexButton: public NexTouch
{
public: /* methods */
    NexButton(uint8_t pid, uint8_t cid, const char *name);

    uint16_t getText(char *buffer, uint16_t len);    
    bool setText(const char *buffer);    
};


#endif /* #ifndef __NEXBUTTON_H__ */
