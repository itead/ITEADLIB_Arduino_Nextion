/**
 * @file NexSlider.h
 *
 * API of NexSlider. 
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

#ifndef __NEXSLIDER_H__
#define __NEXSLIDER_H__
#ifdef __cplusplus
#include "NexTouch.h"

/**
 * NexSlider,subclass of NexTouch,provides simple methods to control slider component. 
 *
 */
class NexSlider: public NexTouch
{
public: /* methods */
    NexSlider(NexPid pid, NexCid cid, char *name, NexTouchEventCb pop = NULL, void *pop_ptr = NULL);
    
    void attachPop(NexTouchEventCb pop, void *ptr = NULL);
    void detachPop(void);
    
    bool getValue(uint32_t *number);
    bool setValue(uint32_t number);
};

#endif /* #ifdef __cplusplus */
#endif /* #ifndef __NEXSLIDER_H__ */
