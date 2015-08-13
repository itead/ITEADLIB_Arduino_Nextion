/**
 * @file NexProgressBar.h
 *
 * API of NexProgressBar. 
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

#ifndef __NEXPROGRESSBAR_H__
#define __NEXPROGRESSBAR_H__
#ifdef __cplusplus
#include "NexTouch.h"
#include "NexHardware.h"

/**
 * NexProgressBar,subclass of NexTouch,provides simple methods to control progress bar component. 
 *
 */
class NexProgressBar: public NexObject
{
public: /* methods */
    NexProgressBar(NexPid pid, NexCid cid, const char *name);
    
    bool getValue(uint32_t *number);
    bool setValue(uint32_t number);
};

#endif /* #ifdef __cplusplus */
#endif /* #ifndef __NEXPROGRESSBAR_H__ */
