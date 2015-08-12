/**
 * @file NexPicture.h
 *
 * API of NexPicture. 
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

#ifndef __NEXPICTURE_H__
#define __NEXPICTURE_H__
#ifdef __cplusplus
#include "NexTouch.h"
#include "NexHardware.h"

/**
 * NexPicture,subclass of NexTouch,provides simple methods to control picture component. 
 *
 */
class NexPicture: public NexTouch
{
public: /* methods */
    NexPicture(NexPid pid, NexCid cid, char *name, NexTouchEventCb pop = NULL, void *pop_ptr = NULL);
    
    void attachPop(NexTouchEventCb pop, void *ptr = NULL);
    void detachPop(void);

    bool getPic(uint32_t *number);
    bool setPic(uint32_t number);
};

#endif /* #ifdef __cplusplus */
#endif /* #ifndef __NEXPICTURE_H__ */
