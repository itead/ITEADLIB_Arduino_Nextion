/**
 * @file NexHotspot.cpp
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
 
#include "NexHotspot.h"

/**
 * Constructor,inherited NexTouch's constructor function.
 *
 */
NexHotspot::NexHotspot(NexPid pid, NexCid cid, char *name, 
    NexTouchEventCb pop, void *pop_ptr,
    NexTouchEventCb push, void *push_ptr)
    :NexTouch(pid, cid, name, pop, pop_ptr, push, push_ptr)
{
}

/**
 * Register hotspot push callback function. 
 *
 * @param push - the pointer to hotspot push callback function.
 * @param ptr - the parameter to be transmitted to hotspot push callback function. 
 */
void NexHotspot::attachPush(NexTouchEventCb push, void *ptr)
{
    NexTouch::attachPush(push, ptr);
}

/**
 * Unload hotsopt push callback function.
 *
 */
void NexHotspot::detachPush(void)
{
    NexTouch::detachPush();
}

/**
 * Register hotspot pop callback function. 
 *
 * @param pop - the pointer to hotspot pot callback function.
 * @param ptr - the parameter to be transmitted to hotspot pop callback function. 
 */
void NexHotspot::attachPop(NexTouchEventCb pop, void *ptr)
{
    NexTouch::attachPop(pop, ptr);
}

/**
 * Unload hotsopt pop callback function.
 *
 */
void NexHotspot::detachPop(void)
{
    NexTouch::detachPop();   
}
