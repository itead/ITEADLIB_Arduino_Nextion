/**
 * @file NexHotspot.h
 *
 * API of NexHotspot. 
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

#ifndef __NEXHOTSPOT_H__
#define __NEXHOTSPOT_H__
#ifdef __cplusplus
#include "NexTouch.h"
#include "NexHardware.h"

/**
 * NexHotspot,subclass of NexTouch,provides simple methods to control hotspot component. 
 *
 */
class NexHotspot: public NexTouch
{
public: /* methods */
    NexHotspot(NexPid pid, NexCid cid, char *name, 
        NexTouchEventCb pop = NULL, void *pop_ptr = NULL,
        NexTouchEventCb push = NULL, void *push_ptr = NULL);

    void attachPush(NexTouchEventCb push, void *ptr = NULL);
    void detachPush(void);
    void attachPop(NexTouchEventCb pop, void *ptr = NULL);
    void detachPop(void);

};

#endif /* #ifdef __cplusplus */
#endif /* #ifndef __NEXHOTSPOT_H__ */
