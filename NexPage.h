/**
 * @file NexPage.h
 *
 * The definition of class NexPage. 
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

#ifndef __NEXPAGE_H__
#define __NEXPAGE_H__

#include "NexTouch.h"
#include "NexHardware.h"

/**
 * NexPage,subclass of NexTouch,provides simple methods to control page component. 
 *
 */
class NexPage: public NexTouch
{
public: /* methods */
    NexPage(NexPid pid, NexCid cid, const char *name);
    bool show(void);
};


#endif /* #ifndef __NEXPAGE_H__ */
